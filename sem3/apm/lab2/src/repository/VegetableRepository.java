package repository;

import model.Vegetable;

public class VegetableRepository {
    private Vegetable[] vegetables;
    private int idx;

    public VegetableRepository(int size)
    {
        this.vegetables = new Vegetable[size];
        this.idx = 0;
    }

    public void addVegetable(Vegetable v) throws RepositoryFullException {
        if(this.idx == this.vegetables.length) throw new RepositoryFullException();
        this.vegetables[this.idx++] = v;
    }

    public void removeVegetable(int idx) throws IndexOutOfBoundsException {
        if(idx < 0 || idx >= this.idx) throw new IndexOutOfBoundsException();
        System.arraycopy(this.vegetables, idx + 1, this.vegetables, idx, this.idx - idx);
        this.idx -= 1;
    }

    public Vegetable[] getAllVegetables()
    {
        Vegetable[] returned = new Vegetable[this.idx];
        System.arraycopy(this.vegetables, 0, returned, 0, idx);
        return returned;
    }
}
