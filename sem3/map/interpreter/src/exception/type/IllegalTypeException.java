package exception.type;

import domain.type.IType;

public class IllegalTypeException extends Exception
{
    public IllegalTypeException(String descriptor, IType type1, IType type2)
    {
        super(descriptor + " expected type " + type1 + ", got " + type2);
    }
}
