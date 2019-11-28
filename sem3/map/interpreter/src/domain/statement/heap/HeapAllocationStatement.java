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
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();

        IValue varValue = symbolTable.queryVariable(this.variableName);
        if(!(varValue instanceof ReferenceValue))
            throw new IllegalTypeException(this.toString(), new ReferenceType(null), varValue.getType());

        IValue result = expression.evaluate(symbolTable, heap);
        IType varValueInnerType = ((ReferenceValue) varValue).getLocationType();
        IType resultType = result.getType();
        if (!varValueInnerType.equals(resultType))
            throw new IllegalTypeException(this.toString(), varValueInnerType, resultType);

        varValue = heap.allocate(((ReferenceValue) varValue).getLocationType().defaultValue());
        heap.write((ReferenceValue) varValue, result);
        symbolTable.updateVariable(variableName, varValue);
        return state;
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
