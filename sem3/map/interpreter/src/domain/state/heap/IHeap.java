package domain.state.heap;

import domain.type.IType;
import domain.value.IValue;
import domain.value.ReferenceValue;

public interface IHeap
{
    int allocate(IValue value);

    int allocate(IType type);

    IValue dereference(ReferenceValue reference) throws InvalidMemoryAddressException;

    void write(ReferenceValue reference, IValue value) throws InvalidMemoryAddressException;
}
