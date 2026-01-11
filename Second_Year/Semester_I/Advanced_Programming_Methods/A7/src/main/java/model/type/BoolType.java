package model.type;

import model.value.BoolValue;
import model.value.Value;

public class BoolType implements Type {
    private final String typeName = "bool";

    @Override
    public boolean equals(Object other) {
        return other instanceof BoolType;
    }

    @Override
    public Value defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public Type deepCopy() {
        return new BoolType();
    }

    @Override
    public String toString() {
        return this.typeName;
    }
}
