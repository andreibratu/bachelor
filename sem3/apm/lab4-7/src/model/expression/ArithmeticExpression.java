package model.expression;

import model.operator.ArithmeticOperator;
import model.type.IntegerType;
import model.value.IntegerValue;
import model.value.Value;

import java.util.Dictionary;

public class ArithmeticExpression implements Expression {
    private Expression first;
    private Expression second;
    private ArithmeticOperator arithmeticOperator;

    public ArithmeticExpression(Expression first, Expression second, ArithmeticOperator arithmeticOperator) {
        this.first = first;
        this.second = second;
        this.arithmeticOperator = arithmeticOperator;
    }

    @Override
    public Value evaluate(Dictionary<String, Value> table) throws Exception {
        Value v1, v2;
        v1 = first.evaluate(table);
        v2 = second.evaluate(table);

        if (!v1.getType().equals(new IntegerType())) throw new Exception("First operand is not integer");
        if (!v2.getType().equals(new IntegerType())) throw new Exception("Second operand is not integer");

        int n1 = ((IntegerValue) v1).getValue();
        int n2 = ((IntegerValue) v2).getValue();
        int result = 0;
        switch (this.arithmeticOperator)
        {
            case PLUS:
                result = n1 + n2;
            case MINUS:
                result = n1 - n2;
            case STAR:
                result = n1 * n2;
            case DIVIDE:
                if (n2 == 0) throw new Exception("Division by zero");
                result = n1 / n2;
        }
        return new IntegerValue(result);
    }
}
