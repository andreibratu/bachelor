package exception.io;

public class FileDoesNotExistException extends Exception
{
    public FileDoesNotExistException(String filepath)
    {
        super("File " + filepath + " does not exist");
    }
}
