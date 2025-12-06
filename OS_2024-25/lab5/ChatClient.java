import java.io.*;
import java.net.*;

public class ChatClient {

    class ReceiverWorker extends Thread {
        private BufferedReader br;

        public ReceiverWorker(BufferedReader br) {
            this.br = br;
        }

        @Override
        public void run() {
            try {
                System.out.println("listening for messages...");
                String message;
                while ((message = br.readLine()) != null) {
                    System.out.println("Received: " + message);
                }
            } catch (IOException e) {
                System.out.println("Error: " + e.getMessage());
            } finally {
                System.out.println("Receiving Thread is stopped.");
            }
        }
    }

    class SenderWorker extends Thread {
        private BufferedWriter out;
//        private String index;

        public SenderWorker(BufferedWriter out, String index) {
            this.out = out;
//            this.index = index;
        }

        @Override
        public void run() {
            try {
                while (true) {
//                    Scanner scanner = new Scanner(System.in);
                    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                    String input = br.readLine() + '\n';


                    if (input.equalsIgnoreCase("exit")) {
                        break;
                    }

                    out.write(input);
                    out.flush();
                }

            } catch (IOException e) {
                throw new RuntimeException(e);
            } finally {
//                scanner.close();
                System.out.println("Sender Thread is stopped.");
            }
        }
    }

    private static final String SERVER_ADDRESS = "194.149.135.49";
    private static final int SERVER_PORT = 9753;
    private String index;
    private Socket socket;
    private BufferedWriter out;
    private BufferedReader br;
    private ReceiverWorker receiver;
    private SenderWorker sender;

    public ChatClient(){
        this.index = "231136";
    }

    public ChatClient(String index){
        this.index = index;
    }

    public void start() {
        while (true) {
            try {
                socket = new Socket(SERVER_ADDRESS, SERVER_PORT);
                out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                br = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                out.write("hello:" + index + '\n');
                out.flush();

                String response = br.readLine();

                System.out.println(response);

                if (response != null && response.toLowerCase().contains("succes")) {
                    System.out.println("Logged in!");

                    out.write("login:" + index + '\n');
                    out.flush();

                    response = br.readLine();
                    System.out.println(response);

                    if (response != null && response.contains("welcome")) {
                        System.out.println("Hello message sent!");

                        receiver = new ReceiverWorker(br);
                        sender = new SenderWorker(out, index);
                        receiver.start();
                        sender.start();
                        break;
                    } else {
                        System.out.println("Hello not sent. Closing connection...");
                        closeConnection();
                    }
                } else {
                    System.out.println("Unsuccessful login. Trying again...");
                    closeConnection();
                    Thread.sleep(1000);
                }
            } catch (IOException | InterruptedException e) {
                System.out.println("Error: " + e.getMessage());
                closeConnection();
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ie) {
                    ie.printStackTrace();
                }
            }
        }
    }

    private void closeConnection() {
        try {
            if (br != null) br.close();
            if (out != null) out.close();
            if (socket != null) socket.close();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ChatClient client;
        if (args.length == 1) {
            String index = args[0];
            client = new ChatClient(index);
        }
        else {
            client = new ChatClient();
        }
        client.start();
    }
}