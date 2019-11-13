package domain.operator;

public enum LogicalOperator
{
    EQUAL, DIFFERENT, GT, GTE, ST, STE, AND, OR;


    @Override
    public String toString() {
        String representation = null;
        switch(this)
        {
            case EQUAL:
                representation = "==";
                break;
            case DIFFERENT:
                representation = "!=";
                break;
            case GT:
                representation = ">";
                break;
            case GTE:
                representation = ">=";
                break;
            case ST:
                representation = "<";
                break;
            case STE:
                representation = "<=";
                break;
            case AND:
                representation = "&&";
                break;
            case OR:
                representation = "||";
                break;
        }
        return representation;
    }
}
