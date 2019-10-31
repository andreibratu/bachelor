package domain.value;

import domain.type.IntegerType;
import domain.type.Type;

public class IntegerValue implements Value<Integer>
{
    private int value;

    public IntegerValue(int value)
    {
        this.value = value;
    }

    @Override
    public Integer getValue()
    {
        return value;
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    public Type getType() {
        return new IntegerType();
    }

    @Override
    public Value deepCopy() {
        return new IntegerValue(value);
    }
}
