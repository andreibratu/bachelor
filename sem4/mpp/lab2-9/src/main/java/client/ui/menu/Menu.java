package client.ui.menu;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Menu
{
    private final List<Command> commands = new ArrayList<>();

    public Command getCommand(Integer index)
    {
        return commands.get(index);
    }

    public void addCommand(String text, Runnable runnable)
    {
        commands.add(new Command(commands.size(), text, runnable));
    }

    @Override
    public String toString()
    {
        return commands.stream().map(Command::toString).collect(Collectors.joining(System.lineSeparator()));
    }

}
