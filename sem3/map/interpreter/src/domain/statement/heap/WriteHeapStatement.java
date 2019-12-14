package domain.statement.heap;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.IllegalTypeException;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.Map;

public class WriteHeapStatement implements IStatement
{
    private String variable;
    private IExpression expression;

    public WriteHeapStatement(String variable, IExpression expression)
    {
        this.variable = variable;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        ISymbolTable table = state.getSymbolTable();
        IHeap heap = state.getHeap();

        IValue<?> varValue = table.queryVariable(variable);

        if(!(varValue instanceof ReferenceValue))
            throw new IllegalTypeException(this.toString(), new ReferenceType(null), varValue.getType());

        IValue<?> result = this.expression.evaluate(table, heap);
        if(!result.getType().equals(((ReferenceValue) varValue).getLocationType()))
            throw new IllegalTypeException(
                    this.toString(),
                    ((ReferenceValue) varValue).getLocationType(),
                    result.getType());

        heap.write((ReferenceValue) varValue, result);
        return state;
    }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType typeVar = typeEnv.get(variable);
        IType typeExpression = expression.typeCheck(typeEnv);
        IType expectedType = new ReferenceType(typeExpression);
        if(!typeVar.equals(expectedType))
            throw new IllegalTypeException(this.toString(), typeVar, expectedType);
        return typeEnv;
    }

    @Override
    public String toString()
    {
        return "*" + variable + " = " + expression.toString();
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        WriteHeapStatement clone = (WriteHeapStatement) super.clone();
        clone.variable = variable;
        clone.expression = (IExpression) this.expression.clone();
        return null;
    }
}
