package service;

import org.junit.Assert;
import org.junit.Test;

public class RandomServiceTest {
    @Test
    public void assertGenerateSingleRandomNumber()
    {
        Assert.assertEquals(6, RandomService.generateRandomInt(6, 7));
    }

    @Test
    public void assertDoubleGeneration()
    {
        for(int idx = 0; idx < 10000; idx++)
        {
            double generated = RandomService.generateRandomDouble(5, 6);
            Assert.assertTrue(5 <= generated && generated < 6);
        }
    }
}
