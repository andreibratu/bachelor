package domain.statement.variable;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import exception.type.IllegalTypeException;
import domain.type.IType;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public class VariableAssignmentStatement implements IStatement
{
    private String id;
    private IExpression expression;

    public VariableAssignmentStatement(String id, IExpression expression)
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
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IValue expressionValue = expression.evaluate(symbolTable);
        try
        {
            IType type = symbolTable.lookUp(id).getType();
            if (expressionValue.getType().equals(type)) symbolTable.put(id, expressionValue);
            else throw new IllegalTypeException(id, type, expressionValue.getType());
            return state;
        } catch (InvalidKeyException e) {
            throw new UndeclaredVariableException(id);
        }
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        VariableAssignmentStatement clone = (VariableAssignmentStatement) super.clone();
        clone.id = this.id;
        clone.expression = (IExpression) this.expression.clone();
        return clone;
    }
}
