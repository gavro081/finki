package tcp;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;    //tcp komunikacija


public class Client extends Thread {

    private int serverPort;

    public Client(int serverPort) {
        this.serverPort = serverPort;
    }

    @Override
    public void run() {
        Socket socket;

        try {
            //otvara tcp konekcija do server koj slusa na dadena IP adr. i porta
            socket = new Socket(InetAddress.getByName("127.0.0.1"), 7003);

            //prikacuva dva strima na socketot
            //input stream za da cita podatoci od tcp
            //output stream za da praka podatoci na tcp
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            //isprakanje na poraka preku socket
            String message="Hello from client!";
            bw.write(message);
            bw.newLine();
            bw.flush();
            System.out.println("Message to server sent! "+ message);

            //primanje na poraka preku socket
            String returnMessage=br.readLine();
            System.out.println(returnMessage);

            bw.write("Closing connection");
            bw.newLine();
            bw.flush();

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Client client = new Client(7000);
        client.start();
    }
}
