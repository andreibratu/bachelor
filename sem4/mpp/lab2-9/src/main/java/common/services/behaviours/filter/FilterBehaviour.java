package common.services.behaviours.filter;

import common.services.behaviours.GenericBehaviour;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Component
@ComponentScan
public class FilterBehaviour extends GenericBehaviour
{
    public FilterBehaviour() {}

    @SuppressWarnings("unchecked")
    public <T> Iterable<T> filter(Iterable<T> list, FilterStrategy strategy)
    {
        Predicate<T> filter = (T obj) ->
        {
            Object objectValue = getAttributeValue(obj, strategy.getAttribute());
            Object compareValue = strategy.getCompareValue();
            boolean result = false;

            if(objectValue instanceof Number && compareValue instanceof Number)
            {
                int comparison = ((Comparable<Number>) objectValue).compareTo((Number) compareValue);
                switch (strategy.getOperator())
                {
                    case "==":
                        result = comparison == 0;
                        break;
                    case "!=":
                        result = comparison != 0;
                        break;
                    case ">":
                        result = comparison > 0;
                        break;
                    case ">=":
                        result = comparison >= 0;
                        break;
                    case "<":
                        result = comparison < 0;
                        break;
                    case "<=":
                        result = comparison <= 0;
                        break;
                }
            }
            if(objectValue instanceof String && compareValue instanceof String)
            {
                switch (strategy.getOperator())
                {
                    case "STARTS":
                        result = ((String)objectValue).toLowerCase().startsWith(((String) compareValue).toLowerCase());
                        break;
                    case "CONTAINS":
                        result = ((String) objectValue).toLowerCase().contains(((String) compareValue).toLowerCase());
                        break;
                }
            }
            if(objectValue instanceof Enum && compareValue instanceof Enum)
            {
                int comparison = ((Enum<?>) objectValue).ordinal() - ((Enum<?>) compareValue).ordinal();
                switch (strategy.getOperator()) {
                    case "EQ":
                        result = comparison == 0;
                        break;
                    case "NEQ":
                        result = comparison != 0;
                        break;
                }
            }
            return result;
        };
        return StreamSupport.stream(list.spliterator(), false).filter(filter).collect(Collectors.toList());
    }

    public static Iterable<String> getFilters(Class<?> cls)
    {
        if(cls == Integer.class || cls == Float.class || cls == Double.class)
        {
            return List.of("==", "!=", ">", ">=", "<", "<=");
        }
        else if (cls == String.class)
        {
            return List.of("STARTS", "CONTAINS");
        }
        return List.of("EQ", "NEQ");
    }
}
