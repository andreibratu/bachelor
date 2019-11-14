package domain.state.heap;

import domain.value.IValue;
import domain.value.ReferenceValue;

public interface IHeap {
    ReferenceValue allocate(IValue value);

    IValue dereference(ReferenceValue reference) throws InvalidMemoryAddressException;

    void write(ReferenceValue reference, IValue value) throws InvalidMemoryAddressException;
}
