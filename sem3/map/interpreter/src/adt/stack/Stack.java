package adt.stack;

public class Stack<T> implements IStack<T> {
    private java.util.Stack<T> stack;

    public Stack() {
        this.stack = new java.util.Stack<>();
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

    @Override
    public Object clone() throws CloneNotSupportedException {
        Stack clone = (Stack) super.clone();
        clone.stack = (java.util.Stack) this.stack.clone();
        return clone;
    }
}
