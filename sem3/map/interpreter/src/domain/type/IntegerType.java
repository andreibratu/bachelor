package domain.type;

import domain.value.IntegerValue;

public class IntegerType implements IType {
    @Override
    public boolean equals(Object obj) {
        return obj instanceof IntegerType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public IntegerValue defaultValue() {
        return new IntegerValue(0);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
