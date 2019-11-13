package domain.expression;

import adt.dictionary.IDictionary;
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
    public IValue evaluate(IDictionary<String, IValue> table) {
        return this.value;
    }

    @Override
    public IExpression clone() throws CloneNotSupportedException {
        ValueExpression clone = (ValueExpression) super.clone();
        clone.value = (IValue) this.value.clone();
        return clone;
    }
}
