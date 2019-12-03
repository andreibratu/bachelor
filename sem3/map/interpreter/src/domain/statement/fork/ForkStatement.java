package domain.statement.fork;

import domain.state.ProgramState;
import domain.statement.IStatement;

public class ForkStatement implements IStatement
{
    private IStatement innerStatement;

    public ForkStatement(IStatement innerStatement)
    {
        this.innerStatement = innerStatement;
    }

    @Override
    public ProgramState execute(ProgramState state)
    {
        ProgramState fork = new ProgramState(state);
        fork.getExecutionStack().push(innerStatement);
        return fork;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ForkStatement clone = (ForkStatement) super.clone();
        clone.innerStatement = (IStatement) innerStatement.clone();
        return clone;
    }
}
