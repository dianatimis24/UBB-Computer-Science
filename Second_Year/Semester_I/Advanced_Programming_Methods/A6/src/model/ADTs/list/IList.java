package model.ADTs.list;

import exceptions.MyIndexOutOfBoundsException;

import java.util.List;

public interface IList<T> {
    void add(T element);
    void remove(int index) throws MyIndexOutOfBoundsException;
    T getElement(int index) throws MyIndexOutOfBoundsException;
    List<T> getAll();
    boolean isEmpty();
    int size();
    void clear();
}
