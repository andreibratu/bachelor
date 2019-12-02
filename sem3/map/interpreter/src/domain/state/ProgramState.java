package domain.state;

import domain.state.collector.IGarbageCollector;
import domain.state.collector.SafeDictionaryGarbageCollector;
import domain.state.file.DictionaryFileTable;
import domain.state.file.IFileTable;
import domain.state.heap.DictionaryHeap;
import domain.state.heap.IHeap;
import domain.state.symbol.DictionarySymbolTable;
import domain.state.symbol.ISymbolTable;
import domain.statement.IStatement;
import domain.value.IValue;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class ProgramState {
    private Stack<IStatement> executionStack;
    private ISymbolTable symbolTable;
    private List<IValue> out;
    private IFileTable fileTable;
    private IHeap heap;
    private IGarbageCollector garbageCollector;

    public ProgramState(IStatement program)
    {
        this.executionStack = new Stack<>();
        this.symbolTable = new DictionarySymbolTable();
        this.out = new LinkedList<>();
        this.fileTable = new DictionaryFileTable();
        this.heap = new DictionaryHeap();
        this.garbageCollector = new SafeDictionaryGarbageCollector(
                (DictionarySymbolTable) symbolTable,
                (DictionaryHeap) heap
        );
        this.executionStack.push(program);
    }

    public Stack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public ISymbolTable getSymbolTable() {
        return this.symbolTable;
    }

    public IFileTable getFileTable() { return this.fileTable; }

    public IHeap getHeap() { return this.heap; }

    public List<IValue> getOut() {
        return this.out;
    }

    @Override
    @SuppressWarnings("unchecked")
    public ProgramState clone() throws CloneNotSupportedException
    {
        ProgramState clone = (ProgramState) super.clone();
        clone.executionStack = (Stack<IStatement>) this.executionStack.clone();
        clone.symbolTable = (DictionarySymbolTable) this.symbolTable.clone();
        clone.out = (List<IValue>) this.symbolTable.clone();
        return clone;
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

    public IGarbageCollector getGarbageCollector()
    {
        return garbageCollector;
    }
}
