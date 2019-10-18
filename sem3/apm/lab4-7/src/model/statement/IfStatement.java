package model.statement;

import model.expression.Expression;
import model.program.ProgramState;

public class IfStatement implements Statement {
    private Expression expression;
    private Statement thenStatement;
    private Statement elseStatement;

    IfStatement(Expression expression, Statement thenStatement, Statement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    public String toString() {
        return "IF (" + expression.toString() + ") " +
                "THEN ( " + thenStatement.toString() + " ) " +
                "ELSE ( " + elseStatement.toString() + ")";
    }

    @Override
    public ProgramState execute(ProgramState state) {
        //...
        return state;
    }
}
