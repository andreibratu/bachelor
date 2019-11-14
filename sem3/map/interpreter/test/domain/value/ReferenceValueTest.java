package domain.value;

import domain.type.IllegalComparisonException;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import org.junit.Test;

import static junit.framework.TestCase.*;
import static org.junit.Assert.assertNotEquals;

public class ReferenceValueTest
{
    @Test
    public void testDefaultConstructor()
    {
        ReferenceValue test = new ReferenceValue(new IntegerType());
        assertEquals((int)test.getValue(), 0);
        assertTrue(test.getLocationType() instanceof IntegerType);
    }

    @Test
    public void testReferenceToReference()
    {
        ReferenceValue test = new ReferenceValue(new IntegerType());
        ReferenceValue testRef = new ReferenceValue(test.getType());
        assertTrue(testRef.getLocationType() instanceof ReferenceType);
    }

    @Test(expected = IllegalComparisonException.class)
    public void testReferencesUncomparable() throws IllegalComparisonException
    {
        ReferenceValue ref1 = new ReferenceValue(1, new IntegerType());
        ReferenceValue ref2 = new ReferenceValue(2, new IntegerType());
        assertTrue(ref1.compareTo(ref2) < 0);
    }

    @Test
    public void testClone()
    {
        ReferenceValue toClone = new ReferenceValue(new IntegerType());
        try {
            ReferenceValue clone = (ReferenceValue) toClone.clone();
            clone.setValue(6);
            assertNotEquals(toClone.getValue(), clone.getValue());
        } catch (CloneNotSupportedException e) {
            fail("Clone should be alright");
        }
    }
}
