package repository;

import domain.state.ProgramState;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class Repository implements IRepository
{
    private final ObservableList<ProgramState> programStateList;
    private final String logFilepath;

    public Repository(ProgramState program, String logFilepath)
    {
        this.programStateList = FXCollections.observableArrayList(program);
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
        this.programStateList.setAll(programStateList);
    }

    @Override
    public void logProgramExecution(ProgramState state)
    {
        try
        {
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
