package model.expression;

import model.value.Value;

import java.util.Dictionary;
import java.util.HashMap;

public class ValueExpression implements Expression {
    private Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    public Value getValue() {
        return value;
    }

    @Override
    public Value evaluate(HashMap<String, Value> table) {
        return this.value;
    }
}
