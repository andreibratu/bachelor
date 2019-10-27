package adt;

public interface IStack<T1> {
    void push(T1 elem);

    T1 pop();

    boolean isEmpty();

    int size();

    String toString();
}
