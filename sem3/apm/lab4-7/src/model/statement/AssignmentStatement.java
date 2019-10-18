package model.statement;

import model.expression.Expression;
import model.program.ProgramState;
import model.type.IllegalTypeException;
import model.type.Type;
import model.value.Value;

import java.util.Dictionary;
import java.util.HashMap;
import java.util.Stack;

public class AssignmentStatement implements Statement
{
    private String id;
    private Expression expression;

    AssignmentStatement(String id, Expression expression)
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
        Stack<Statement> stack = state.getExecutionStack();
        HashMap<String, Value> symbolTable = state.getSymbolTable();
        Value expressionValue = expression.evaluate(symbolTable);
        if (symbolTable.containsKey(id))
        {
            Type variableType = (symbolTable.get(id)).getType();
            if (expressionValue.getType().equals(variableType)) symbolTable.put(id, expressionValue);
            else throw new IllegalTypeException(id, variableType, expressionValue.getType());
        }
        else throw new UndeclaredVariableException(id);
        return state;
    }
}
