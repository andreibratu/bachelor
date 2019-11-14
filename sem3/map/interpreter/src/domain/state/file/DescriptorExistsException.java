package domain.state.file;

public class DescriptorExistsException extends Exception
{
    public DescriptorExistsException(String filePath)
    {
        super("A file descriptor is already associated with " + filePath);
    }
}
