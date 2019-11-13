package domain.value;

import domain.type.StringType;
import domain.value.StringValue;
import exception.type.IllegalComparisonException;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;
import static org.junit.Assert.*;

public class StringValueTest
{
   private StringValue foo;
   private StringValue bar;

    @Before
    public void setUp()
    {
        this.foo = new StringValue("foo");
        this.bar = new StringValue("bar");
    }

    @Test
    public void testDefaultValue()
    {
        assertEquals(new StringValue().getValue(), "");
    }

    @Test
    public void testToString() {
        assertEquals(this.foo.toString(), "foo");
    }

    @Test
    public void testGetType()
    {
        assertTrue(new StringValue().getType() instanceof StringType);
    }

    @Test
    public void testClone() throws CloneNotSupportedException {
        StringValue clone = (StringValue) this.bar.clone();
        clone.setValue("foo");
        assertNotEquals(clone.getValue(), this.bar.getValue());
    }

    @Test
    public void TestEquals() {
        assertEquals(this.foo, new StringValue("foo"));
        assertNotEquals(this.foo, this.bar);
    }

    @Test(expected = IllegalComparisonException.class)
    public void TestIllegalEquals() {
        assertNotEquals(this.foo, new Object());
    }

    @Test(expected = IllegalComparisonException.class)
    public void CannotCompareString() {
        assertTrue(this.foo.compareTo(this.bar) > 0);
    }
}
