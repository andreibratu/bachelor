package domain.statement;

import domain.state.ProgramState;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;

public interface IStatement {
    ProgramState execute(ProgramState state)
        throws IllegalTypeException, UndeclaredVariableException, VariableAlreadyDefinedException;

    IStatement deepCopy();
}
