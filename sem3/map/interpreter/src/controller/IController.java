package controller;

import domain.state.ProgramState;

import java.util.List;

public interface IController {
     List<ProgramState> removeCompletedPrograms();

     void allSteps() throws InterruptedException;
}
