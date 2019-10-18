package repository;

import model.program.ProgramState;

import java.util.ArrayList;
import java.util.List;

public class MemoryRepository implements IRepository
{
    private List<ProgramState> states;

    public MemoryRepository()
    {
        this.states = new ArrayList<>();
    }

    @Override
    public ProgramState getCurrentProgram() throws RepositoryEmptyException
    {
        try {
            return this.states.get(this.states.size() - 1);
        }
        catch(IndexOutOfBoundsException e) {
            throw new RepositoryEmptyException();
        }
    }
}
