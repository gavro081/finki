import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class SenderWorker extends Thread{
    BufferedWriter writer;

    SenderWorker(BufferedWriter writer) {
        this.writer = writer;
    }

    public void run(){
        try {
            while (true) {
            BufferedReader msgWriter = new BufferedReader(new InputStreamReader(System.in));
                String input = msgWriter.readLine() + '\n';
                if (input.contains("exit")){
                    msgWriter.close();
                    writer.close();
                    System.out.println("Sender worker is closed.");
                    break;
                }
                writer.write(input);
                writer.flush();
            }
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
