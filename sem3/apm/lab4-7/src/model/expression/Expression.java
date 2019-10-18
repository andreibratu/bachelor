package model.expression;

import model.value.Value;

import java.util.Dictionary;
import java.util.HashMap;

public interface Expression {
    Value evaluate(HashMap<String, Value> table) throws Exception;
}
