package controller;

import domain.state.ProgramState;
import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.state.heap.InvalidMemoryAddressException;
import domain.type.IllegalTypeException;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;

import java.io.IOException;

public interface IController {
     ProgramState oneStep(ProgramState state)
             throws VariableAlreadyDefinedException, UndeclaredVariableException,
             IllegalTypeException, DescriptorExistsException, FileDoesNotExistException,
             DescriptorNotExistsException, IOException, InvalidMemoryAddressException;

     void allSteps() throws VariableAlreadyDefinedException, DescriptorNotExistsException,
             UndeclaredVariableException, IOException, FileDoesNotExistException,
             DescriptorExistsException, IllegalTypeException, InvalidMemoryAddressException;
}
