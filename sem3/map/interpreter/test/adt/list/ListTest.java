package adt.list;

import org.junit.Before;
import org.junit.Test;

import java.util.Iterator;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;
import static org.junit.Assert.assertNotEquals;

public class ListTest
{
    private List<Integer> list;

    @Before
    public void setUp()
    {
        this.list = new List<>();
        for(int i = 0; i < 10; i++) list.add(i);
    }

    @Test
    public void testSize()
    {
        assertEquals(this.list.size(), 10);
    }

    @Test
    public void testDelete()
    {
        try {
            this.list.delete(15);
        } catch (EmptyListException e) {
            fail("Should not throw for nonexistent elements");
        }
        assertEquals(this.list.size(), 10);
        try {
            this.list.delete(4);
            assertEquals("Elements should shift left", (int)this.list.get(4), 5);
        } catch (EmptyListException e) {
            fail("Should not throw for existent elements");
        }
    }

    @Test
    @SuppressWarnings("unchecked")
    public void testClone()
    {
        try {
            List<Integer> clone = (List<Integer>) this.list.clone();
            clone.add(9);
            assertNotEquals(clone.size(), this.list.size());

        } catch (CloneNotSupportedException e) {
            fail("Hierarchy should be implementing clone");
        }
    }

    @Test
    public void testIterator()
    {
        Iterator iterator = this.list.iterator();
        int count = 0;
        while(iterator.hasNext())
        {
            iterator.next();
            count++;
        }
        assertEquals(count, this.list.size());
    }
}
