package domain.type;

import domain.value.IValue;
import domain.value.ReferenceValue;

public class ReferenceType implements IType {
    private IType innerType;

    public ReferenceType(IType innerType) {
        this.innerType = innerType;
    }

    public IType getInnerType() {
        return this.innerType;
    }

    public boolean equals(Object another) {
        if (another instanceof ReferenceType)
            return innerType.equals(((ReferenceType) another).getInnerType());
        return false;
    }

    @Override
    public String toString() {
        if (innerType == null) return "&";
        return innerType.toString()+"&";
    }

    public IValue<?> defaultValue() { return new ReferenceValue(0, innerType);}

    @Override
    public Object clone() throws CloneNotSupportedException {
        ReferenceType clone = (ReferenceType) super.clone();
        clone.innerType = (IType) this.innerType.clone();
        return clone;
    }
}
