package adt;

import java.util.HashMap;
import Exception.MyException;
import lombok.Getter;
import lombok.Setter;

import javax.management.openmbean.KeyAlreadyExistsException;

@Getter
@Setter
public class Dictionary<T1,T2> implements IDictionary<T1,T2> {
    private HashMap<T1,T2> dictionary;
    public Dictionary(){
        this.dictionary = new HashMap<T1,T2>();
    }
    @Override
    public void add(T1 t1, T2 t2) throws RuntimeException{
        if(t1 == null || t2 == null)
            throw new NullPointerException("You can not add null values!!!");
        if(this.dictionary.containsKey(t1))
            throw new KeyAlreadyExistsException("This element is already in your map!!!");
        this.dictionary.put(t1, t2);
    }

    @Override
    public void update(T1 t1, T2 t2) throws MyException {
        if(t1 == null || t2 == null)
            throw new NullPointerException("You can not add null values!!!");
        if(!this.dictionary.containsKey(t1))
            throw new MyException("This element is not in your map...You can not update it!!!");
        this.dictionary.put(t1,t2);
    }

    @Override
    public T2 lookUp(T1 id) throws MyException {
        if(!this.dictionary.containsKey(id))
            throw new MyException("This element does not exist!");
        return this.dictionary.get(id);
    }

    @Override
    public boolean isDefined(T1 id) {
        return this.dictionary.containsKey(id);
    }

    @Override
    public String toString() {
        String printDict = "";
        for (HashMap.Entry<T1,T2> element : this.dictionary.entrySet()) {
            printDict = printDict + "Key: " + element.getKey().toString()
                    + ", Value: " + element.getValue().toString() + "\n";
        }
        return printDict;
    }

}
