package domain.type;

import domain.value.IValue;

public class IllegalComparisonException extends RuntimeException {
    public IllegalComparisonException(IValue<?> val1, Object val2)
    {
        super("Illegal comparison: " + val1 + " of type " + val1.getClass()
                + ", and " + val2 + " of type " + val2.getClass());
    }
}
