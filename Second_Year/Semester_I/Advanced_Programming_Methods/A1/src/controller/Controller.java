package controller;

import model.GeometricShape;
import repository.IRepository;

import java.util.Arrays;

public class Controller {
    public IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void addGeometricShape(GeometricShape geometricShape) {
        if (geometricShape.getVolume() > 0) {
            try {
                repository.addGeometricShape(geometricShape);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        else {
            throw new RuntimeException("Please add a valid geometric shape!");
        }
    }

    public GeometricShape removeGeometricShape(int index) throws IndexOutOfBoundsException {
        return this.repository.removeGeometricShape(index);
    }

    public GeometricShape[] getAll() {
        return this.repository.getAll();
    }

    public GeometricShape[] getLargeGeometricShapes(float minimumVolume) {
        GeometricShape[] shapes = this.repository.getAll();
        GeometricShape[] largeShapes = new GeometricShape[shapes.length];
        int size = 0;

        for (var shape : shapes) {
            if (shape.getVolume() > minimumVolume) {
                largeShapes[size++] = shape;
            }
        }

        return Arrays.copyOf(largeShapes, size);
    }
}
