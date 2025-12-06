import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Server extends Thread {
    int port;
    static final Map<Integer, ServerWorker> clients = new ConcurrentHashMap<>();

    public Server(int port){
        this.port = port;
    }

    public static Map<Integer, ServerWorker> getClients(){ return clients; }

    public void run(){
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
            System.out.println("server waiting for connection..");
            while (true){
                Socket socket = serverSocket.accept();
                System.out.println("accepted connection");
                new ServerWorker(socket, clients).start();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
//    new Server(5005).start();
        String key = System.getenv("KEY");
        System.out.println(key);
    }
}