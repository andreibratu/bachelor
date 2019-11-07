package exception.type;

import domain.type.Type;

public class IllegalTypeException extends Exception {

    public IllegalTypeException(String id, Type expectedType, Type actualType)
    {
        super(
            "Cannot assign to variable " + id +
            " of type " + expectedType.toString() +
            " the evaluation of type " + actualType);
    }

    public IllegalTypeException(Type expectedType, Type actualType)
    {
        super("Expected type " + expectedType + " but got " + actualType);
    }
}
