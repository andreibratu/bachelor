// 1. A client sends to the server an array of numbers.
// Server returns the sum of the numbers.

import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Scanner;

class Client
{
    public static void main(String[] args) throws Exception
    {
        DatagramSocket clientSocket = new DatagramSocket();
        InetAddress IPAddress = InetAddress.getByName("localhost");

        Scanner keyboard = new Scanner(System.in);
        System.out.println("How many numbers:");
        int count = keyboard.nextInt();

        DatagramPacket countPacket = new DatagramPacket(
                ByteBuffer.allocate(4).putInt(count).array(),
                4, IPAddress, 5555);
        clientSocket.send(countPacket);

        while(count != 0)
        {
            System.out.println("Input next number:");
            int number = keyboard.nextInt();

            DatagramPacket numberPacket = new DatagramPacket(
                    ByteBuffer.allocate(4).putInt(number).array(),
                    4, IPAddress, 5555);
            clientSocket.send(numberPacket);

            count--;
        }

        DatagramPacket serverResponse = new DatagramPacket(new byte[4], 4);
        clientSocket.receive(serverResponse);
        Integer sum = ByteBuffer.wrap(serverResponse.getData()).getInt();
        System.out.println(sum);
    }
}
