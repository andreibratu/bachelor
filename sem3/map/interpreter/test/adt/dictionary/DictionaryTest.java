package adt.dictionary;

import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertFalse;

public class DictionaryTest
{
    private Dictionary<String, Integer> tester;

    @Before
    public void setUp()
    {
        tester = new Dictionary<>();
    }

    @Test(expected = NullPointerException.class)
    public void invalidNullKey()
    {
        tester.put(null, 5);
    }

    @Test(expected = NullPointerException.class)
    public void invalidNullValue()
    {
        tester.put("foobar", null);
    }

    @Test
    public void insertValueDictionary()
    {
        tester.put("foo", 7);
        try {
            int val = tester.lookUp("foo");
            assertEquals(val, 7);
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        }
    }

    @Test(expected = InvalidKeyException.class)
    public void getNonExistentKey() throws InvalidKeyException
    {
        tester.lookUp("foo");
    }

    @Test
    public void removeKey() throws InvalidKeyException
    {
        tester.put("foo", 7);
        tester.remove("foo");
        assertFalse(tester.isDefined("foo"));
    }

    @Test(expected = InvalidKeyException.class)
    public void removeNonExistentKey() throws InvalidKeyException
    {
        tester.remove("foo");
    }
}
