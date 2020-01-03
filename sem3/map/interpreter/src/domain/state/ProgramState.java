package domain.state;

import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.DictionaryFileTable;
import domain.state.heap.DictionaryHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.type.IllegalTypeException;
import domain.value.IValue;

import java.io.IOException;
import java.util.*;

public class ProgramState
{
    private Stack<IStatement> executionStack;
    private DictSymbolTable symbolTable;
    private List<IValue<?>> out;
    private static DictionaryFileTable fileTable;
    private static DictionaryHeap heap;
    public final int id;
    private static volatile int globalId = 1;

    public ProgramState(IStatement program) throws IllegalTypeException
    {
        program.typeCheck(new HashMap<>());
        this.id = globalId;
        incrementGlobalId();
        this.executionStack = new Stack<>();
        this.symbolTable = new DictSymbolTable();
        this.out = new ArrayList<>();
        fileTable = new DictionaryFileTable();
        heap = new DictionaryHeap();
        this.executionStack.push(program);
    }

    public ProgramState(ProgramState programState)
    {
        this.id = globalId;
        incrementGlobalId();
        executionStack = new Stack<>();
        symbolTable = new DictSymbolTable(programState.symbolTable);
        out = Collections.emptyList();
    }

    public int getId() { return id; }

    public static synchronized int getGlobalIdId() { return globalId; }

    public static synchronized void setGlobalId(int globalId) { ProgramState.globalId = globalId; }

    private static synchronized void incrementGlobalId() { globalId = globalId + 1; }

    public Stack<IStatement> getExecutionStack() { return this.executionStack; }

    public DictSymbolTable getSymbolTable() { return this.symbolTable; }

    public DictionaryFileTable getFileTable() { return fileTable; }

    public DictionaryHeap getHeap() { return heap; }

    public List<IValue<?>> getOut() { return this.out; }

    public boolean isFinished() { return this.executionStack.size() == 0; }

    public ProgramState oneStep()
            throws VariableAlreadyDefinedException, UndeclaredVariableException,
            IllegalTypeException, DescriptorExistsException,
            DescriptorNotExistsException, IOException, InvalidMemoryAddressException
    {
        IStatement currentStatement = executionStack.pop();
        //        if (currentStatement instanceof PrintStatement)
//        {
//            List<IValue<?>> printLog = this.getOut();
//            IValue<?> lastPrint = printLog.get(printLog.size() - 1);
//            System.out.println("PRINT: " + lastPrint.toString());
//        }
        return currentStatement.execute(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ProgramState that = (ProgramState) o;
        return id == that.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString()
    {
        /* Return full representation of current program */
        final String DELIMITER = "======";
        StringBuilder output = new StringBuilder();
        Object[] programProperties =
                {this.executionStack, this.symbolTable, heap, this.out, fileTable};
        for (Object programProperty : programProperties)
        {
            output.append(DELIMITER).append("\n");
            output.append(programProperty.toString());
            output.append("\n");
        }
        return output.toString();
    }
}
