package controller;

import domain.state.ProgramState;
import exception.io.DescriptorExistsException;
import exception.io.DescriptorNotExistsException;
import exception.io.FileDoesNotExistException;
import exception.state.ExecutionFinishedException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;

import java.io.IOException;

public interface IController {
     ProgramState oneStep(ProgramState state)
             throws ExecutionFinishedException, VariableAlreadyDefinedException,
             UndeclaredVariableException, IllegalTypeException, DescriptorExistsException, FileDoesNotExistException, DescriptorNotExistsException, IOException;

     void allSteps() throws VariableAlreadyDefinedException, DescriptorNotExistsException, UndeclaredVariableException, IOException, ExecutionFinishedException, FileDoesNotExistException, DescriptorExistsException, IllegalTypeException;
}
