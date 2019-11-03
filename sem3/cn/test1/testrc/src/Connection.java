import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class Connection
{
    private Socket clientSocket;

    public void writeInteger(int value) throws IOException
    {
        this.clientSocket.getOutputStream().write(ByteBuffer.allocate(4).putInt(value).array());
    }

    public void writeString(String value) throws IOException
    {
        this.clientSocket.getOutputStream().write(value.getBytes());
    }

    public int readInteger() throws IOException
    {
        byte[] response = this.clientSocket.getInputStream().readNBytes(4);
        return ByteBuffer.wrap(response).getInt();
    }

    public boolean readByte() throws IOException
    {
        return clientSocket.getInputStream().readNBytes(1)[0] == 1;
    }

    public String readString() throws IOException
    {
        return new String(clientSocket.getInputStream().readNBytes(101), StandardCharsets.US_ASCII);
    }

    public Connection(String host, int port) throws IOException
    {
        this.clientSocket = new Socket(host, port);
    }

    public void closeConnection() throws IOException
    {
        this.clientSocket.close();
    }
}
