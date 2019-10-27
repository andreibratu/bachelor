// 8. The client sends to the server two arrays of integers.
// The server returns an arrays containing the common numbers found in both arrays.

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.ArrayList;

public class Server {

    private static ArrayList<Integer> common(ArrayList<Integer> a, ArrayList<Integer> b)
    {
        ArrayList<Integer> answer = new ArrayList<>();
        for(int x: a) if(b.contains(x)) answer.add(x);
        return answer;
    }

    private static int readInt(Socket client) throws IOException
    {
        return ByteBuffer.wrap(client.getInputStream().readNBytes(4)).getInt();
    }

    private static ArrayList<Integer> readArray(int n, Socket client) throws IOException
    {
        ArrayList<Integer> array = new ArrayList<>();
        while (n != 0)
        {
            array.add(readInt(client));
            n--;
        }
        return array;
    }

    public static void main(String[] args) throws IOException
    {
        ServerSocket serverSocket = new ServerSocket(5555);
        System.out.println("Waiting for client");
        Socket clientSocket = serverSocket.accept();

        System.out.println("Reading first list");
        int firstListLength = readInt(clientSocket);
        ArrayList<Integer> firstList = readArray(firstListLength, clientSocket);
        for(int x: firstList) System.out.println(x);

        System.out.println("Reading second list");
        int secondListLength = readInt(clientSocket);
        ArrayList<Integer> secondList = readArray(secondListLength, clientSocket);
        for(int x: secondList) System.out.println(x);

        ArrayList<Integer> commonList = common(firstList, secondList);

        System.out.println("Writing " + commonList.size() + " numbers to socket");
        clientSocket.getOutputStream().write(commonList.size());
        for(int x: commonList) clientSocket.getOutputStream().write(ByteBuffer.allocate(4).putInt(x).array());

        clientSocket.close();
        serverSocket.close();
    }
}
