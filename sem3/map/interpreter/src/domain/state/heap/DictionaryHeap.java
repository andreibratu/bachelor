package domain.state.heap;

import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.HashMap;
import java.util.Map;

public class DictionaryHeap implements IHeap {
    private Map<Integer, IValue> heap;
    private int heapFreeAddress;

    public DictionaryHeap() {
        this.heapFreeAddress = 1;
        this.heap = new HashMap<>();
    }

    public ReferenceValue allocate(IValue value)
    {
        this.heap.put(this.heapFreeAddress, value);
        return new ReferenceValue(this.heapFreeAddress++, value.getType());
    }

    @Override
    public IValue dereference(ReferenceValue reference) throws InvalidMemoryAddressException
    {
        if(!this.heap.containsKey(reference.getValue()))
            throw new InvalidMemoryAddressException(reference.toString(), reference.getValue());
        return this.heap.get(reference.getValue());
    }

    @Override
    public void write(ReferenceValue reference, IValue value) throws InvalidMemoryAddressException {
        if(!this.heap.containsKey(reference.getValue()))
            throw new InvalidMemoryAddressException(reference.toString(), reference.getValue());
        this.heap.put(reference.getValue(), value);
    }
}
