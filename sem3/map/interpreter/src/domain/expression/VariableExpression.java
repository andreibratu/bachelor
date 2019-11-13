package domain.expression;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public class VariableExpression implements IExpression
{
    private String variableName;

    public VariableExpression(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public String toString() { return this.variableName; }

    @Override
    public IValue evaluate(IDictionary<String, IValue> table) throws UndeclaredVariableException
    {
        try {
            return table.lookUp(this.variableName);
        } catch (InvalidKeyException e) {
            throw new UndeclaredVariableException(this.variableName);
        }
    }

    @Override
    public IExpression clone() throws CloneNotSupportedException {
        VariableExpression clone = (VariableExpression) super.clone();
        clone.variableName = this.variableName;
        return clone;
    }
}
