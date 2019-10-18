package controller;

import model.program.ProgramState;
import model.statement.StatementExecutionException;

public interface IController {
     ProgramState step(ProgramState state) throws Exception;
}
