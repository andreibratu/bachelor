package domain.statement.control;

import adt.dictionary.IDictionary;
import adt.stack.IStack;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import exception.type.IllegalTypeException;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public class IfStatement implements IStatement
{
    private IExpression expression;
    private IStatement thenStatement;
    private IStatement elseStatement;

    IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement)
    {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    public String toString()
    {
        return "IF (" + expression.toString() + ") " +
                "THEN ( " + thenStatement.toString() + " ) " +
                "ELSE ( " + elseStatement.toString() + ")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IStack<IStatement> exeStack = state.getExecutionStack();
        IDictionary<String, IValue> symTable = state.getSymbolTable();
        IValue result = this.expression.evaluate(symTable);
        if(!result.getValue().equals(0))
            exeStack.push(thenStatement);
        else
            exeStack.push(elseStatement);
        return state;
    }

    @Override
    public IStatement clone() throws CloneNotSupportedException {
        IfStatement clone = (IfStatement) super.clone();
        clone.expression = (IExpression) this.expression.clone();
        clone.thenStatement = (IStatement) this.thenStatement.clone();
        clone.elseStatement = (IStatement) this.thenStatement.clone();
        return clone;
    }
}
