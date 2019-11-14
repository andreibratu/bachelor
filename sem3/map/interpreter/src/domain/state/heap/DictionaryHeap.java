package domain.state;

import adt.dictionary.Dictionary;
import adt.dictionary.IDictionary;
import domain.value.IValue;

public class Heap {
    private IDictionary<Integer, IValue> heap;
    private int heapFreeAddress;

    public Heap() {
        this.heapFreeAddress = 1;
        this.heap = new Dictionary<>();
    }

    public int allocate(IValue value) {
        this.heap.put(this.heapFreeAddress, value);
        return this.heapFreeAddress++;
    }
}
