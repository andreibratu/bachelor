package domain.expression;

import adt.dictionary.IDictionary;
import exception.type.IllegalTypeException;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public interface IExpression extends Cloneable
{
    IValue evaluate(IDictionary<String, IValue> table) throws IllegalTypeException, UndeclaredVariableException;

    Object clone() throws CloneNotSupportedException;
}
