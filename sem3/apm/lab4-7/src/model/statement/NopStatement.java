package model.statement;

import model.program.ProgramState;

public class NopStatement implements Statement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }
}
