package domain.statement;

import domain.state.ProgramState;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.type.IllegalTypeException;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;

import java.io.IOException;

public interface IStatement extends Cloneable
{
    ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException,
            VariableAlreadyDefinedException, DescriptorExistsException, FileDoesNotExistException, DescriptorNotExistsException, IOException, InvalidMemoryAddressException;

    Object clone() throws CloneNotSupportedException;
}
