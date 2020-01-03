package domain.expression;

import domain.state.heap.DictionaryHeap;
import domain.state.symbol.DictSymbolTable;
import domain.value.IValue;
import domain.value.IntegerValue;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.*;

public class ValueExpressionTest {

    private ValueExpression integerValueExpression;
    private DictSymbolTable mockSymbolTable;
    private DictionaryHeap mockHeap;

    @Before
    public void setUp()
    {
        this.integerValueExpression = new ValueExpression(new IntegerValue(5));
        this.mockSymbolTable = new DictSymbolTable();
        this.mockHeap = new DictionaryHeap();
    }

    @Test
    public void testToString()
    {
        assertEquals(this.integerValueExpression.toString(), "5");
    }

    @Test
    public void testGetValue()
    {
        assertEquals(this.integerValueExpression.getValue(), new IntegerValue(5));
    }

    @Test
    public void testEvaluate()
    {
        IValue<?> result = this.integerValueExpression.evaluate(this.mockSymbolTable, this.mockHeap);
        assertEquals(result, this.integerValueExpression.getValue());
    }

    @Test
    public void testClone()
    {
        ValueExpression clone = null;
        try {
            clone = (ValueExpression) this.integerValueExpression.clone();
        } catch (CloneNotSupportedException e) {
            fail("Hierarchy should implement clone");
        }
        clone.setValue(new IntegerValue(20));
        assertNotSame(this.integerValueExpression, clone);
    }

    @Test
    public void testConstructor()
    {
        IExpression expression = new ValueExpression(new IntegerValue(6));
        try {
            assertEquals(expression.evaluate(this.mockSymbolTable, this.mockHeap), new IntegerValue(6));
        } catch (Exception e) {
            fail("Expression should not throw");
        }
    }
}
