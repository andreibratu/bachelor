package domain.state.file;

public class FileDoesNotExistException extends Exception
{
    public FileDoesNotExistException(String filepath)
    {
        super("File " + filepath + " does not exist");
    }
}
