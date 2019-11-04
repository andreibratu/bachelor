import java.io.IOException;
import java.util.Scanner;

// Allow players to guess each other's number in pairs of two

public class Main
{
    private static boolean isValidNumber(int x)
    {
        int count = 0;
        do
        {
            x = x / 10;
            count++;
        }
        while(x != 0);
        return count == 4;
    }

    private static int inputNumber()
    {
        int val = 0;
        Scanner in = new Scanner(System.in);
        while(!isValidNumber(val))
        {
            System.out.println("Please input a four digit number: ");
            val = in.nextInt();
        }
        return val;
    }

    public static void main(String[] args) throws IOException
    {
        Connection connection = new Connection("172.30.119.234", 4444);
        System.out.println("Waiting for opponent..");

        boolean isPlayerOne = connection.readInteger() == 0;
        if (isPlayerOne) System.out.println("You are player one!");
        else System.out.println("You are player two!");

        System.out.println("Please choose your number!");
        int value = inputNumber();
        connection.writeInteger(value);

        connection.readInteger();

        while (true)
        {
            if (isPlayerOne)
            {
                System.out.println("Guess opponent's number!");

                int guess = inputNumber();
                connection.writeInteger(guess);
                System.out.println("Number sent..");

                boolean wasGuessed = connection.readInteger() == 0;

                if (wasGuessed)
                {
                    System.out.println("Congrats, you have guessed the number!");
                    break;
                }
                else
                {
                    System.out.println("That was not it sport!");
                    System.out.println("Your number is being guessed..");

                    boolean opponentGuessed = connection.readInteger() != 0;
                    if (opponentGuessed)
                    {
                        System.out.println("Shame, opponent guessed your number!");
                        break;
                    }
                    else System.out.println("Opponent missed!");
                }
            }
            else
            {
                System.out.println("Your number is being guessed..");

                boolean opponentGuessed = connection.readInteger() != 0;

                if (opponentGuessed)
                {
                    System.out.println("Shame, opponent guessed your number!");
                    break;
                }
                else
                {
                    System.out.println("Guess opponent's number!");

                    int guess = inputNumber();
                    connection.writeInteger(guess);

                    boolean wasGuessed = connection.readInteger() == 0;

                    if (wasGuessed)
                    {
                        System.out.println("Congrats, you have guessed it!");
                        break;
                    }
                }
            }
        }
        connection.closeConnection();
    }
}
