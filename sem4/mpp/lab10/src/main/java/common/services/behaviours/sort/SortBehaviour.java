package common.services.behaviours.sort;

import common.services.behaviours.GenericBehaviour;
import javafx.util.Pair;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Component;

import java.util.function.BiFunction;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Component
@ComponentScan
public class SortBehaviour extends GenericBehaviour
{
    public SortBehaviour() {}

    public <T> Iterable<T> sort(Iterable<T> list, SortStrategy strategy)
    {
        if(strategy == null) return list;
        BiFunction<T, T, Integer> cmp = (T a, T b) ->
        {
            for(Pair<String, SortStrategy.Direction> field: strategy.getFields())
            {
                Object val1 = getAttributeValue(a, field.getKey());
                Object val2 = getAttributeValue(b, field.getKey());
                if(val1 instanceof Integer)
                {
                    int result = (field.getValue() == SortStrategy.Direction.ASC) ?
                            ((Integer) val1).compareTo((Integer) val2) :
                            ((Integer) val2).compareTo((Integer) val1);
                    if(result != 0) return result;
                }
                if(val1 instanceof Double)
                {
                    int result = (field.getValue() == SortStrategy.Direction.ASC) ?
                            ((Double) val1).compareTo((Double) val2) :
                            ((Double) val2).compareTo((Double) val1);
                    if(result != 0) return result;
                }
                if(val1 instanceof String)
                {
                    int result = (field.getValue() == SortStrategy.Direction.ASC) ?
                            ((String) val1).compareTo((String)val2) :
                            ((String) val2).compareTo((String)val1);
                    if(result != 0) return result;
                }
                if(val1 instanceof Enum<?>)
                {
                    throw new RuntimeException("Cannot sort by categorical attribute!");
                }
            }
            return 0;
        };
        return StreamSupport.stream(list.spliterator(), false).sorted(cmp::apply).collect(Collectors.toList());
    }
}
