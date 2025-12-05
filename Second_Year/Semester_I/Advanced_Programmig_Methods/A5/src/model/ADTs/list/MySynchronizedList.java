package model.ADTs.list;

import exceptions.MyIndexOutOfBoundsException;

import java.util.List;
import java.util.Vector;

public class MySynchronizedList<T> implements IList<T> {
    private final List<T> list = new Vector<>();

    @Override
    public synchronized void add(T element) {
        this.list.add(element);
    }

    @Override
    public synchronized void remove(int index) throws MyIndexOutOfBoundsException {
        if (index < 0 || index >= this.list.size()) {
            throw new MyIndexOutOfBoundsException();
        }
        this.list.remove(index);
    }

    @Override
    public synchronized T getElement(int index) throws MyIndexOutOfBoundsException {
        if (index < 0 || index >= this.list.size()) {
            throw new MyIndexOutOfBoundsException();
        }
        return this.list.get(index);
    }

    @Override
    public synchronized List<T> getAll() {
        return List.copyOf(this.list);
    }

    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public void clear() {
        this.list.clear();
    }

    @Override
    public String toString() {
        return this.list.toString();
    }
}
