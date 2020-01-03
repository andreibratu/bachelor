package domain.statement.fork;

import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.IllegalTypeException;

import java.util.HashMap;
import java.util.Map;

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
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        Map<String, IType> copyInner = new HashMap<>(typeEnv);
        innerStatement.typeCheck(copyInner);
        return typeEnv;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ForkStatement clone = (ForkStatement) super.clone();
        clone.innerStatement = (IStatement) innerStatement.clone();
        return clone;
    }

    @Override
    public String toString() { return "fork( " + innerStatement + " )"; }
}
