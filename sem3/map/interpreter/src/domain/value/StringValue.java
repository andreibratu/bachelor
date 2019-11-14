package domain.value;

import domain.type.IType;
import domain.type.StringType;
import domain.type.IllegalComparisonException;

public class StringValue implements IValue<String>
{
    private String value;

    public StringValue(String value)
    {
        this.value = value;
    }

    public StringValue() { this.value = new StringType().defaultValue().value; }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public String getValue() {
        return this.value;
    }

    public void setValue(String value) { this.value = value; }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        StringValue clone = (StringValue) super.clone();
        clone.value = this.value;
        return clone;
    }

    @Override
    public String toString() {
        return this.value;
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof StringValue))
            throw new IllegalComparisonException(this, obj);
        return this.value.equals(((StringValue) obj).value);
    }

    @Override
    public int compareTo(Object o) {
        throw new IllegalComparisonException(this, this.getType().toString());
    }
}
