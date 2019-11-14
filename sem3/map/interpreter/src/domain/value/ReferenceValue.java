package domain.value;

import domain.type.IType;
import domain.type.ReferenceType;
import domain.type.IllegalComparisonException;

public class ReferenceValue implements IValue<Integer> {

    private int address;
    private IType locationType;

    public ReferenceValue(int address, IType locationType)
    {
        this.address = address;
        this.locationType = locationType;
    }

    public ReferenceValue(IType locationType)
    {
        ReferenceValue defaultVal = (ReferenceValue) new ReferenceType(locationType).defaultValue();
        this.address = defaultVal.address;
        this.locationType = defaultVal.locationType;
    }

    @Override
    public IType getType() {
        return new ReferenceType(locationType);
    }

    @Override
    public Integer getValue() {
        return address;
    }

    public void setValue(Integer address)
    {
        this.address = address;
    }

    public IType getLocationType() {
        return locationType;
    }

    @Override
    public int compareTo(Object o) {
        throw new IllegalComparisonException(this, o.getClass().toString());
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        ReferenceValue clone = (ReferenceValue) super.clone();
        clone.address = address;
        clone.locationType = (IType) locationType.clone();
        return clone;
    }
}
