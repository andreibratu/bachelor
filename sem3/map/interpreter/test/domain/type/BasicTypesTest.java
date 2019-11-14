package domain.type;

import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.*;
import static org.junit.Assert.assertNotEquals;

public class BasicTypesTest {
    private BoolType boolType;
    private IntegerType integerType;
    private StringType stringType;

    @Before
    public void setUp()
    {
        this.boolType = new BoolType();
        this.integerType = new IntegerType();
        this.stringType = new StringType();
    }

    @Test
    public void testToString()
    {
        assertEquals(boolType.toString(), "bool");
        assertEquals(integerType.toString(), "int");
        assertEquals(stringType.toString(), "string");
    }

    @Test
    public void testDefaultValue()
    {
        assertFalse(boolType.defaultValue().getValue());
        assertEquals((int)integerType.defaultValue().getValue(), 0);
        assertEquals(stringType.defaultValue().getValue(), "");
    }

    @Test
    public void testEquality()
    {
        assertEquals(this.boolType, new BoolType());
        assertNotEquals(this.stringType, this.boolType);
        assertEquals(this.stringType, new StringType());
    }
}
