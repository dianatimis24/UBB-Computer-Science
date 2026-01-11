package model.state.heap;

import exceptions.MyException;
import model.value.Value;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public interface IHeap {
    boolean isDefined(Integer address);
    int insert(Value value);
    Value getValueForKey(Integer address) throws MyException;
    void update(Integer address, Value value) throws MyException;
    void remove(Integer address) throws MyException;
    Map<Integer, Value> getContent();
    void setContent(HashMap<Integer, Value> heap);
    List<Value> getValues();
    Set<Integer> keySet();
    String toString();
}
