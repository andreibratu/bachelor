package common.services.behaviours;

import common.entities.GenreEnum;

import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public abstract class GenericBehaviour
{
    public static Map<String, Class<?>> getEntityAttributes(Class<?> cls)
    {
        List<Class<?>> allowedTypes = List.of(Integer.class, Double.class, String.class, GenreEnum.class);
        return Arrays.stream(cls.getDeclaredFields())
                .filter(field -> allowedTypes.contains(field.getType()))
                .collect(Collectors.toMap(Field::getName, Field::getType));
    }

    protected Object getAttributeValue(Object obj, String attrName)
    {
        Object val = null;
        try
        {
            Field field = obj.getClass().getDeclaredField(attrName);
            field.setAccessible(true);
            val = field.get(obj);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return val;
    }
}
