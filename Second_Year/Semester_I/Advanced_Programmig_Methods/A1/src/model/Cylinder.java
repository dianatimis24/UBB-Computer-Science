package model;

public class Cylinder implements GeometricShape {
    public final float radius;
    public final float height;
    public final float volume;

    public Cylinder(float volume, float radius, float height) {
        this.volume = volume;
        this.radius = radius;
        this.height = height;
    }

    public Cylinder(float radius, float height) {
        this.radius = radius;
        this.height = height;
        this.volume = (float) (Math.PI * this.radius * this.radius * this.height);
    }

    @Override
    public float getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Cylinder with volume " + this.volume + ", radius " + this.radius + " and height " + this.height;
    }
}
