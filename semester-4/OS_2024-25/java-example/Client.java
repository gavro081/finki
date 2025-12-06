import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
public class Client extends Thread{
    String address;
    int port;
    int index = 231136;

    Client(String address, int port){
        this.address = address;
        this.port = port;
    }

    Client(String address, int port, int index){
        this.address = address;
        this.port = port;
        this.index = index;
    }


    public void run() {
        Socket socket = null;
        try {
            socket = new Socket(InetAddress.getByName(address), port);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        BufferedReader reader = null;
        BufferedWriter writer = null;
        BufferedWriter fileWriter = null;
        while (true) {
            try {
                reader = new BufferedReader(
                        new InputStreamReader(socket.getInputStream())
                );
                writer = new BufferedWriter(
                        new OutputStreamWriter(socket.getOutputStream())
                );
                String filename = "chatlog" + index + ".txt";
                fileWriter = new BufferedWriter(
                        new FileWriter(filename, true)
                );
                RandomAccessFile raf = new RandomAccessFile("counter.txt", "rw");
                writer.write("hello:" + index + '\n');
                writer.flush();
                String line = reader.readLine();
                System.out.println(line);
                if (line.contains("Server says: Succesfully logged on to server!")) {
                    System.out.println(reader.readLine());
                        new SenderWorker(writer).start();
                        new ReceiverWorker(reader, fileWriter, raf).start();

                        break;
//                    }
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public static void main(String[] args) {
//    Client client = new Client("194.149.135.49", 9753);
        Client client;
        if (args.length != 1)
            client = new Client("localhost", 5005);
        else {
            int index;
            try {
                index = Integer.parseInt(args[0]);
            } catch (Exception e){
                System.out.println("invalid index. resorting to default...");
                index = 231136;
            }
            client = new Client("localhost", 5005, index);
        }
        client.start();
    }
}



