import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

// 6. The client sends to the server a string and a character.
// The server returns to the client a list of all positions in the string where specified character is found.

public class Server {

    private static ArrayList<Integer> solve(String query, Character c)
    {
        ArrayList<Integer> occurrences = new ArrayList<>();
        for(int i = 0 ; i < query.length(); i++)
        {
            if(query.charAt(i) == c) occurrences.add(i);
        }
        return occurrences;
    }

    public static void main(String[] args) {
        try {
            DatagramSocket socket = new DatagramSocket(5555);
            while(true)
            {
                System.out.println("Serving client..");

                DatagramPacket stringLengthPacket = new DatagramPacket(new byte[4], 4);
                socket.receive(stringLengthPacket);
                InetAddress clientAddress = stringLengthPacket.getAddress();
                int clientPort = stringLengthPacket.getPort();
                int length = ByteBuffer.wrap(stringLengthPacket.getData()).getInt();
                System.out.println("Expecting string of length " + length);

                DatagramPacket stringPacket = new DatagramPacket(new byte[length+1], length);
                socket.receive(stringPacket);
                String query = new String(stringPacket.getData(), StandardCharsets.US_ASCII);
                System.out.println("Received string " + query);

                DatagramPacket charPacket = new DatagramPacket(new byte[1], 1);
                socket.receive(charPacket);
                char character = new String(charPacket.getData(), StandardCharsets.US_ASCII).charAt(0);

                List<Integer> positions = solve(query, character);
                System.out.println("Sending " + positions.size() + " occurrences");
                socket.send(new DatagramPacket(
                        ByteBuffer.allocate(4).putInt(positions.size()).array(),
                        4, clientAddress, clientPort
                ));
                for(int x: positions)
                {
                    socket.send(new DatagramPacket(
                            ByteBuffer.allocate(4).putInt(x).array(),
                            4, clientAddress, clientPort
                    ));
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
