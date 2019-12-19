package domain.statement;

import domain.state.ProgramState;
import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.type.IType;
import domain.type.IllegalTypeException;

import java.io.IOException;
import java.util.Map;

public interface IStatement extends Cloneable
{
    ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException,
            VariableAlreadyDefinedException, DescriptorExistsException, FileDoesNotExistException,
            DescriptorNotExistsException, IOException, InvalidMemoryAddressException;

    Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException;

    Object clone() throws CloneNotSupportedException;
}
