package adt.dictionary;

public interface IDictionary<K, V> extends Cloneable {
    void put(K key, V value) throws NullPointerException;

    V lookUp(K key) throws InvalidKeyException;

    boolean isDefined(K key);

    String toString();

    void remove(K key) throws InvalidKeyException;

    Object clone() throws CloneNotSupportedException;
}
