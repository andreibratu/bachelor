package adt;

import java.util.HashMap;

import javax.management.openmbean.KeyAlreadyExistsException;

public class Dictionary<T1,T2> implements IDictionary<T1,T2> {
    private HashMap<T1,T2> dictionary;

    public Dictionary(){
        this.dictionary = new HashMap<T1,T2>();
    }

    @Override
    public void add(T1 key, T2 value) throws RuntimeException{
        if(key == null || value == null)
            throw new NullPointerException("Map does not support null values!");
        this.dictionary.put(key, value);
    }

    @Override
    public void update(T1 key, T2 value) throws Exception {
        if(key == null || value == null)
            throw new NullPointerException("You can not add null values!");
        if(!this.dictionary.containsKey(key))
            throw new Exception("Key does not exist in the map!");
        this.dictionary.put(key, value);
    }

    @Override
    public T2 lookUp(T1 id) throws Exception {
        if(!this.dictionary.containsKey(id))
            throw new Exception("This element does not exist!");
        return this.dictionary.get(id);
    }

    @Override
    public boolean isDefined(T1 id) {
        return this.dictionary.containsKey(id);
    }

    @Override
    public String toString() {
        StringBuilder printDict = new StringBuilder();
        for (HashMap.Entry<T1,T2> element : this.dictionary.entrySet()) {
            printDict.append("Key: ").append(element.getKey().toString())
                    .append(", Value: ").append(element.getValue().toString()).append("\n");
        }
        return printDict.toString();
    }

}
