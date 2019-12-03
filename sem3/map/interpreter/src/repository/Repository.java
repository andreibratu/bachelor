package repository;
import domain.state.ProgramState;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository
{
    private List<ProgramState> programStateList;
    private String logFilepath;

    public Repository(ProgramState program, String logFilepath)
    {
        this.programStateList = new ArrayList<>();
        this.programStateList.add(program);
        this.logFilepath = logFilepath;
    }

    @Override
    public List<ProgramState> getProgramList()
    {
        return this.programStateList;
    }

    @Override
    public void setProgramList(List<ProgramState> programStateList)
    {
        this.programStateList = programStateList;
    }

    @Override
    public void logProgramExecution(ProgramState state)
    {
        try
        {
            // Log current program state
            FileWriter writer = new FileWriter(this.logFilepath, true);
            writer.write(this.programStateList.toString());
            writer.write("\n\n\n");
            writer.close();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
