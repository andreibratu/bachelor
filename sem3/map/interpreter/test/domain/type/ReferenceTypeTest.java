package domain.type;

import org.junit.Test;

import static junit.framework.TestCase.*;

public class ReferenceTypeTest
{
    @Test
    public void testReferenceToReference()
    {
        ReferenceType test = new ReferenceType(new IntegerType());
        assertTrue(test.getInnerType() instanceof IntegerType);
        ReferenceType testRef = new ReferenceType(test);
        assertTrue(testRef.getInnerType() instanceof ReferenceType);
    }

    @Test
    public void testToString()
    {
        ReferenceType nullRef = new ReferenceType(null);
        assertEquals("&", nullRef.toString());
        ReferenceType intRef = new ReferenceType(new IntegerType());
        assertEquals("int&", intRef.toString());
        ReferenceType intRefRef = new ReferenceType(intRef);
        assertEquals("int&&", intRefRef.toString());
    }

    @Test
    public void testEquals()
    {
        ReferenceType intRef1 = new ReferenceType(new IntegerType());
        ReferenceType intRef2 = new ReferenceType(new IntegerType());
        assertEquals(intRef1, intRef2);
        ReferenceType intRefRef1 = new ReferenceType(intRef1);
        ReferenceType intRefRef2 = new ReferenceType(intRef2);
        assertEquals(intRefRef1, intRefRef2);
    }

    @Test
    public void testClone()
    {
        ReferenceType toClone = new ReferenceType(new IntegerType());
        try
        {
            ReferenceType clone = (ReferenceType) toClone.clone();
            assertTrue(clone.getInnerType() instanceof IntegerType);
        } catch (CloneNotSupportedException e)
        {
            fail("Hierarchy should be implementing clone properly");
        }

    }
}
