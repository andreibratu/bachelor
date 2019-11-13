package domain.value;

import domain.type.IType;

public interface IValue<T> extends Cloneable, Comparable {
    IType getType();

    T getValue();

    Object clone() throws CloneNotSupportedException;
}
