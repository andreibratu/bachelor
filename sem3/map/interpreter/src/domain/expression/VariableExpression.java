package domain.expression;

import domain.state.heap.IHeap;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.type.IType;
import domain.value.IValue;

import java.util.Map;

public class VariableExpression implements IExpression
{
    private String variableName;

    public VariableExpression(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public String toString() { return this.variableName; }

    @Override
    public IType typeCheck(Map<String, IType> typeEnv) { return typeEnv.get(variableName); }

    @Override
    public IValue evaluate(ISymbolTable table, IHeap heap) throws UndeclaredVariableException
    {
        return table.queryVariable(this.variableName);
    }

    @Override
    public IExpression clone() throws CloneNotSupportedException
    {
        VariableExpression clone = (VariableExpression) super.clone();
        clone.variableName = this.variableName;
        return clone;
    }
}
