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
    private IRepository repository;
    private ExecutorService executor;
    private boolean debugFlag;

    public Controller(IRepository repository, boolean debugFlag)
    {
        this.repository = repository;
        this.debugFlag = debugFlag;
    }

    public List<ProgramState> removeCompletedPrograms()
    {
        return this.repository.getProgramList().stream()
                .filter(p -> !p.isFinished())
                .collect(Collectors.toList());
    }

    private void oneStepAllPrograms(List<ProgramState> programStates) throws InterruptedException
    {
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
                .collect(Collectors.toList());

        // Add the new created threads to the list of existing threads
        programStates.addAll(newProgramStates);

        // After the execution, print the PrgState List into the log file
        if(debugFlag) programStates.forEach(repository::logProgramExecution);

        // Save the current programs in the repository
        repository.setProgramList(programStates);
    }

    public void allSteps() throws InterruptedException
    {
        executor = Executors.newFixedThreadPool(2);
        // Remove completed programs
        List<ProgramState> programStateList = removeCompletedPrograms();

        while(programStateList.size() > 0)
        {
            oneStepAllPrograms(programStateList);
            // Remove completed programs
            programStateList = removeCompletedPrograms();
        }
        executor.shutdownNow();
        // Note that the repository still contains at least one completed ProgramState,
        // thus the List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        // setProgramList of repository in order to change the repository
        repository.setProgramList(programStateList);
    }
}
