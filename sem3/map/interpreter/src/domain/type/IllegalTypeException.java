package domain.type;

import domain.type.IType;

public class IllegalTypeException extends Exception
{
    public IllegalTypeException(String descriptor, IType expected, IType actual)
    {
        super(descriptor + ": expected type " + expected + ", got " + actual);
    }

    public IllegalTypeException(String descriptor) { super(descriptor); }
}
