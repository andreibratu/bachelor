package domain.statement.control;

import adt.stack.IStack;
import domain.state.ProgramState;
import domain.statement.IStatement;

public class CompoundStatement implements IStatement
{
    private IStatement first;
    private IStatement second;

    public CompoundStatement(IStatement first, IStatement second)
    {
        this.first = first;
        this.second = second;
    }

    public String toString() {
        return "( " + first.toString() + " ; " + second.toString() + " )";
    }

    @Override
    public ProgramState execute(ProgramState state)
    {
        IStack<IStatement> stack = state.getExecutionStack();
        stack.push(second);
        stack.push(first);
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        CompoundStatement clone = (CompoundStatement) super.clone();
        clone.first = (IStatement) this.first.clone();
        clone.second = (IStatement) this.first.clone();
        return clone;
    }
}
