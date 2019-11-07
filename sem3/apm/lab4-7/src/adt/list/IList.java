package adt.list;

public interface IList<T>
{
    void add(T element);

    void delete(T element) throws EmptyListException;

    int size();

    T get(int index);

    String toString();
}
