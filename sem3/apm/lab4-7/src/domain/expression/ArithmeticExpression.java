package domain.expression;

import adt.IDictionary;
import domain.operator.ArithmeticOperator;
import domain.type.IllegalTypeException;
import domain.type.IntegerType;
import domain.value.IntegerValue;
import domain.value.Value;

public class ArithmeticExpression implements Expression {
    private Expression first;
    private Expression second;
    private ArithmeticOperator operator;

    public ArithmeticExpression(Expression first, Expression second, ArithmeticOperator operator) {
        this.first = first;
        this.second = second;
        this.operator = operator;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table) throws IllegalTypeException, ArithmeticException {
        Value v1 = first.evaluate(table);
        Value v2 = second.evaluate(table);

        if (!v1.getType().equals(new IntegerType())) throw new IllegalTypeException(new IntegerType(), v1.getType());
        if (!v2.getType().equals(new IntegerType())) throw new IllegalTypeException(new IntegerType(), v2.getType());

        int n1 = ((IntegerValue) v1).getValue();
        int n2 = ((IntegerValue) v2).getValue();
        int result = 0;
        switch (this.operator)
        {
            case PLUS:
                result = n1 + n2;
                break;
            case MINUS:
                result = n1 - n2;
                break;
            case STAR:
                result = n1 * n2;
                break;
            case DIVIDE:
                if (n2 == 0) throw new ArithmeticException("Division by zero");
                result = n1 / n2;
                break;
        }
        return new IntegerValue(result);
    }
}
