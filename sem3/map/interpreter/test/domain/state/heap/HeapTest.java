package domain.state.heap;

import domain.type.IntegerType;
import domain.value.IntegerValue;
import domain.value.ReferenceValue;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;
import static org.junit.Assert.assertNotEquals;

public class HeapTest
{
    private DictionaryHeap mockHeap;

    @Before
    public void setUp()
    {
        this.mockHeap = new DictionaryHeap();
    }

    @Test
    public void testAllocate()
    {
        ReferenceValue ref = new ReferenceValue(new IntegerType());
        ref.setValue(mockHeap.allocate(new IntegerValue(7)));
        assertNotEquals(0, (int)ref.getValue());
        try {
            assertEquals(mockHeap.dereference(ref).getValue(), 7);
        } catch (InvalidMemoryAddressException e) {
            fail("It should properly dereference the allocated value");
        }
    }

    @Test
    public void testWrite()
    {
        ReferenceValue ref = new ReferenceValue(5, new IntegerType());
        try
        {
            mockHeap.write(ref, new IntegerValue(5));
        }
        catch (Exception e)
        {
            ref.setValue(mockHeap.allocate(new IntegerValue(6)));
            assertEquals((int)ref.getValue(), 1);
            try
            {
                mockHeap.write(ref, new IntegerValue(10));
                return;
            } catch (Exception e2)
            {
                fail(e2.getMessage());
            }
        }
        fail("Should not be able to write to unallocated address");
    }
}
