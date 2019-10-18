package model.statement;

import model.program.ProgramState;

public interface Statement {
    ProgramState execute(ProgramState state) throws Exception;
}
