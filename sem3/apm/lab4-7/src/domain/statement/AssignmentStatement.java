package domain.statement;

import adt.IDictionary;
import adt.IStack;
import domain.expression.Expression;
import domain.state.ProgramState;
import domain.type.IllegalTypeException;
import domain.type.Type;
import domain.value.Value;

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
        return this.id + "=" + this.expression.toString();
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IStack<IStatement> stack = state.getExecutionStack();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        Value expressionValue = expression.evaluate(symbolTable);
        if (symbolTable.isDefined(id)) {
            Type variableType = (symbolTable.lookUp(id)).getType();
            if (expressionValue.getType().equals(variableType)) symbolTable.add(id, expressionValue);
            else throw new IllegalTypeException(id, variableType, expressionValue.getType());
        } else throw new UndeclaredVariableException(id);
        return state;
    }
}
