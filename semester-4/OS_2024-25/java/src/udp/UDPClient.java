package udp;

import java.io.IOException;
import java.net.*;

public class UDPClient extends Thread {

    private String serverName;
    private int serverPort;

    private DatagramSocket socket;
    private InetAddress address;
    private String message;
    private byte[] buffer;
//  127.0.0.1 --- localhost
    public UDPClient(String serverName, int serverPort, String message) {
        this.serverName = serverName;
        this.serverPort = serverPort;
        this.message = message;

        try {
            this.socket = new DatagramSocket();   // otvarame UDP konekcija
            this.address = InetAddress.getByName("127.0.0.1");  // definirame adresa na server so kogo sakame da komunicirame
        } catch (SocketException | UnknownHostException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        buffer = message.getBytes();
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, serverPort);
        //datagram packet- udp packet

        try {
            socket.send(packet); //ispraka paket

            byte [] newBuffer=new byte[256];
            DatagramPacket receivedPacket = new DatagramPacket(newBuffer, newBuffer.length, address, serverPort);

            socket.receive(receivedPacket);
            System.out.println(new String(receivedPacket.getData(), 0, receivedPacket.getLength()));
            System.out.println(receivedPacket.getAddress().getHostAddress());
            System.out.println(receivedPacket.getPort());
        } catch (IOException exception) {
            exception.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UDPClient client = new UDPClient("localhost", 4445, "Hello :)");
        client.start();
    }
}
