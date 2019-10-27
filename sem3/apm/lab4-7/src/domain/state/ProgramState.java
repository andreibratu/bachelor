package domain.state;

import adt.IDictionary;
import adt.IList;
import adt.IStack;
import domain.statement.IStatement;
import domain.value.Value;

public class ProgramState {
    private IStack<IStatement> executionStack;
    private IDictionary<String, Value> symbolTable;
    private IList<Value> out;
    private IStatement originalProgram;

    public ProgramState(IStack<IStatement> executionStack, IDictionary<String, Value> symbolTable,
                        IList<Value> out, IStatement originalProgram) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.executionStack.push(this.originalProgram);
    }

    public IStack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public IDictionary<String, Value> getSymbolTable() {
        return this.symbolTable;
    }

    public IList<Value> getOut() {
        return this.out;
    }
}
