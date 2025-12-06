import java.io.*;
import java.net.Socket;
import java.util.Map;

record ParsedInput(String message, int index) {}

public class ServerWorker extends Thread {
    Socket socket;
    Map<Integer, ServerWorker> clients;
    int index;
    BufferedWriter writer;

    ServerWorker(Socket socket, Map<Integer, ServerWorker> clients){
        this.socket = socket;
        this.clients = clients;
    }

    public void run(){
        try {
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            String line = reader.readLine();
            try {
                index = parseFirst(line);
                clients.put(index, this);
                writer.write("Server says: Succesfully logged on to server!\n");
                writer.flush();
                writer.write("hello " + index + "\n");
                writer.flush();

            }
            catch (Exception e){
                writer.write("rejecting connection. \n");
                writer.flush();
                writer.close();
                reader.close();
                return;
            }

            while ((line = reader.readLine()) != null){
                try {
                    System.out.println("Received " + line + " from " + index);
                    ParsedInput query = parse(line);
                    ServerWorker targetWorker = clients.get(query.index());
                    if (targetWorker != null && targetWorker.writer != null){
                        targetWorker.writer.write(index + " said " + query.message() + '\n');
                        targetWorker.writer.flush();
                    } else {
                        writer.write("client with index " + query.index() + " is not logged in\n");
                        writer.flush();
                    }
                } catch (Exception e){
                    System.out.println("error parsing. continuing");
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            clients.remove(index);
            try{
                if (writer != null) writer.close();
                if (socket != null) socket.close();
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }

    public int parseFirst(String line) throws Exception {
        String[] parts = line.split(":");
        int index = Integer.parseInt(parts[1]);
        if (parts[0].equals("hello") && index >= 200000 && index < 240000)
            return Integer.parseInt(parts[1]);
        throw new Exception("invalid message / index");
    }
    public ParsedInput parse(String line) throws Exception {
        String[] parts = line.split(":");
        int index = Integer.parseInt(parts[0]);
        if (index >= 200000 && index < 240000)
            return new ParsedInput(parts[1], Integer.parseInt(parts[0]));
        throw new Exception("invalid index");
    }


}

