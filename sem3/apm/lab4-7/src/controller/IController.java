package controller;

import domain.state.ProgramState;

public interface IController {
     ProgramState oneStep(ProgramState state) throws Exception;
}
