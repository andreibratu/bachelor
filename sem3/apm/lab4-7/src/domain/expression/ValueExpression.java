package domain.expression;

import adt.dictionary.IDictionary;
import domain.value.Value;

public class ValueExpression implements Expression {
    private Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    public Value getValue() {
        return value;
    }

    @Override
    public String toString() { return this.value.toString(); }

    @Override
    public Value evaluate(IDictionary<String, Value> table) {
        return this.value;
    }

    @Override
    public Expression deepCopy() {
        return new ValueExpression(value.deepCopy());
    }
}
