package controller;

import domain.state.ProgramState;
import exception.state.ExecutionFinishedException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;

public interface IController {
     ProgramState oneStep(ProgramState state)
        throws ExecutionFinishedException, VariableAlreadyDefinedException,
        UndeclaredVariableException, IllegalTypeException;

     void allSteps();
}
