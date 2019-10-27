package controller;

import adt.IStack;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.StatementExecutionException;
import repository.IRepository;

public class Controller implements IController {
    private IRepository repository;

    public Controller(IRepository repository)
    {
        this.repository = repository;
    }

    @Override
    public ProgramState oneStep(ProgramState state) throws Exception {
        IStack<IStatement> stack = state.getExecutionStack();
        if (stack.isEmpty()) throw new StatementExecutionException();
        IStatement currentStatement = stack.pop();
        return currentStatement.execute(state);
    }

    public void allSteps()
    {
        ProgramState currentProgram = this.repository.getCurrentProgram();
        try {
            while(true)
            {
                System.out.println(currentProgram.toString());
                oneStep(currentProgram);
            }
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
            System.exit(0);
        }
    }
}
