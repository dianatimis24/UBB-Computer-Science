package model.ADTs.stack;

import exceptions.MyEmptyStackException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements IStack<T> {
    private final Stack<T> stack = new Stack<>();

    @Override
    public void push(T element) {
        this.stack.push(element);
    }

    @Override
    public T pop() throws MyEmptyStackException {
        if (this.stack.isEmpty())
            throw new MyEmptyStackException();
        return this.stack.pop();
    }

    @Override
    public T top() throws MyEmptyStackException {
        if (this.stack.isEmpty())
            throw new MyEmptyStackException();
        return this.stack.peek();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public int size() {
        return this.stack.size();
    }

    @Override
    public List<T> toList() {
        List<T> list = new ArrayList<>(this.stack);
        Collections.reverse(list);
        return list;
    }

    public Stack<T> getStack() {
        return this.stack;
    }

    @Override
    public String toString() {
        return this.stack.toString();
    }
}
