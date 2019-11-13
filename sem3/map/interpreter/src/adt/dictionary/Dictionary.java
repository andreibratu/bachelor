package adt.dictionary;

import java.util.HashMap;

public class Dictionary<K, V> implements IDictionary<K, V> {
    private HashMap<K, V> dictionary;

    public Dictionary(){
        this.dictionary = new HashMap<>();
    }

    @Override
    public void put(K key, V value) throws NullPointerException
    {
        if(key == null || value == null)
            throw new NullPointerException("Map does not support null values!");
        this.dictionary.put(key, value);
    }

    @Override
    public V lookUp(K key) throws InvalidKeyException
    {
        if(!this.dictionary.containsKey(key))
            throw new InvalidKeyException();
        return this.dictionary.get(key);
    }

    @Override
    public boolean isDefined(K key) {
        return this.dictionary.containsKey(key);
    }

    @Override
    public String toString()
    {
        StringBuilder printDict = new StringBuilder();
        for (HashMap.Entry<K, V> element : this.dictionary.entrySet()) {
            printDict.append("Key: ").append(element.getKey().toString())
                    .append(", Value: ").append(element.getValue().toString()).append("\n");
        }
        return printDict.toString();
    }

    @Override
    public void remove(K key) throws InvalidKeyException
    {
        if(!this.dictionary.containsKey(key))
            throw new InvalidKeyException();
        this.dictionary.remove(key);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Dictionary clone = (Dictionary) super.clone();
        clone.dictionary = (HashMap) this.dictionary.clone();
        return clone;
    }
}
