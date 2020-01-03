package domain.value;

import domain.type.IntegerType;
import domain.type.IType;
import domain.type.IllegalComparisonException;
import org.jetbrains.annotations.NotNull;

@SuppressWarnings("rawtypes")
public class IntegerValue implements IValue<Integer>, Comparable
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

    public IType getType() {
        return new IntegerType();
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        IntegerValue clone = (IntegerValue) super.clone();
        clone.value = this.value;
        return clone;
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof IntegerValue))
            throw new IllegalComparisonException(this, obj);
        return this.value == ((IntegerValue) obj).value;
    }

    @Override
    public int compareTo(@NotNull Object obj) {
        if (!(obj instanceof IntegerValue))
            throw new IllegalComparisonException(this, obj);
        return this.value - ((IntegerValue) obj).value;
    }

    public boolean greaterThenEqual(Object o) {
        return this.compareTo(o) >= 0;
    }

    public boolean different(Object o) {
        return this.compareTo(o) != 0;
    }

    public boolean equal(Object o) {
        return this.compareTo(o) == 0;
    }

    public boolean smallerEqual(Object o) {
        return this.compareTo(o) <= 0;
    }

    public boolean smaller(Object o) {
        return this.compareTo(o) < 0;
    }
}
