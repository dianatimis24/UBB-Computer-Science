package model.state.symbolTable;

import exceptions.MyException;
import exceptions.MyKeyNotFoundException;
import model.ADTs.dictionary.IDictionary;
import model.ADTs.dictionary.MyDictionary;
import model.type.Type;
import model.value.Value;

import java.util.List;
import java.util.Map;

public class SymbolTable implements ISymbolTable {
    private final IDictionary<String, Value> data = new MyDictionary<>();

    @Override
    public boolean isDefined(String variableName) {
        return this.data.isDefined(variableName);
    }

    @Override
    public void insert(String variableName, Type variableType) {
        this.data.insert(variableName, variableType.defaultValue());
    }

    @Override
    public Value getValueForKey(String variableName) throws MyException {
        try {
            return this.data.getValueForKey(variableName);
        } catch (MyKeyNotFoundException exception) {
            throw new MyKeyNotFoundException();
        }
    }

    @Override
    public void update(String variableName, Value value) throws MyException {
        if (!this.data.isDefined(variableName))
            throw new MyKeyNotFoundException();

        if (!this.data.getValueForKey(variableName).getType().equals(value.getType()))
            throw new MyKeyNotFoundException();

        this.data.update(variableName, value);
    }

    @Override
    public Map<String, Value> getMap() {
        return this.data.getMap();
    }

    @Override
    public List<Value> getValues() {
        return this.data.getAllValues();
    }

    @Override
    public ISymbolTable deepCopy() throws MyException {
        SymbolTable copySymbolTable = new SymbolTable();
        for (String key : this.data.getAllKeys()) {
            Value value = this.data.getValueForKey(key);
            copySymbolTable.insert(key, value.getType());
            copySymbolTable.update(key, value);
        }
        return copySymbolTable;
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("SymTable:\n");
        try {
            for (String key : this.data.getAllKeys()) {
                answer.append(key).append("(").append(this.data.getValueForKey(key).getType().toString()).append(")").append(" -> ").append(this.data.getValueForKey(key).toString()).append("\n");
            }
        } catch (MyException exception) {
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }
}
