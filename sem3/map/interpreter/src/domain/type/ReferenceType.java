package domain.type;

import domain.value.IValue;
import domain.value.ReferenceValue;

public class ReferenceType implements IType {
    private IType inner;

    public ReferenceType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return this.inner;
    }

    public boolean equals(Object another) {
        if (another instanceof ReferenceType)
            return inner.equals(((ReferenceType) another).getInner());
        return false;
    }

    @Override
    public String toString() {
        if (inner == null) return "&";
        return inner.toString()+"&";
    }

    public IValue defaultValue() { return new ReferenceValue(0, inner);}

    @Override
    public Object clone() throws CloneNotSupportedException {
        ReferenceType clone = (ReferenceType) super.clone();
        clone.inner = (IType) this.inner.clone();
        return clone;
    }
}
