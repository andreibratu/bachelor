package domain.operator;

public enum ArithmeticOperator
{
    PLUS, MINUS, STAR, DIVIDE;


    @Override
    public String toString() {
        String representation = null;
        switch (this)
        {
            case PLUS:
                representation = "+";
                break;
            case STAR:
                representation = "*";
                break;
            case MINUS:
                representation =  "-";
                break;
            case DIVIDE:
                representation = "/";
                break;
        }
        return representation;
    }
}
