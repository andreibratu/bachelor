package domain.statement;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.expression.Expression;
import domain.state.ProgramState;
import exception.type.IllegalTypeException;
import domain.type.Type;
import domain.value.Value;
import exception.variable.UndeclaredVariableException;

public class AssignmentStatement implements IStatement
{
    private String id;
    private Expression expression;

    public AssignmentStatement(String id, Expression expression)
    {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return this.id + " = " + this.expression.toString();
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        Value expressionValue = expression.evaluate(symbolTable);
        try
        {
            Type type = symbolTable.lookUp(id).getType();
            if (expressionValue.getType().equals(type)) symbolTable.put(id, expressionValue);
            else throw new IllegalTypeException(id, type, expressionValue.getType());
            return state;
        }
        catch(InvalidKeyException e)
        {
            throw new UndeclaredVariableException(id);
        }
    }

    @Override
    public IStatement deepCopy() {
        return new AssignmentStatement(this.id, this.expression);
    }
}
