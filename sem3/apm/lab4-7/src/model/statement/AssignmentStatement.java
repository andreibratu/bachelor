package model.statement;

import model.expression.Expression;
import model.program.ProgramState;
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
    public ProgramState execute(ProgramState state) throws Exception
    {
        Stack<Statement> stack = state.getExecutionStack();
        HashMap<String, Value> symbolTable = state.getSymbolTable();
        Value value = expression.evaluate(symbolTable);
        if (symbolTable.containsKey(id))
        {
            Type typeId = (symbolTable.get(id)).getType();
            if (value.getType().equals(typeId)) symbolTable.put(id, value);
            else throw new Exception(
                "Declared type of variable " +
                id +
                " and type of assigned expression do not match");
        }
        else throw new Exception("Variable " + id + " was not used before");
        return state;
    }
}
