package domain.expression;

import adt.dictionary.IDictionary;
import domain.operator.LogicalOperator;
import domain.type.BoolType;
import exception.type.IllegalTypeException;
import domain.type.IntegerType;
import domain.type.IType;
import domain.value.BoolValue;
import domain.value.IntegerValue;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public class LogicalExpression implements IExpression
{
    private IExpression first;
    private IExpression second;
    private LogicalOperator operator;

    public LogicalExpression(IExpression first, IExpression second, LogicalOperator operator)
    {
        this.first = first;
        this.second = second;
        this.operator = operator;
    }

    @Override
    public IValue evaluate(IDictionary<String, IValue> table) throws IllegalTypeException, UndeclaredVariableException
    {
        IValue v1 = first.evaluate(table);
        IType type1 = v1.getType();
        IValue v2 = second.evaluate(table);
        IType type2 = v2.getType();
        boolean result = false;
        switch (this.operator)
        {
            case EQUAL:
            case DIFFERENT:
                if (!v1.getType().equals(v2.getType()))
                    throw new IllegalTypeException(this.toString(), v1.getType(), v2.getType());
                break;
            case GT:
            case GTE:
            case ST:
            case STE:
                if (!type1.equals(new IntegerType()))
                    throw new IllegalTypeException(this.toString(), new IntegerType(), type1);
                if (!type2.equals(new IntegerType()))
                    throw new IllegalTypeException(this.toString(), new IntegerType(), type2);
                break;
            case AND:
            case OR:
                if (!type1.equals(new BoolType()))
                    throw new IllegalTypeException(this.toString(), new BoolType(), type1);
                if (!type2.equals(new BoolType()))
                    throw new IllegalTypeException(this.toString(), new BoolType(), type2);
                break;
        }
        switch (this.operator)
        {
            case EQUAL:
                result = v1.getValue().equals(v2.getValue());
                break;
            case DIFFERENT:
                result = !v1.getValue().equals(v2.getValue());
                break;
            case GT:
                result = ((IntegerValue)v1).getValue() > ((IntegerValue)v2).getValue();
                break;
            case GTE:
                result = ((IntegerValue)v1).getValue() >= ((IntegerValue)v2).getValue();
                break;
            case ST:
                result = ((IntegerValue)v1).getValue() < ((IntegerValue)v2).getValue();
                break;
            case STE:
                result = ((IntegerValue)v1).getValue() <= ((IntegerValue)v2).getValue();
                break;
            case AND:
                result = ((BoolValue)v1).getValue() && ((BoolValue)v2).getValue();
                break;
            case OR:
                result = ((BoolValue)v1).getValue() || ((BoolValue)v2).getValue();
                break;
        }
        return new BoolValue(result);
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        LogicalExpression clone = (LogicalExpression) super.clone();
        clone.first = (IExpression) this.first.clone();
        clone.second = (IExpression) this.second.clone();
        clone.operator = this.operator;
        return clone;
    }
}
