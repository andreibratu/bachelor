package controller;

import domain.state.ProgramState;
import repository.IRepository;

import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller implements IController
{
    private final IRepository repository;
    private final ExecutorService executor;
    private final boolean debugFlag;

    public Controller(IRepository repository, boolean debugFlag)
    {
        executor = Executors.newFixedThreadPool(2);
        this.repository = repository;
        this.debugFlag = debugFlag;
    }

    public void removeCompletedPrograms()
    {
        this.repository.setProgramList(
            this.repository.getProgramList().stream()
            .filter(p -> !p.isFinished())
            .collect(Collectors.toList()));
    }

    public void oneStepAllPrograms() throws InterruptedException
    {
        List<ProgramState> programStates = this.repository.getProgramList();
        // Log each program state into file
        if(debugFlag) programStates.forEach(repository::logProgramExecution);

        // Run concurrently one step of every program state

        // Prepare list of callables
        List<Callable<ProgramState>> callables = programStates.stream()
            .map(p -> (Callable<ProgramState>)(p::oneStep))
            .collect(Collectors.toList());

        List<ProgramState> newProgramStates = executor.invokeAll(callables).stream()
            .map(programStateFuture -> {
                ProgramState programState = null;
                try { programState = programStateFuture.get(); }
                catch (Exception e) { System.out.println(e.getMessage()); }
                return programState;
            })
            .filter(Objects::nonNull)
            .filter(state -> !programStates.contains(state))
            .collect(Collectors.toList());

        programStates.addAll(newProgramStates.stream()
                .filter(state -> !programStates.contains(state))
                .collect(Collectors.toList())
        );
        removeCompletedPrograms();

        // After the execution, print the PrgState List into the log file
        if(debugFlag) programStates.forEach(repository::logProgramExecution);
    }

    public void allSteps() throws InterruptedException
    {
        List<ProgramState> programStates = this.repository.getProgramList();
        while(programStates.size() > 0)
        {
            oneStepAllPrograms();
        }
        executor.shutdownNow();
    }
}
