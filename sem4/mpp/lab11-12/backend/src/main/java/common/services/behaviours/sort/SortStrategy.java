package common.services.behaviours.sort;

import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;

public class SortStrategy
{

    public enum Direction
    {
        DESC, ASC
    }

    private final List<Pair<String, Direction>> fields;

    public SortStrategy()
    {
        fields = new ArrayList<>();
    }

    public SortStrategy(Direction direct, String... names)
    {
        fields = new ArrayList<>();
        for( String name : names)
        {
            Pair<String, Direction> elem = new Pair<>(name, direct);
            this.fields.add(elem);
        }
    }

    public void add(String fieldName, Direction direction)
    {
        this.fields.add(new Pair<>(fieldName, direction));
    }

    public List<Pair<String, Direction>> getFields() {
        return fields;
    }
}