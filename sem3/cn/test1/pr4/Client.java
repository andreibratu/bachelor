// 3.   A client sends to the server a string.
// The server returns the reversed string to the client

import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {

    public static void main(String[] args) throws IOException
    {
        Socket clientSocket = new Socket("127.0.0.1", 5555);

        System.out.println("Input a query");
        Scanner keyboard = new Scanner(System.in);
        String query = keyboard.nextLine();

        clientSocket.getOutputStream().write(ByteBuffer.allocate(4).putInt(query.length()+1).array());
        clientSocket.getOutputStream().write(query.getBytes());

        String answer = new String(
                clientSocket.getInputStream().readNBytes(query.length()+1), StandardCharsets.US_ASCII);
        System.out.println(answer);
    }
}
