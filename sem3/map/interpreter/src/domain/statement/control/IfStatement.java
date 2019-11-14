package domain.statement.control;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.value.IValue;
import domain.type.IllegalTypeException;

import java.util.Stack;

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
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        Stack<IStatement> exeStack = state.getExecutionStack();
        ISymbolTable symTable = state.getSymbolTable();
        IHeap heap = state.getHeap();
        IValue result = this.expression.evaluate(symTable, heap);
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
