package domain.statement;

import adt.dictionary.IDictionary;
import domain.state.ProgramState;
import domain.value.Value;
import exception.variable.VariableAlreadyDefinedException;

public class VariableDeclarationStatement implements IStatement {
    private String name;
    private Value value;

    public VariableDeclarationStatement(String name, Value value)
    {
        this.name = name;
        this.value = value;
    }

    @Override
    public String toString() { return name + " = " + value.toString(); }

    @Override
    public ProgramState execute(ProgramState state) throws VariableAlreadyDefinedException
    {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.isDefined(this.name)) throw new VariableAlreadyDefinedException(name);
        symbolTable.put(name, value);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new VariableDeclarationStatement(name, value.deepCopy());
    }
}
