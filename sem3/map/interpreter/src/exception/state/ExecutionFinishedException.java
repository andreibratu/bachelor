package exception.state;

public class ExecutionFinishedException extends Exception
{
    public ExecutionFinishedException()
    {
        super("Program successfully finished.");
    }
}
