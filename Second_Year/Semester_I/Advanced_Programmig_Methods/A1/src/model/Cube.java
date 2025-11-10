package model;

public class Cube implements GeometricShape {
    public final float edge;
    public final float volume;

    public Cube(float volume, float edge) {
        this.volume = volume;
        this.edge = edge;
    }

    public Cube(float edge) {
        this.edge = edge;
        this.volume = edge * edge * edge;
    }

    @Override
    public float getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Cube with volume " + this.volume + " and edge " + this.edge;
    }
}
