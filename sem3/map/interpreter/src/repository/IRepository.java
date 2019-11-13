package repository;

import domain.state.ProgramState;

public interface IRepository
{
    ProgramState getProgram();

    void setProgram(ProgramState state);

    void logProgramExecution();
}
