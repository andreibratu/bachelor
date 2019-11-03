import java.io.IOException;

public class Controller
{
    private Connection connection;
    private State state;
    private int playerId;

    public Controller(Connection connection)
    {
        this.connection = connection;
        this.state = new State(-1, "", true);
    }

    public boolean isGameRunning()
    {
        return this.state.isRunning;
    }

    public void readPlayerId() throws IOException
    {
        this.playerId = this.connection.readInteger();
    }

    public void join() throws IOException {
        this.connection.writeString("join");
        this.readPlayerId();
    }

    public void submitWord(String word) throws IOException
    {
        this.connection.writeString(word);
    }

    public String getCurrentWord()
    {
        return this.state.lastWord;
    }

    public boolean isPlayerTurn()
    {
        return this.playerId == this.state.cId;
    }

    public void readState() throws IOException {
        int cId = this.connection.readInteger();
        boolean isRunning = this.connection.readByte();
        String lastWord = this.connection.readString();
        this.state = new State(cId, lastWord, isRunning);
    }
}
