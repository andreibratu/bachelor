package domain.state.symtable;

public class UndeclaredVariableException extends Exception
{
    public UndeclaredVariableException(String varName)
    {
        super("Undeclared variable " + varName + "!");
    }
}
