package controller;

import model.Eggplant;
import model.Pepper;
import model.Tomato;
import model.Vegetable;
import repository.VegetableRepository;
import repository.RepositoryFullException;

public class VegetableController {
    private VegetableRepository repository;

    public VegetableController()
    {
        this.repository = new VegetableRepository(100);
    }

    public void addVegetable(String type, float weight) throws InvalidVegetableException, RepositoryFullException {
        Vegetable v;
        switch (type)
        {
            case "eggplant":
                v = new Eggplant(weight);
                break;
            case "tomato":
                v = new Tomato(weight);
                break;
            case "pepper":
                v = new Pepper(weight);
                break;
            default:
                throw new InvalidVegetableException();
        }
        this.repository.addVegetable(v);
    }

    public void removeVegetable(int idx) throws IndexOutOfBoundsException
    {
        this.repository.removeVegetable(idx);
    }

    public Vegetable[] getAllVegetables()
    {
        return this.repository.getAllVegetables();
    }

    public Vegetable[] filterByWeight(float x)
    {
        Vegetable[] vegetables = this.repository.getAllVegetables();
        int count = 0, idx = 0;
        for(Vegetable v : vegetables) if(v.isGreaterThan(x)) count++;
        Vegetable[] filtered = new Vegetable[count];
        for(Vegetable v : vegetables) if(v.isGreaterThan(x)) filtered[idx++] = v;
        return filtered;
    }
}
