package model;

public class Eggplant extends Vegetable
{
    public Eggplant(float weight) {
        super(weight);
    }

    @Override
    public String toString() {
        return "Eggplant " + Float.toString(this.getWeight());
    }
}
