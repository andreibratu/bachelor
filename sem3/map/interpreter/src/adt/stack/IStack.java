package adt.stack;

public interface IStack<T> extends Cloneable{
    void push(T elem);

    T pop();

    T peek();

    boolean isEmpty();

    int size();

    String toString();

    Object clone() throws CloneNotSupportedException;
}
