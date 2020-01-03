package domain.expression;

import domain.state.heap.DictionaryHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.type.IType;
import domain.type.IllegalTypeException;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.Map;

public class ReadHeapExpression implements IExpression
{
    private IExpression expression;

    public ReadHeapExpression(IExpression expression)
    {
        this.expression = expression;
    }

    @Override
    public IValue<?> evaluate(DictSymbolTable table, DictionaryHeap heap)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        IValue<?> result = expression.evaluate(table, heap);
        if(!(result instanceof ReferenceValue))
            throw new IllegalTypeException(this.toString(), result.getType(), new ReferenceType(null));
        return heap.dereference(((ReferenceValue) result));
    }

    @Override
    public IType typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType type = expression.typeCheck(typeEnv);
        if(type instanceof ReferenceType)
            return ((ReferenceType) type).getInnerType();
        throw new IllegalTypeException(this.toString(), new ReferenceType(null), type);
    }

    @Override
    public String toString()
    {
        return "*(" + expression.toString() + ")";
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ReadHeapExpression clone = (ReadHeapExpression) super.clone();
        clone.expression = (IExpression) expression.clone();
        return clone;
    }
}
