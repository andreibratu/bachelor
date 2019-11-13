package domain.type;

import domain.value.StringValue;

public class StringType implements IType
{
    @Override
    public StringValue defaultValue() {
        return new StringValue("");
    }

    @Override
    public boolean equals(Object obj) {
        return (obj instanceof StringType);
    }

    @Override
    public String toString() {
        return "string";
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
