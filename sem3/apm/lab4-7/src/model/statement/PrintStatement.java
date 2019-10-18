package model.statement;

import model.expression.Expression;
import model.program.ProgramState;
import model.statement.Statement;

public class PrintStatement implements Statement
{
    private Expression expression;

    PrintStatement(Expression expression)
    {
        this.expression = expression;
    }

    public String toString() {
        return "print("+expression.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state) {
        //...
        return state;
    }
}
