package domain.statement.heap;


import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.ReferenceValue;
import domain.type.IllegalTypeException;

import java.util.Map;

public class HeapAllocationStatement implements IStatement
{
    private String variableName;
    private IExpression expression;

    public HeapAllocationStatement(String variableName, IExpression expression)
    {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType typeVar = typeEnv.get(variableName);
        IType typeExpression = expression.typeCheck(typeEnv);
        IType expectedType = new ReferenceType(typeExpression);
        if(!typeVar.equals(expectedType))
            throw new IllegalTypeException(this.toString(), typeVar, expectedType);
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();

        IValue<?> varValue = symbolTable.queryVariable(this.variableName);
        if(!(varValue instanceof ReferenceValue))
            throw new IllegalTypeException(this.toString(), new ReferenceType(null), varValue.getType());

        IValue<?> result = expression.evaluate(symbolTable, heap);
        IType varValueInnerType = ((ReferenceValue) varValue).getLocationType();
        IType resultType = result.getType();
        if (!varValueInnerType.equals(resultType))
            throw new IllegalTypeException(this.toString(), varValueInnerType, resultType);

        ((ReferenceValue) varValue).setValue(heap.allocate(result));
        return null;
    }

    @Override
    public String toString()
    {
        return "new( " + variableName + ", " + expression + " )";
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        HeapAllocationStatement clone = (HeapAllocationStatement) super.clone();
        clone.variableName = variableName;
        clone.expression = (IExpression) this.expression.clone();
        return clone;
    }
}
