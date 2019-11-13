package domain.value;

import domain.type.IntegerType;
import domain.value.BoolValue;
import domain.value.IntegerValue;
import exception.type.IllegalComparisonException;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;
import static org.junit.Assert.assertFalse;

@SuppressWarnings("ALL")
public class IntegerValueTest {

    @Test
    public void testEquals()
    {
        assertEquals(new IntegerValue(5), new IntegerValue(5));
    }

    @Test(expected = IllegalComparisonException.class)
    public void testIllegalEquals()
    {
        new IntegerValue(5).equals(new BoolValue());
    }

    @Test
    public void testGreaterEqualThen()
    {
        assertTrue(new IntegerValue(5).greaterThenEqual(new IntegerValue(2)));
        assertTrue(new IntegerValue(5).greaterThenEqual(new IntegerValue(5)));
    }

    @Test
    public void testDifferent()
    {
        assertTrue(new IntegerValue(5).different(new IntegerValue(2)));
        assertFalse(new IntegerValue(5).different(new IntegerValue(5)));
    }

    @Test
    public void testEqual()
    {
        assertTrue(new IntegerValue(5).equal(new IntegerValue(5)));
        assertFalse(new IntegerValue(5).equal(new IntegerValue(2)));
    }

    @Test
    public void testSmallerEqualThen()
    {
        assertTrue(new IntegerValue(2).smallerEqual(new IntegerValue(10)));
        assertTrue(new IntegerValue(2).smallerEqual(new IntegerValue(2)));
    }

    @Test
    public void testSmaller()
    {
        assertTrue(new IntegerValue(2).smaller(new IntegerValue(10)));
        assertFalse(new IntegerValue(2).smaller(new IntegerValue(2)));
    }

    @Test
    public void testGetType()
    {
        assertTrue(new IntegerValue(5).getType() instanceof IntegerType);
    }

    @Test
    public void testGetValue()
    {
        assertEquals((int)new IntegerValue(5).getValue(), 5);
    }
}
