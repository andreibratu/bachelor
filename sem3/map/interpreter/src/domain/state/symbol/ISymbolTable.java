package domain.state.symbol;

import domain.value.IValue;

public interface ISymbolTable
{
    void createVariable(String variable, IValue value) throws VariableAlreadyDefinedException;

    void updateVariable(String variable, IValue value) throws UndeclaredVariableException;

    IValue queryVariable(String variable) throws UndeclaredVariableException;
}
