package domain.expression;

import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.ReferenceValue;
import domain.type.IllegalTypeException;

public class ReadHeapExpression implements IExpression
{
    private IExpression expression;

    public ReadHeapExpression(IExpression expression)
    {
        this.expression = expression;
    }

    @Override
    public IValue evaluate(ISymbolTable table, IHeap heap)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        IValue result = expression.evaluate(table, heap);
        if(!(result instanceof ReferenceValue))
            throw new IllegalTypeException(this.toString(), result.getType(), new ReferenceType(null));
        return heap.dereference(((ReferenceValue) result));
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ReadHeapExpression clone = (ReadHeapExpression) super.clone();
        clone.expression = (IExpression) expression.clone();
        return clone;
    }
}
