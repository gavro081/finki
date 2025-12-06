package src.tcp;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread {

    private int port;

    public Server(int port) {
        this.port = port;
    }

    @Override
    public void run() {
        System.out.println("SERVER: starting...");
        ServerSocket serverSocket;

        try {
            serverSocket = new ServerSocket(port); // bara da mu se otvori porta 7000
        } catch (IOException e) {
            //  ako e zafatena portata
            System.err.println(e.getMessage());
            return;
        }

        //navamu, portata e otvorena
        System.out.println("SERVER: started");
        System.out.println("SERVER: waiting for connections...");

        while (true) {
            Socket socketToClient=null;
            try {
                socketToClient = serverSocket.accept();  // go kompletira tcp handshakeot iniciran od klientot
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }

            System.out.println("SERVER: new client - creating new worker thread...");
            //kreira worker thread i mu go predava otvoreniot socket kon klientot
            tcp.Worker w= new tcp.Worker(socketToClient);
            w.start();  //go startuva workerot
        }
    }

    public static void main(String[] args) {
        Server server = new Server(7003);
        server.start();
    }
}