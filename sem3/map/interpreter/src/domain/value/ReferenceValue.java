package domain.value;

import domain.type.IType;
import domain.type.ReferenceType;
import exception.type.IllegalComparisonException;

public class ReferenceValue implements IValue {

    private int address;
    private IType locationType;

    public ReferenceValue(int address, IType locationType)
    {
        this.address = address;
        this.locationType = locationType;
    }

    @Override
    public IType getType() {
        return new ReferenceType(this.locationType);
    }

    @Override
    public Object getValue() {
        return this.address;
    }

    @Override
    public int compareTo(Object o) {
        throw new IllegalComparisonException(this, o.getClass().toString());
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        ReferenceValue clone = (ReferenceValue) super.clone();
        clone.address = this.address;
        clone.locationType = (IType) this.locationType.clone();
        return clone;
    }
}
