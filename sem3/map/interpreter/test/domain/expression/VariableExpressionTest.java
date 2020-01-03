package domain.expression;

import domain.state.heap.DictionaryHeap;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.value.IntegerValue;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class VariableExpressionTest {

    private VariableExpression varExpression;
    private DictSymbolTable mockSymbolTable;
    private DictionaryHeap mockHeap;

    @Before
    public void setUp() {
        this.varExpression = new VariableExpression("a");
        this.mockSymbolTable = new DictSymbolTable();
        this.mockHeap = new DictionaryHeap();
        try {
            mockSymbolTable.createVariable("a", new IntegerValue(7));
        } catch (Exception e) {
            fail(e.getMessage());
        }
    }

    @Test
    public void testToString() {
        assertEquals(this.varExpression.toString(), "a");
    }

    @Test
    public void testEvaluate() {
        try {
            assertEquals(varExpression.evaluate(mockSymbolTable, mockHeap), new IntegerValue(7));
        } catch (UndeclaredVariableException e) {
            fail("Variable does exist in the symbol table");
        }
    }

    @Test(expected = UndeclaredVariableException.class)
    public void testEvaluateUndeclaredVariable() throws UndeclaredVariableException
    {
        VariableExpression invalid = new VariableExpression("b");
        invalid.evaluate(mockSymbolTable, mockHeap);
    }

    @Test
    @SuppressWarnings("unused")
    public void testClone() {
        try {
            VariableExpression clone = (VariableExpression) this.varExpression.clone();
        } catch (CloneNotSupportedException e) {
            fail("Hierarchy should implement clone");
        }

    }
}
