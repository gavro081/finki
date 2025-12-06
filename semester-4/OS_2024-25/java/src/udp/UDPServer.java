package udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class UDPServer extends Thread {

    private DatagramSocket socket;
    private byte[] buffer;

    public UDPServer(int port) {
        try {
            this.socket = new DatagramSocket(port);
        } catch (SocketException e) {
            e.printStackTrace();
        }
        this.buffer = new byte[256];
    }

    @Override
    public void run() {

        //se kreira prazen paket. Ova go pobaruva receive funkcijata
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

        while (true) {
            try {
                //se predava prazniot paket, vo koj se zapisuvaat podatocite procitani od klientot
                socket.receive(packet);
                //posle receive, packet gi ima istite podatoci sto gi pratil klientot
                String received = new String(packet.getData(), 0, packet.getLength());
                System.out.println("RECEIVED: " + received);
                System.out.println(packet.getAddress().getHostAddress());
                System.out.println(packet.getPort());

                String returnMessage="Hello back";
                byte[] newBuffer= returnMessage.getBytes();

                DatagramPacket newPacket = new DatagramPacket(newBuffer, newBuffer.length,
                        packet.getAddress(), packet.getPort());

                socket.send(newPacket);
            } catch (IOException exception) {
                exception.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        UDPServer server = new UDPServer(4445);
        server.start();
    }
}
