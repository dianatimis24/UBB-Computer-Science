package model.value;

import model.type.ReferenceType;
import model.type.Type;

public class ReferenceValue implements Value {
    private final int address;
    private final Type locationType;

    public ReferenceValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    @Override
    public Type getType() {
        return new ReferenceType(this.locationType);
    }

    public int getAddress() {
        return this.address;
    }

    @Override
    public boolean equals(Value other) {
        return (other instanceof ReferenceValue) && this.address == ((ReferenceValue) other).address && this.getType().equals(other.getType());
    }

    @Override
    public Value deepCopy() {
        return new ReferenceValue(this.address, this.locationType.deepCopy());
    }

    @Override
    public String toString() {
        return "ReferenceValue(" + this.address + ", " + this.locationType.toString() + ")";
    }
}
