package adt;

import javax.management.openmbean.KeyAlreadyExistsException;

public interface IDictionary<T1,T2> {
    void add(T1 t1, T2 t2) throws NullPointerException, KeyAlreadyExistsException;
    void update(T1 t1, T2 t2)throws NullPointerException, Exception;

    T2 lookUp(T1 id) throws Exception;

    boolean isDefined(T1 id);

    String toString();
}
