package model.state.symbolTable;

import exceptions.MyException;
import model.type.Type;
import model.value.Value;

import java.util.Map;

public interface ISymbolTable {
    boolean isDefined(String variableName);
    void insert(String variableName, Type variableType);
    Value getValueForKey(String variableName) throws MyException;
    void update(String variableName, Value value) throws MyException;
    String toString();
    Map<String, Value> getMap();
}
