package domain.statement;

class UndeclaredVariableException extends Exception {

    UndeclaredVariableException(String id)
    {
        super("Variable " + id + " was not declared before!");
    }
}
