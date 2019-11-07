package controller;

import adt.list.IList;
import adt.stack.IStack;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.PrintStatement;
import domain.value.Value;
import exception.state.ExecutionFinishedException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;
import repository.IRepository;
import java.util.EmptyStackException;

public class Controller implements IController
{
    private IRepository repository;
    private boolean debugFlag;

    public Controller(IRepository repository, boolean debugFlag)
    {
        this.repository = repository;
        this.debugFlag = debugFlag;
    }

    @Override
    public ProgramState oneStep(ProgramState state)
            throws ExecutionFinishedException, VariableAlreadyDefinedException,
            UndeclaredVariableException, IllegalTypeException
    {
        IStack<IStatement> stack = state.getExecutionStack();
        try
        {
            IStatement currentStatement = stack.pop();
            ProgramState result = currentStatement.execute(state);
            if (currentStatement instanceof PrintStatement)
            {
                IList<Value> printLog = result.getOut();
                Value lastPrint = printLog.get(printLog.size() - 1);
                System.out.println("PRINT: " + lastPrint.toString());
            }
            return result;
        } catch (EmptyStackException e)
        {
            throw new ExecutionFinishedException();
        }
    }

    public void allSteps()
    {
        ProgramState currentProgram = this.repository.getCurrentProgram();
        try
        {
            while(true)
            {
                if (debugFlag) System.out.println(currentProgram.toString());
                oneStep(currentProgram);
            }
        }
        catch(Exception e)
        {
            System.out.println(e.getClass().toString());
            System.out.println(e.getMessage());
            System.exit(0);
        }
    }
}
