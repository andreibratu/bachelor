package model.value;

import model.type.Type;

public interface Value<T> {
    Type getType();

    T getValue();
}
