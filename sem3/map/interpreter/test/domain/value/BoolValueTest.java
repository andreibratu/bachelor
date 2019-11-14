package domain.value;

import domain.type.BoolType;
import domain.type.IllegalComparisonException;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;
import static org.junit.Assert.*;

public class BoolValueTest
{
    private BoolValue falseValue;
    private BoolValue trueValue;

    @Before
    public void setUp() {
        falseValue = new BoolValue();
        trueValue = new BoolValue(true);
    }

    @Test
    public void testDefaultValue()
    {
        assertFalse(this.falseValue.getValue());
    }

    @Test
    public void testConstructor() {
        BoolValue val = new BoolValue(true);
        assertTrue(val.getValue());
    }

    @Test
    public void testToString() {
        assertEquals(trueValue.toString(), "true");
        assertEquals(falseValue.toString(), "false");
    }

    @Test
    public void testGetType()
    {
        assertTrue(trueValue.getType() instanceof BoolType);
    }

    @Test
    public void testClone() throws CloneNotSupportedException {
        BoolValue clone = (BoolValue) this.falseValue.clone();
        clone.setValue(true);
        assertNotSame(falseValue, clone);
    }

    @Test
    public void TestEquals() {
        assertEquals(this.falseValue, new BoolValue());
        assertNotEquals(this.falseValue, this.trueValue);
    }

    @Test(expected = IllegalComparisonException.class)
    public void TestIllegalEquals() {
        assertNotEquals(this.trueValue, new Object());
    }

    @Test(expected = IllegalComparisonException.class)
    public void CannotCompareBooleans() {
        assertTrue(this.trueValue.compareTo(this.falseValue) > 0);
    }
}
