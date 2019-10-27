package repository;

import domain.state.ProgramState;

public interface IRepository {
    ProgramState getCurrentProgram();

    public void addProgram(ProgramState state);
}
