package adt.stack;

import java.util.Stack;

public class MyStack<T> implements IStack<T> {
    private Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    @Override
    public void push(T elem) {
        this.stack.push(elem);
    }

    @Override
    public T pop() { return this.stack.pop(); }

    @Override
    public T peek() { return this.stack.peek(); }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public int size() {
        return this.stack.size();
    }


    @Override
    public String toString() {
       StringBuilder printStack = new StringBuilder();
       for (T elem : this.stack)
           printStack.append(elem.toString()).append("\n");
       return printStack.toString();
    }

    public Stack<T> getStack() {
        return this.stack;
    }
}
