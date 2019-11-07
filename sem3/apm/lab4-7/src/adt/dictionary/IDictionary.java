package adt.dictionary;

public interface IDictionary<K, V> {
    void put(K key, V value) throws NullPointerException;

    V lookUp(K key) throws InvalidKeyException;

    boolean isDefined(K key);

    String toString();
}
