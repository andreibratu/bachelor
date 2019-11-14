package exception.io;

public class DescriptorNotExistsException extends Exception
{
    public DescriptorNotExistsException(String filepath)
    {
        super("No file descriptor associated with " + filepath + ". Is the file opened?");
    }
}
