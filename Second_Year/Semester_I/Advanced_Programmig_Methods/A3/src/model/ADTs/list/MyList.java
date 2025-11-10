package model.ADTs.list;

import exceptions.MyIndexOutOfBoundsException;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements IList<T> {
    private List<T> list;

    public MyList() {
        this.list = new ArrayList<>();
    }

    @Override
    public void add(T element) {
        this.list.add(element);
    }

    @Override
    public void remove(int index) throws MyIndexOutOfBoundsException {
        if (index < 0 || index >= this.list.size()) {
            throw new MyIndexOutOfBoundsException();
        }
        this.list.remove(index);
    }

    @Override
    public T getElement(int index) throws MyIndexOutOfBoundsException {
        if (index < 0 || index >= this.list.size()) {
            throw new MyIndexOutOfBoundsException();
        }
        return this.list.get(index);
    }

    @Override
    public List<T> getAll() {
        return this.list;
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public void clear() {
        this.list.clear();
    }

    public void setList(List<T> list) {
        this.list = list;
    }

    @Override
    public String toString() {
        return this.list.toString();
    }
}
