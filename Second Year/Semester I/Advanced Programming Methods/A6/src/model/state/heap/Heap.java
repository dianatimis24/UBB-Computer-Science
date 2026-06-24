package model.state.heap;

import exceptions.MyException;
import exceptions.MyKeyNotFoundException;
import model.value.Value;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class Heap implements IHeap {
    private Map<Integer, Value> heap = new ConcurrentHashMap<>();
    private int firstFreeLocation = 1;

    public synchronized int newAddress() {
        this.firstFreeLocation++;
        while (this.firstFreeLocation == 0 || isDefined(this.firstFreeLocation)) {
            this.firstFreeLocation++;
        }
        return this.firstFreeLocation;
    }

    @Override
    public synchronized boolean isDefined(Integer address) {
        return this.heap.containsKey(address);
    }

    @Override
    public synchronized int insert(Value value) {
        this.heap.put(this.firstFreeLocation, value);
        int addressToReturn = this.firstFreeLocation;
        this.firstFreeLocation = newAddress();
        return addressToReturn;
    }

    @Override
    public synchronized Value getValueForKey(Integer address) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        return heap.get(address);
    }

    @Override
    public synchronized void update(Integer address, Value value) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        this.heap.put(address, value);
    }

    @Override
    public synchronized void remove(Integer address) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        this.heap.remove(address);
    }

    @Override
    public synchronized Map<Integer, Value> getContent() {
        return Map.copyOf(this.heap);
    }

    @Override
    public synchronized void setContent(HashMap<Integer, Value> heap) {
        this.heap = heap;
    }

    @Override
    public synchronized List<Value> getValues() {
        return this.heap.values().stream().toList();
    }

    @Override
    public synchronized Set<Integer> keySet() {
        return this.heap.keySet();
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("Heap:\n");
        for (int key : this.heap.keySet()) {
            answer.append(key).append("(").append(this.heap.get(key).getType().toString()).append(")").append(":-> ").append(this.heap.get(key).toString()).append("\n");
        }
        return answer.toString();
    }
}
