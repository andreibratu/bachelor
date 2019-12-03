package domain.state;

import domain.state.file.*;
import domain.state.heap.DictionaryHeap;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictionarySymbolTable;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.statement.print.PrintStatement;
import domain.type.IllegalTypeException;
import domain.value.IValue;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class ProgramState {
    private Stack<IStatement> executionStack;
    private ISymbolTable symbolTable;
    private List<IValue> out;
    private IFileTable fileTable;
    private IHeap heap;
    private int id;
    private static volatile int globalId = 1;

    public ProgramState(IStatement program)
    {
        this.id = globalId;
        incrementGlobalId();
        this.executionStack = new Stack<>();
        this.symbolTable = new DictionarySymbolTable();
        this.out = new LinkedList<>();
        this.fileTable = new DictionaryFileTable();
        this.heap = new DictionaryHeap();
        this.executionStack.push(program);
    }

    public ProgramState(ProgramState programState)
    {
        this.id = globalId;
        incrementGlobalId();
        executionStack = new Stack<>();
        symbolTable = new DictionarySymbolTable((DictionarySymbolTable) programState.symbolTable);
        out = programState.out;
        fileTable = programState.fileTable;
        heap = programState.heap;
    }

    public static synchronized int getGlobalIdId() { return globalId; }

    public static synchronized void setGlobalId(int globalId) { ProgramState.globalId = globalId; }

    private static synchronized void incrementGlobalId() { globalId = globalId + 1; }

    public Stack<IStatement> getExecutionStack() { return this.executionStack; }

    public ISymbolTable getSymbolTable() { return this.symbolTable; }

    public IFileTable getFileTable() { return this.fileTable; }

    public IHeap getHeap() { return this.heap; }

    public List<IValue> getOut() { return this.out; }

    public boolean isFinished() { return this.executionStack.size() == 0; }

    public ProgramState oneStep()
            throws VariableAlreadyDefinedException, UndeclaredVariableException,
            IllegalTypeException, DescriptorExistsException, FileDoesNotExistException,
            DescriptorNotExistsException, IOException, InvalidMemoryAddressException
    {
        IStatement currentStatement = executionStack.pop();
        ProgramState result = currentStatement.execute(this);
        if (currentStatement instanceof PrintStatement)
        {
            List<IValue> printLog = this.getOut();
            IValue lastPrint = printLog.get(printLog.size() - 1);
            System.out.println("PRINT: " + lastPrint.toString());
        }
        return result;
    }

    @Override
    public String toString()
    {
        /* Return full representation of current program */
        final String DELIMITER = "======";
        StringBuilder output = new StringBuilder();
        Object[] programProperties =
                {this.executionStack, this.symbolTable, this.heap, this.out, this.fileTable};
        for (Object programProperty : programProperties)
        {
            output.append(DELIMITER).append("\n");
            output.append(programProperty.toString());
            output.append("\n");
        }
        return output.toString();
    }
}
