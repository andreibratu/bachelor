package domain.state.symbol;

public class UndeclaredVariableException extends Exception
{
    public UndeclaredVariableException(String varName)
    {
        super("Undeclared variable " + varName + "!");
    }
}
