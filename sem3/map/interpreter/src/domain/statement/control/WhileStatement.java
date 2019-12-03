package domain.statement.control;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.BoolType;
import domain.type.IllegalTypeException;
import domain.value.BoolValue;
import domain.value.IValue;

import java.util.Stack;

public class WhileStatement implements IStatement
{
    private IExpression condition;
    private IStatement innerStatement;

    WhileStatement(IExpression condition, IStatement innerStatement)
    {
        this.condition = condition;
        this.innerStatement = innerStatement;
    }

    @Override
    public String toString() {
        return "( while( " + condition.toString() + " ) " + innerStatement.toString() + " )";
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();
        Stack<IStatement> executionStack = state.getExecutionStack();

        IValue result = condition.evaluate(symbolTable, heap);
        if(!(result instanceof BoolValue))
            throw new IllegalTypeException(this.toString(), new BoolType(), result.getType());

        if(((BoolValue) result).getValue())
        {
            executionStack.push(this);
            executionStack.push(innerStatement);
        }
        return null;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        WhileStatement clone = (WhileStatement) super.clone();
        clone.innerStatement = (IStatement) this.innerStatement.clone();
        clone.condition = (IExpression) this.condition.clone();
        return clone;
    }
}
