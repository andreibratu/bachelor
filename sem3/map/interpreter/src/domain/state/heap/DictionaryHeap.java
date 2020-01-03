package domain.state.heap;

import domain.type.IType;
import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.HashMap;
import java.util.Map;

public class DictionaryHeap
{
    private Map<Integer, IValue<?>> dictionary;
    private int heapFreeAddress;

    public DictionaryHeap() {
        this.heapFreeAddress = 1;
        this.dictionary = new HashMap<>();
    }

    public int allocate(IValue<?> value)
    {
        this.dictionary.put(heapFreeAddress, value);
        return heapFreeAddress++;
    }

    public int allocate(IType type)
    {
        this.dictionary.put(heapFreeAddress, type.defaultValue());
        return heapFreeAddress++;
    }

    public IValue<?> dereference(ReferenceValue reference) throws InvalidMemoryAddressException
    {
        if(!this.dictionary.containsKey(reference.getValue()))
            throw new InvalidMemoryAddressException(reference.toString(), reference.getValue());
        return this.dictionary.get(reference.getValue());
    }

    public void write(ReferenceValue reference, IValue<?> value) throws InvalidMemoryAddressException
    {
        if(!this.dictionary.containsKey(reference.getValue()))
            throw new InvalidMemoryAddressException(reference.toString(), reference.getValue());
        this.dictionary.put(reference.getValue(), value);
    }

    public HashMap<Integer, IValue<?>> getContent()
    {
        HashMap<Integer, IValue<?>> clone = new HashMap<>();
        for(Map.Entry<Integer, IValue<?>> entry : dictionary.entrySet())
        {
            Integer key = entry.getKey();
            IValue<?> value = null;
            try
            {
                value = (IValue<?>) (entry.getValue()).clone();
            } catch (CloneNotSupportedException e)
            {
                e.printStackTrace();
            }
            clone.put(key, value);
        }
        return clone;
    }

    public void setContent(HashMap<Integer, IValue<?>> hashMap)
    {
        this.dictionary = hashMap;
    }

    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("HEAP\n");
        for(Map.Entry<Integer, IValue<?>> entry : dictionary.entrySet())
        {
            builder.append(entry.getKey().toString()).append(" -> ").append(entry.getValue().toString()).append("\n");
        }
        return builder.toString();
    }

    @Override
    protected Object clone() throws CloneNotSupportedException
    {
        DictionaryHeap clone = (DictionaryHeap) super.clone();
        for(Map.Entry<Integer, IValue<?>> entry : dictionary.entrySet())
        {
            Integer key = entry.getKey();
            IValue<?> value = (IValue<?>) (entry.getValue()).clone();
            clone.dictionary.put(key, value);
        }
        return clone;
    }

    public Map<Integer, IValue<?>> getDictionary() { return dictionary; }
}
