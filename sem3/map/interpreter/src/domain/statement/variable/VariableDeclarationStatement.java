package domain.statement.variable;

import domain.state.ProgramState;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.value.IValue;

import java.util.Map;

public class VariableDeclarationStatement implements IStatement
{
    private String name;
    private IValue<?> value;

    public VariableDeclarationStatement(String name, IType type)
    {
        this.name = name;
        this.value = type.defaultValue();
    }

    public VariableDeclarationStatement(String name, IValue<?> value)
    {
        this.name = name;
        this.value = value;
    }

    @Override
    public String toString() { return value.getType().toString() + " " + name; }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv)
    {
        typeEnv.put(name, value.getType());
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state) throws VariableAlreadyDefinedException
    {
        DictSymbolTable symbolTable = state.getSymbolTable();
        symbolTable.createVariable(name, value);
        return null;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        VariableDeclarationStatement clone = (VariableDeclarationStatement) super.clone();
        clone.name = this.name;
        clone.value = (IValue<?>) this.value.clone();
        return clone;
    }
}
