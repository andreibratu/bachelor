package service;

import lombok.NoArgsConstructor;

import java.util.Random;

@NoArgsConstructor
public class RandomService
{
    private static final Random random = new Random();

    public static int generateRandomInt(int low, int high)
    {
        return random.ints(low, high).limit(1).sum();
    }

    public static double generateRandomDouble(double low, double high)
    {
        return random.doubles(low, high).limit(1).sum();
    }

    public static String generateRandomString(int length)
    {
        int leftLimit = 97; // letter 'a'
        int rightLimit = 122; // letter 'z'

        return random.ints(leftLimit, rightLimit + 1)
                .limit(length)
                .collect(StringBuilder::new, StringBuilder::appendCodePoint, StringBuilder::append)
                .toString();
    }
}
