package domain.expression;

import domain.state.heap.IHeap;
import domain.state.symbol.ISymbolTable;
import domain.value.IValue;

public class ValueExpression implements IExpression {
    private IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    public IValue getValue() {
        return value;
    }

    public void setValue(IValue value) { this.value = value;}

    @Override
    public String toString() { return this.value.toString(); }

    @Override
    public IValue evaluate(ISymbolTable table, IHeap heap) {
        return this.value;
    }

    @Override
    public IExpression clone() throws CloneNotSupportedException {
        ValueExpression clone = (ValueExpression) super.clone();
        clone.value = (IValue) this.value.clone();
        return clone;
    }
}
