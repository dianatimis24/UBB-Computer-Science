package repository;

import exceptions.FullRepositoryException;
import model.GeometricShape;

import java.util.Arrays;

public class Repository implements IRepository {
    private final GeometricShape[] geometricShapes;
    private int size = 0;

    public Repository(int capacity) {
        this.geometricShapes = new GeometricShape[capacity];
    }

    @Override
    public void addGeometricShape(GeometricShape geometricShape) throws Exception {
        if (this.size == this.geometricShapes.length) {
            throw new FullRepositoryException();
        }
        this.geometricShapes[this.size++] = geometricShape;
    }

    @Override
    public GeometricShape removeGeometricShape(int index) {
        if (index < 0 || index >= this.size) {
            throw new IndexOutOfBoundsException("The index is not valid!");
        }
        var removedGeometricShape = this.geometricShapes[index];
        for (int i = index; i < this.size; i++) {
            this.geometricShapes[i] = this.geometricShapes[i + 1];
        }
        this.size--;
        return removedGeometricShape;
    }

    @Override
    public GeometricShape[] getAll() {
        return Arrays.copyOf(geometricShapes, size);
    }
}
