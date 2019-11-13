package domain.state;

import adt.dictionary.Dictionary;
import adt.dictionary.IDictionary;
import adt.list.IList;
import adt.list.List;
import adt.stack.IStack;
import adt.stack.Stack;
import domain.statement.IStatement;
import domain.value.IValue;
import domain.value.StringValue;

import java.io.BufferedReader;

public class ProgramState {
    private IStack<IStatement> executionStack;
    private IDictionary<String, IValue> symbolTable;
    private IList<IValue> out;
    private IDictionary<StringValue, BufferedReader> fileTable;
    Heap heap;

    public ProgramState(IStatement program)
    {
        this.executionStack = new Stack<>();
        this.symbolTable = new Dictionary<>();
        this.out = new List<>();
        this.fileTable = new Dictionary<>();
        this.heap = new Heap();
        this.executionStack.push(program);
    }

    public String getProgramStatus()
    {
        /* Return a string representation of program's current status */
        String currentStatement = this.executionStack.peek().toString();
        String symTableStatus = this.symbolTable.toString();
        return currentStatement + "\n" + symTableStatus + "-----";
    }

    public IStack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public IDictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public IDictionary<StringValue, BufferedReader> getFileTable() { return this.fileTable; }

    public Heap getHeap() { return this.heap; }

    public IList<IValue> getOut() {
        return this.out;
    }

    @Override
    @SuppressWarnings("unchecked")
    public ProgramState clone() throws CloneNotSupportedException
    {
        ProgramState clone = (ProgramState) super.clone();
        clone.executionStack = (IStack<IStatement>) this.executionStack.clone();
        clone.symbolTable = (IDictionary<String, IValue>) this.symbolTable.clone();
        clone.out = (IList<IValue>) this.symbolTable.clone();
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
        String[] names =
                {"EXECUTION STACK", "SYMBOL TABLE", "HEAP", "OUTPUT", "FILE TABLE"};
        for(int i = 0; i < programProperties.length; i++)
        {
            output.append(names[i]).append("\n").append(DELIMITER).append("\n");
            output.append(programProperties[i].toString());
            output.append("\n").append(DELIMITER).append("\n");
        }
        return output.toString();
    }
}
