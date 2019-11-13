package domain.type;

import domain.value.BoolValue;

public class BoolType implements IType {
    @Override
    public boolean equals(Object obj) {
        return obj instanceof BoolType;
    }

    @Override
    public String toString() {
        return "bool";
    }

    @Override
    public BoolValue defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
