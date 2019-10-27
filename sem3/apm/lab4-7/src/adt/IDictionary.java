package adt;

import Exception.MyException;

import javax.management.openmbean.KeyAlreadyExistsException;

public interface IDictionary<T1,T2> {
    void add(T1 t1, T2 t2) throws NullPointerException, KeyAlreadyExistsException;
    void update(T1 t1, T2 t2)throws NullPointerException, MyException;

    //Functia va returna un element de tipul T2-->valoare(din dictionar)pe care il va cauta dupa ID
    T2 lookUp(T1 id) throws MyException;

    boolean isDefined(T1 id);
    String toString();
}
