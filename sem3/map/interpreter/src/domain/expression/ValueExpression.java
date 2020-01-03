package domain.expression;

import domain.state.heap.DictionaryHeap;
import domain.state.symbol.DictSymbolTable;
import domain.type.IType;
import domain.value.IValue;

import java.util.Map;

public class ValueExpression implements IExpression
{
    private IValue<?> value;

    public ValueExpression(IValue<?> value) {
        this.value = value;
    }

    public IValue<?> getValue() {
        return value;
    }

    public void setValue(IValue<?> value) { this.value = value;}

    @Override
    public IType typeCheck(Map<String, IType> typeEnv) { return value.getType(); }

    @Override
    public String toString() { return this.value.toString(); }

    @Override
    public IValue<?> evaluate(DictSymbolTable table, DictionaryHeap heap) {
        return this.value;
    }

    @Override
    public IExpression clone() throws CloneNotSupportedException {
        ValueExpression clone = (ValueExpression) super.clone();
        clone.value = (IValue<?>) this.value.clone();
        return clone;
    }
}
