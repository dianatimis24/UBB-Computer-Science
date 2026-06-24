package model.ADTs.dictionary;

import exceptions.MyKeyNotFoundException;

import java.util.List;
import java.util.Map;

public interface IDictionary<K, V> {
    boolean isDefined(K key);
    void insert(K key, V value);
    void update(K key, V value) throws MyKeyNotFoundException;
    void remove(K key) throws MyKeyNotFoundException;
    V getValueForKey(K key) throws MyKeyNotFoundException;
    List<K> getAllKeys();
    List<V> getAllValues();
    Map<K, V> getMap();
}
