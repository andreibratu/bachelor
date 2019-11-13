package domain.statement.variable;

import adt.dictionary.IDictionary;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IType;
import domain.value.IValue;
import exception.variable.VariableAlreadyDefinedException;

public class VariableDeclarationStatement implements IStatement {
    private String name;
    private IValue value;

    public VariableDeclarationStatement(String name, IType type)
    {
        this.name = name;
        this.value = type.defaultValue();
    }

    @Override
    public String toString() { return value.getType().toString() + " " + name; }

    @Override
    public ProgramState execute(ProgramState state) throws VariableAlreadyDefinedException
    {
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        if (symbolTable.isDefined(this.name)) throw new VariableAlreadyDefinedException(name);
        symbolTable.put(name, value);
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        VariableDeclarationStatement clone = (VariableDeclarationStatement) super.clone();
        clone.name = this.name;
        clone.value = (IValue) this.value.clone();
        return clone;
    }
}
