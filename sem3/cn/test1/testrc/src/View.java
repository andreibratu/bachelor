import java.io.IOException;
import java.util.Scanner;

public class View {

    public static void main(String[] args) throws IOException {
	    Connection connection = new Connection("172.30.119.227", 1234);
	    Controller controller = new Controller(connection);
		Scanner keyboard = new Scanner(System.in);
		String input;

	    controller.join();

	    while(controller.isGameRunning())
		{
			controller.readState();
			String cWord = controller.getCurrentWord();
			System.out.println("Current word is: " + cWord);
			if(controller.isPlayerTurn())
			{
				System.out.println("It is your turn to pick a word!");
				System.out.println("Input \'fail\' if you are out of ideas");
				do {
					System.out.println("Input: ");
					input = keyboard.nextLine();
				} while(!cWord.substring(cWord.length()-2).equals(input.substring(input.length()-2)));
				controller.submitWord(input);
			}
			else
			{
				System.out.println("Waiting for other players..");
			}
		}
    }
}
