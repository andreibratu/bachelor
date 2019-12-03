package repository;

import domain.state.ProgramState;

import java.util.List;

public interface IRepository
{
    List<ProgramState> getProgramList();

    void setProgramList(List<ProgramState> programStateList);

    void logProgramExecution(ProgramState state);
}
