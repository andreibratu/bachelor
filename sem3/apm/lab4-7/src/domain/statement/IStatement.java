package domain.statement;

import domain.state.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState state) throws Exception;
}
