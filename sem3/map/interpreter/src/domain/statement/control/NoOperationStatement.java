package domain.statement.control;

import domain.state.ProgramState;
import domain.statement.IStatement;

public class NoOperationStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
