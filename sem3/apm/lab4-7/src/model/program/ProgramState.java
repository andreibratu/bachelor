package model.program;

import model.statement.Statement;
import model.value.Value;

import java.util.Dictionary;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

public class ProgramState {
    private Stack<Statement> executionStack;
    private HashMap<String, Value> symbolTable;
    private List<Value> out;
    private Statement originalProgram;

    public ProgramState(Stack<Statement> executionStack, HashMap<String, Value> symbolTable,
                        List<Value> out, Statement originalProgram) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.executionStack.push(this.originalProgram);
    }

    public Stack<Statement> getExecutionStack() {
        return this.executionStack;
    }

    public HashMap<String, Value> getSymbolTable() {
        return this.symbolTable;
    }

    public List<Value> getOut() {
        return this.out;
    }
}
