package model.type;

import model.value.IntValue;
import model.value.Value;

public class IntType implements Type {
    private final String typeName = "int";

    @Override
    public boolean equals(Object other) {
        return other instanceof IntType;
    }

    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }

    @Override
    public Type deepCopy() {
        return new IntType();
    }

    @Override
    public String toString() {
        return this.typeName;
    }
}
