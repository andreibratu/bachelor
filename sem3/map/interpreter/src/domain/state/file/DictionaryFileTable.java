package domain.state.file;

import domain.value.StringValue;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class DictionaryFileTable implements IFileTable
{
    private Map<String, BufferedReader> dictionary;

    public DictionaryFileTable()
    {
        this.dictionary = new HashMap<>();
    }

    @Override
    public void createDescriptor(StringValue filename)
            throws DescriptorExistsException, FileNotFoundException
    {
        String filepath = filename.getValue();
        if (dictionary.containsKey(filepath))
            throw new DescriptorExistsException(filepath);
        FileReader reader = new FileReader(filepath);
        BufferedReader buffered = new BufferedReader(reader);
        dictionary.put(filename.getValue(), buffered);
    }

    @Override
    public BufferedReader getDescriptor(StringValue filename) throws DescriptorNotExistsException
    {
        String filepath = filename.getValue();
        if (!dictionary.containsKey(filepath))
            throw new DescriptorNotExistsException(filepath);
        return dictionary.get(filepath);
    }

    @Override
    public void closeDescriptor(StringValue filename)
            throws DescriptorNotExistsException, IOException
    {
        String filepath = filename.getValue();
        if (!dictionary.containsKey(filepath))
            throw new DescriptorNotExistsException(filepath);
        dictionary.get(filepath).close();
        this.dictionary.remove(filepath);
    }
}
