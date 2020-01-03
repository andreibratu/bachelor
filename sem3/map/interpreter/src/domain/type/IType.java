package domain.type;

import domain.value.IValue;

public interface IType extends Cloneable {
    IValue<?> defaultValue();

    Object clone() throws CloneNotSupportedException;
}
