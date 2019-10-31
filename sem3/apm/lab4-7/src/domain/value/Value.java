package domain.value;

import domain.type.Type;

public interface Value<T> {
    Type getType();

    T getValue();

    Value deepCopy();
}
