package domain.expression;

import domain.operator.ArithmeticOperator;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.type.IntegerType;
import domain.value.IValue;
import domain.value.IntegerValue;
import domain.type.IllegalTypeException;

public class ArithmeticExpression implements IExpression {
    private IExpression first;
    private IExpression second;
    private ArithmeticOperator operator;

    public ArithmeticExpression(IExpression first, IExpression second, ArithmeticOperator operator)
    {
        this.first = first;
        this.second = second;
        this.operator = operator;
    }

    @Override
    public String toString()
    {
        return this.first.toString() + " " + operator.toString() + " " + second.toString();
    }

    @Override
    public IValue evaluate(ISymbolTable table, IHeap heap)
            throws IllegalTypeException, ArithmeticException,
            UndeclaredVariableException, InvalidMemoryAddressException
    {
        IValue v1 = first.evaluate(table, heap);
        IValue v2 = second.evaluate(table, heap);

        if (!v1.getType().equals(new IntegerType()))
            throw new IllegalTypeException(this.toString(), new IntegerType(), v1.getType());
        if (!v2.getType().equals(new IntegerType()))
            throw new IllegalTypeException(this.toString(), new IntegerType(), v2.getType());

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

    @Override
    public Object clone() throws CloneNotSupportedException {
        ArithmeticExpression clone = (ArithmeticExpression) super.clone();
        clone.first = (ArithmeticExpression) this.first.clone();
        clone.second = (ArithmeticExpression) this.second.clone();
        clone.operator = this.operator;
        return clone;
    }
}
