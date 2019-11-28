package repository;
import domain.state.ProgramState;

import java.io.FileWriter;
import java.io.IOException;

public class Repository implements IRepository
{
    private ProgramState program;
    private String logFilepath;

    public Repository(ProgramState program, String logFilepath)
    {
        this.program = program;
        this.logFilepath = logFilepath;
    }

    @Override
    public ProgramState getProgram()
    {
        return this.program;
    }

    @Override
    public void setProgram(ProgramState program) { this.program = program; }

    @Override
    public void logProgramExecution()
    {
        try {
            // Log current program state
            FileWriter writer = new FileWriter(this.logFilepath, true);
            writer.write(this.program.toString());
            writer.write("\n\n\n");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
