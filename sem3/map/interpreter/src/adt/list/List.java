package adt.list;

import java.util.Iterator;
import java.util.LinkedList;

public class List<T> implements IList<T>, Iterable<T>
{
    private LinkedList<T> list;

    public List(){
        this.list = new LinkedList<T>();
    }

    @Override
    public void add(T element){
        this.list.add(element);
    }

    @Override
    public void delete(T element) throws EmptyListException
    {
        if(this.list.isEmpty())
            throw new EmptyListException("The list is empty!");
        this.list.remove(element);
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public T get(int index) {
        return this.list.get(index);
    }

    @Override
    public String toString()
    {
        StringBuilder printList = new StringBuilder();
        for (T element : this.list){
            printList.append("Element: ").append(element.toString()).append("\n");
        }
        return printList.toString();
    }

    @Override
    public Iterator<T> iterator() {
        return this.list.iterator();
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        List clone = (List) super.clone();
        clone.list = (LinkedList) this.list.clone();
        return clone;
    }
}
