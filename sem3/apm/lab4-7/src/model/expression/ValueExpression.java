package model.expression;

import model.value.Value;

import java.util.Dictionary;

public class ValueExpression implements Expression {
    private Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    public Value getValue() {
        return value;
    }

    @Override
    public Value evaluate(Dictionary<String, Value> table) {
        return this.value.getValue();
    }
}
