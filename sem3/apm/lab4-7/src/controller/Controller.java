package controller;

import model.program.ProgramState;
import model.statement.Statement;
import model.statement.StatementExecutionException;
import repository.IRepository;

import java.util.Stack;

public class Controller implements IController {
    private IRepository repository;

    public Controller(IRepository repository)
    {
        this.repository = repository;
    }

    @Override
    public ProgramState step(ProgramState state) throws Exception {
        Stack<Statement> stack = state.getExecutionStack();
        if (stack.isEmpty()) throw new StatementExecutionException();
        Statement currentStatement = stack.pop();
        return currentStatement.execute(state);
    }
}
