package common.services.behaviours.filter;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
public class FilterStrategy
{
    private String attribute;
    private String operator;
    private Object compareValue;
}
