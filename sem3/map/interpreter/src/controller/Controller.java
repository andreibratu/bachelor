package controller;

import adt.list.IList;
import adt.stack.IStack;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.print.PrintStatement;
import domain.value.IValue;
import exception.io.DescriptorExistsException;
import exception.io.DescriptorNotExistsException;
import exception.io.FileDoesNotExistException;
import exception.state.ExecutionFinishedException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;
import repository.IRepository;

import java.io.IOException;
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
            UndeclaredVariableException, IllegalTypeException, DescriptorExistsException,
            FileDoesNotExistException, DescriptorNotExistsException, IOException
    {
        IStack<IStatement> stack = state.getExecutionStack();
        try
        {
            IStatement currentStatement = stack.pop();
            ProgramState result = currentStatement.execute(state);
            if (currentStatement instanceof PrintStatement)
            {
                IList<IValue> printLog = result.getOut();
                IValue lastPrint = printLog.get(printLog.size() - 1);
                System.out.println("PRINT: " + lastPrint.toString());
            }
            return result;
        } catch (EmptyStackException e)
        {
            throw new ExecutionFinishedException();
        }
    }

    public void allSteps()
            throws VariableAlreadyDefinedException, DescriptorNotExistsException, UndeclaredVariableException,
            IOException, ExecutionFinishedException, FileDoesNotExistException, DescriptorExistsException,
            IllegalTypeException
    {
        ProgramState currentProgram = this.repository.getProgram();
        this.repository.logProgramExecution();
        while(!currentProgram.getExecutionStack().isEmpty())
        {
            if (debugFlag) System.out.println(currentProgram.getProgramStatus());
            oneStep(currentProgram);
            this.repository.logProgramExecution();
        }
    }
}
