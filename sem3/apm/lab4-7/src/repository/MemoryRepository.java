package repository;

import domain.state.ProgramState;

import java.util.LinkedList;
import java.util.Queue;

public class MemoryRepository implements IRepository
{
    private Queue<ProgramState> states;

    public MemoryRepository()
    {
        this.states = new LinkedList<>();
    }

    @Override
    public ProgramState getCurrentProgram()
    {
        return this.states.poll();
    }

    @Override
    public void addProgram(ProgramState state)
    {
        this.states.add(state);
    }
}
