package repository;

import model.program.ProgramState;

public interface IRepository {
    ProgramState getCurrentProgram() throws RepositoryEmptyException;
}
