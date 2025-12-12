package model.value;

import model.type.IntType;
import model.type.Type;

public class IntValue implements Value {
    private final int value;

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public boolean equals(Value other) {
        return other instanceof IntValue && ((IntValue) other).value == this.value;
    }

    @Override
    public Value deepCopy() {
        return new IntValue(this.value);
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }
}
