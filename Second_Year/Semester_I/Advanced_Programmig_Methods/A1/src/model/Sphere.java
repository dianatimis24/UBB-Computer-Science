package model;

public class Sphere implements GeometricShape {
    public final float radius;
    public final float volume;

    public Sphere(float volume, float radius) {
        this.volume = volume;
        this.radius = radius;
    }

    public Sphere(float radius) {
        this.radius = radius;
        this.volume = (float) (4 * Math.PI * this.radius * this.radius * this.radius / 3);
    }

    @Override
    public float getVolume() {
        return this.volume;
    }

    @Override
    public String toString() {
        return "Sphere with volume " + this.volume + " and radius " + this.radius;
    }
}
