package model;

public class Pepper extends Vegetable
{
    public Pepper(float weight)
    {
        super(weight);
    }

    @Override
    public String toString()
    {
        return "Pepper " + Float.toString(this.getWeight());
    }
}
