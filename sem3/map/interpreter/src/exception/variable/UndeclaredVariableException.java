package exception.variable;

public class UndeclaredVariableException extends Exception
{
    public UndeclaredVariableException(String varName)
    {
        super("Undeclared variable " + varName + "!");
    }
}
