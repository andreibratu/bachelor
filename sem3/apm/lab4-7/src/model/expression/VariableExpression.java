package model.expression;

import model.value.Value;

import java.util.Dictionary;

public class VariableExpression implements Expression {
    private String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    @Override
    public Value evaluate(Dictionary<String, Value> table) {
        return table.get(this.id);
    }
}
