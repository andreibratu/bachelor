package domain.expression;

import adt.IDictionary;
import domain.value.Value;

public class VariableExpression implements Expression {
    private String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table) {
        return table.lookUp(this.id);
    }
}
