package domain.expression;

import adt.IDictionary;
import domain.value.Value;

public interface Expression {
    Value evaluate(IDictionary<String, Value> table) throws Exception;

    Expression deepCopy();
}
