package model.expression;

import model.operator.LogicalOperator;
import model.value.Value;

import java.util.Dictionary;

public class LogicalExpression implements Expression {
    Expression first;
    Expression second;
    LogicalOperator logicalOperator;

    @Override
    public Value evaluate(Dictionary<String, Value> table) {
        return null;
    }
}
