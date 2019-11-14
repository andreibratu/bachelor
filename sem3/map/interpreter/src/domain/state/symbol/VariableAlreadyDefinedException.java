package domain.state.symbol;

public class VariableAlreadyDefinedException extends Exception
{
    public VariableAlreadyDefinedException(String varName)
    {
        super("Variable " + varName + " is already declared!");
    }
}
