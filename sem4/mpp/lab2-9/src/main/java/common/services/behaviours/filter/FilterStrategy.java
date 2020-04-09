package common.services.behaviours.filter;

public class FilterStrategy
{
    private String attribute;
    private String operator;
    private Object compareValue;

    public FilterStrategy(String attribute, String operator, Object compareValue)
    {
        this.attribute = attribute;
        this.operator = operator;
        this.compareValue = compareValue;
    }

    public String getAttribute() {
        return attribute;
    }

    public void setAttribute(String attribute) {
        this.attribute = attribute;
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public Object getCompareValue() {
        return compareValue;
    }

    public void setCompareValue(Object compareValue) {
        this.compareValue = compareValue;
    }
}
