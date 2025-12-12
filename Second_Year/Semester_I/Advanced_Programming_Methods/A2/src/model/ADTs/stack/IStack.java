package model.ADTs.stack;

import exceptions.MyEmptyStackException;

import java.util.List;

public interface IStack<T> {
    void push(T element);
    T pop() throws MyEmptyStackException;
    T top() throws MyEmptyStackException;
    boolean isEmpty();
    int size();
    List<T> toList();
}
