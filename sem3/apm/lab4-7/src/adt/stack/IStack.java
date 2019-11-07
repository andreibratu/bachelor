package adt.stack;

public interface IStack<T> {
    void push(T elem);

    T pop();

    T peek();

    boolean isEmpty();

    int size();

    String toString();
}
