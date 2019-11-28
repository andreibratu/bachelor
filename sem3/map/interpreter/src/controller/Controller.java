package controller;

import domain.state.ProgramState;
import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.statement.print.PrintStatement;
import domain.value.IValue;
import domain.type.IllegalTypeException;
import repository.IRepository;

import java.io.IOException;
import java.util.List;
import java.util.Stack;

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
            throws VariableAlreadyDefinedException, UndeclaredVariableException,
            IllegalTypeException, DescriptorExistsException, FileDoesNotExistException,
            DescriptorNotExistsException, IOException, InvalidMemoryAddressException
    {
        Stack<IStatement> stack = state.getExecutionStack();
        IStatement currentStatement = stack.pop();
        ProgramState result = currentStatement.execute(state);
        if (currentStatement instanceof PrintStatement)
        {
            List<IValue> printLog = result.getOut();
            IValue lastPrint = printLog.get(printLog.size() - 1);
            System.out.println("PRINT: " + lastPrint.toString());
        }
        return result;
    }

    public void allSteps()
            throws VariableAlreadyDefinedException, DescriptorNotExistsException,
            UndeclaredVariableException, IOException, FileDoesNotExistException,
            DescriptorExistsException, IllegalTypeException, InvalidMemoryAddressException
    {
        ProgramState currentProgram = this.repository.getProgram();
        while(!currentProgram.getExecutionStack().isEmpty())
        {
            if (debugFlag) System.out.println(currentProgram.getProgramStatus());
            oneStep(currentProgram);
        }
        this.repository.logProgramExecution();
    }
}
