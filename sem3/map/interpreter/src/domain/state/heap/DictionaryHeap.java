package domain.state.heap;

import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.HashMap;
import java.util.Map;

public class DictionaryHeap implements IHeap
{
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
    public void write(ReferenceValue reference, IValue value) throws InvalidMemoryAddressException
    {
        if(!this.heap.containsKey(reference.getValue()))
            throw new InvalidMemoryAddressException(reference.toString(), reference.getValue());
        this.heap.put(reference.getValue(), value);
    }

    public HashMap<Integer, IValue> getContent()
    {
        HashMap<Integer, IValue> clone = new HashMap<>();
        for(Map.Entry entry : heap.entrySet())
        {
            Integer key = (Integer) entry.getKey();
            IValue value = null;
            try
            {
                value = (IValue) ((IValue) entry.getValue()).clone();
            } catch (CloneNotSupportedException e)
            {
                e.printStackTrace();
            }
            clone.put(key, value);
        }
        return clone;
    }

    public void setContent(HashMap<Integer, IValue> hashMap)
    {
        this.heap = hashMap;
    }

    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        for(Map.Entry entry : heap.entrySet())
        {
            builder.append(entry.getKey().toString()).append(" -> ").append(entry.getValue().toString()).append("\n");
        }
        return builder.toString();
    }

    @Override
    protected Object clone() throws CloneNotSupportedException
    {
        DictionaryHeap clone = (DictionaryHeap) super.clone();
        for(Map.Entry entry : heap.entrySet())
        {
            Integer key = (Integer) entry.getKey();
            IValue value = (IValue) ((IValue) entry.getValue()).clone();
            clone.heap.put(key, value);
        }
        return clone;
    }
}
