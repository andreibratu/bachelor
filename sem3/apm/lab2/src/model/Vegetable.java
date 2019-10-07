package model;

public class Vegetable implements ICompareTo {
    private float weight;

    Vegetable(float weight)
    {
        this.weight = weight;
    }

    public float getWeight()
    {
        return weight;
    }

    public void setWeight(float weight)
    {
        this.weight = weight;
    }

    public String toString()
    {
        return "Vegetable " + Float.toString(this.weight);
    }

    @Override
    public boolean isGreaterThan(float x) {
        return this.weight > x;
    }
}
