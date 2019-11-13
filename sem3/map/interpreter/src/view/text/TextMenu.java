package view.text;

import view.text.command.Command;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private Map<String, Command> commands;

    public TextMenu() {
        commands = new HashMap<>();
    }

    public void addCommand(Command c)
    {
        commands.put(c.getKey(), c);
    }

    private void printMenu()
    {
        System.out.println("===\nMENU\n===");
        for (Command com : commands.values()) {
            String line = String.format("%4s : %s", com.getKey(), com.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.print("Input the option: ");
            String key = scanner.nextLine();
            Command command = commands.get(key);
            if (command == null)
            {
                System.out.println("Invalid Option..");
                continue;
            }
            command.execute();
        }
    }
}