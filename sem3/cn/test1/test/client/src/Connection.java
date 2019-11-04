import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Connection
{
    private Socket clientSocket;

    public void writeInteger(int value) throws IOException
    {
        // Write an integer to socket, integer has size of 4 bytes
        this.clientSocket.getOutputStream().write(ByteBuffer.allocate(4).putInt(value).array());
    }

    public int readInteger() throws IOException
    {
        // Read 4 bytes from socket, interpret them as integer
        byte[] response = this.clientSocket.getInputStream().readNBytes(4);
        return ByteBuffer.wrap(response).getInt();
    }

    public Connection(String host, int port) throws IOException
    {
        // Connect to server's socket
        this.clientSocket = new Socket(host, port);
    }

    public void closeConnection() throws IOException
    {
        this.clientSocket.close();
    }
}
