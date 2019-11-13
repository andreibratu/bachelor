package model;

public class Tomato extends Vegetable
{
    public Tomato(float weight)
    {
        super(weight);
    }

    @Override
    public String toString()
    {
        return "Tomato " + Float.toString(this.getWeight());
    }
}
