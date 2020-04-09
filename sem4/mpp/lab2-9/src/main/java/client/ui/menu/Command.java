package client.ui.menu;

public class Command
{
    public final Integer index;
    public final String text;
    public final Runnable runnable;

    Command(Integer index, String text, Runnable runnable) {
        this.index = index;
        this.text = text;
        this.runnable = runnable;
    }

    @Override
    public String toString() {
        return String.join(". ", index.toString(), text);
    }

    public void execute() {
        this.runnable.run();
    }
}
