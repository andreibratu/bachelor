package domain.expression;

import adt.dictionary.IDictionary;
import exception.type.IllegalTypeException;
import domain.value.Value;
import exception.variable.UndeclaredVariableException;

public interface Expression
{
    Value evaluate(IDictionary<String, Value> table) throws IllegalTypeException, UndeclaredVariableException;

    Expression deepCopy();
}
