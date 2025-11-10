package repository;

import model.GeometricShape;

public interface IRepository {
    void addGeometricShape(GeometricShape geometricShape) throws Exception;
    GeometricShape removeGeometricShape(int index);
    GeometricShape[] getAll();
}
