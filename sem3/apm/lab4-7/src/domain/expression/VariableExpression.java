package domain.expression;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.value.Value;
import exception.variable.UndeclaredVariableException;

public class VariableExpression implements Expression
{
    private String variableName;

    public VariableExpression(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public String toString() { return this.variableName; }

    @Override
    public Value evaluate(IDictionary<String, Value> table) throws UndeclaredVariableException
    {
        try {
            return table.lookUp(this.variableName);
        } catch (InvalidKeyException e) {
            throw new UndeclaredVariableException(this.variableName);
        }
    }

    @Override
    public Expression deepCopy() {
        return new VariableExpression(variableName);
    }
}
