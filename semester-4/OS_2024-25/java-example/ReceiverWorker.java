import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.RandomAccessFile;

public class ReceiverWorker extends Thread{
    BufferedReader reader;
    BufferedWriter fileWriter;
    RandomAccessFile raf;

    ReceiverWorker(BufferedReader reader, BufferedWriter fileWriter, RandomAccessFile raf){
        this.reader = reader;
        this.fileWriter = fileWriter;
        this.raf = raf;
    }

    public void run(){
            try {
                while (true) {
                    String line;
                    System.out.println("listening for messages..");
                    raf.write(0);
                    while ((line = reader.readLine()) != null){
                        System.out.println(line);
                        fileWriter.write(line + '\n');
                        fileWriter.flush();
                        try {
                            raf.seek(0);
                            int count = raf.read();
//                            System.out.println(count);
                            raf.seek(0);
                            raf.write(count + 1);
                        } catch (IOException e){
                        }
                    }
                }
            } catch (IOException e) {
                System.out.println("Socket connection is closed. Terminating receiver worker.");
                getTotalMessages();
            }
    }

    public void getTotalMessages(){
        try {
            raf.seek(0);
            int count = raf.read();
            System.out.printf("total messages received: %d\n", count);
            raf.close();
            fileWriter.close();
            reader.close();
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }
}
