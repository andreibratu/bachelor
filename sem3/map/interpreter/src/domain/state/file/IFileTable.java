package domain.state.file;

import domain.value.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public interface IFileTable {

    void createDescriptor(StringValue filename) throws DescriptorExistsException, FileNotFoundException;

    BufferedReader getDescriptor(StringValue filename) throws DescriptorNotExistsException;

    void closeDescriptor(StringValue filename) throws DescriptorNotExistsException, IOException;
}
