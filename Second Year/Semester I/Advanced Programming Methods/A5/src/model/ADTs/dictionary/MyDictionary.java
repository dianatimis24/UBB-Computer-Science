package model.ADTs.dictionary;

import exceptions.MyKeyNotFoundException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyDictionary<K, V> implements IDictionary<K, V> {
    private final Map<K, V> map = new HashMap<>();

    @Override
    public boolean isDefined(K key) {
        return this.map.containsKey(key);
    }

    @Override
    public void insert(K key, V value) {
        this.map.put(key, value);
    }

    @Override
    public void update(K key, V value) throws MyKeyNotFoundException {
        if (!isDefined(key)) {
            throw new MyKeyNotFoundException();
        }
        this.map.put(key, value);
    }

    @Override
    public void remove(K key) throws MyKeyNotFoundException {
        if (!isDefined(key)) {
            throw new MyKeyNotFoundException();
        }
        this.map.remove(key);
    }

    @Override
    public V getValueForKey(K key) throws MyKeyNotFoundException {
        if (!isDefined(key)) {
            throw new MyKeyNotFoundException();
        }
        return this.map.get(key);
    }

    @Override
    public List<K> getAllKeys() {
        return new ArrayList<>(this.map.keySet());
    }

    @Override
    public List<V> getAllValues() {
        return new ArrayList<>(this.map.values());
    }

    @Override
    public Map<K, V> getMap() {
        return Map.copyOf(this.map);
    }

    @Override
    public boolean isEmpty() {
        return this.map.isEmpty();
    }

    @Override
    public int size() {
        return this.map.size();
    }

    @Override
    public String toString() {
        return this.map.toString();
    }
}
