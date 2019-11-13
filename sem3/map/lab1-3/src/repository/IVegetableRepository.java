package repository;

import model.Vegetable;

public interface IVegetableRepository {
    void addVegetable(Vegetable v) throws RepositoryFullException;

    void removeVegetable(int idx) throws IndexOutOfBoundsException;

    Vegetable[] getAllVegetables();
}
