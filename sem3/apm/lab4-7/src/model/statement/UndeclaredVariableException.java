package model.statement;

public class UndeclaredVariableException extends Exception {

    public UndeclaredVariableException(String id)
    {
        super("Variable " + id + " was not declared before");
    }
}
