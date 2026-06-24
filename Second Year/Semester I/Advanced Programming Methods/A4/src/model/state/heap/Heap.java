package model.state.heap;

import exceptions.MyException;
import exceptions.MyKeyNotFoundException;
import model.value.Value;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class Heap implements IHeap {
    private HashMap<Integer, Value> heap;
    private int firstFreeLocation;

    public Heap() {
        this.heap = new HashMap<>();
        this.firstFreeLocation = 1;
    }

    public int newAddress() {
        this.firstFreeLocation++;
        while (this.firstFreeLocation == 0 || isDefined(this.firstFreeLocation)) {
            this.firstFreeLocation++;
        }
        return this.firstFreeLocation;
    }

    @Override
    public boolean isDefined(Integer address) {
        return this.heap.containsKey(address);
    }

    @Override
    public int insert(Value value) {
        this.heap.put(this.firstFreeLocation, value);
        int addressToReturn = this.firstFreeLocation;
        this.firstFreeLocation = newAddress();
        return addressToReturn;
    }

    @Override
    public Value getValueForKey(Integer address) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        return heap.get(address);
    }

    @Override
    public void update(Integer address, Value value) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        this.heap.put(address, value);
    }

    @Override
    public void remove(Integer address) throws MyException {
        if (!isDefined(address)) {
            throw new MyKeyNotFoundException();
        }
        this.heap.remove(address);
    }

    @Override
    public Map<Integer, Value> getContent() {
        return this.heap;
    }

    @Override
    public void setContent(HashMap<Integer, Value> heap) {
        this.heap = heap;
    }

    @Override
    public Set<Integer> keySet() {
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
