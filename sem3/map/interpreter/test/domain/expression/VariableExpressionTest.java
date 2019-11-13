package domain.expression;

import adt.dictionary.Dictionary;
import adt.dictionary.IDictionary;
import domain.value.IValue;
import domain.value.IntegerValue;
import exception.variable.UndeclaredVariableException;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class VariableExpressionTest {

    private VariableExpression varExpression;
    private IDictionary<String, IValue> mockSymbolTable;

    @Before
    public void setUp() {
        this.varExpression = new VariableExpression("a");
        this.mockSymbolTable = new Dictionary<>();
        mockSymbolTable.put("a", new IntegerValue(7));
    }

    @Test
    public void testToString() {
        assertEquals(this.varExpression.toString(), "a");
    }

    @Test
    public void testEvaluate() {
        try {
            assertEquals(varExpression.evaluate(mockSymbolTable), new IntegerValue(7));
        } catch (UndeclaredVariableException e) {
            fail("Variable does exist in the symbol table");
        }
    }

    @Test(expected = UndeclaredVariableException.class)
    public void testEvaluateUndeclaredVariable() throws UndeclaredVariableException {
        VariableExpression invalid = new VariableExpression("b");
        invalid.evaluate(mockSymbolTable);
    }

    @Test
    public void testClone() {
        try {
            VariableExpression clone = (VariableExpression) this.varExpression.clone();
        } catch (CloneNotSupportedException e) {
            fail("Hierarchy should implement clone");
        }

    }
}
