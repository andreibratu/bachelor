package domain.statement;

import domain.state.ProgramState;
import exception.io.DescriptorExistsException;
import exception.io.DescriptorNotExistsException;
import exception.io.FileDoesNotExistException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;

import java.io.IOException;

public interface IStatement extends Cloneable
{
    ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException,
            VariableAlreadyDefinedException, DescriptorExistsException, FileDoesNotExistException, DescriptorNotExistsException, IOException;

    Object clone() throws CloneNotSupportedException;
}
