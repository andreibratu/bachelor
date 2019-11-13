package domain.value;

import domain.type.BoolType;
import domain.type.IType;
import exception.type.IllegalComparisonException;

public class BoolValue implements IValue<Boolean> {
    private boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    public BoolValue() { this.value = new BoolType().defaultValue().value; }

    @Override
    public Boolean getValue() {
        return this.value;
    }

    public void setValue(boolean value) { this.value = value; }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        BoolValue clone = (BoolValue) super.clone();
        clone.value = this.value;
        return clone;
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof BoolValue))
            throw new IllegalComparisonException(this, obj);
        return this.value == ((BoolValue) obj).value;
    }

    @Override
    public int compareTo(Object o) {
        throw new IllegalComparisonException(this, o.getClass().toString());
    }
}
