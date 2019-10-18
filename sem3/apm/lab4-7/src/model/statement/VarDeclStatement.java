package model.statement;

import model.program.ProgramState;
import model.type.Type;
import model.value.Value;

import java.util.HashMap;
import java.util.Stack;

public class VarDeclStatement implements Statement {
    private String name;
    private Value value;

    public VarDeclStatement(String name, Value value)
    {
        this.name = name;
        this.value = value;
    }

    @Override
    public ProgramState execute(ProgramState state) throws Exception {
        HashMap<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.containsKey(this.name)) throw new Exception("Variable with given name already exists");
        symbolTable.put(name, value);
        return state;
    }
}
