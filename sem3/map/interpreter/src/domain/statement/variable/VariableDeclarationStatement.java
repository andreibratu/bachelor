package domain.statement.variable;

import domain.state.ProgramState;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.value.IValue;

public class VariableDeclarationStatement implements IStatement
{
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
        ISymbolTable symbolTable = state.getSymbolTable();
        symbolTable.createVariable(name, value);
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
