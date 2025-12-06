import java.io.*;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

public class TemperatureSensor {
    private static final String FILE_PATH = "/temperature/temperature.txt";
    private static final Random random = new Random();

    public static void main(String[] args) {
        Timer timer = new Timer();
        
        TimerTask task = new TimerTask() {
            public void run() {
                try {
                    StringBuilder temperatures = new StringBuilder();
                    for (int i = 0; i < 5; i++) {
                        int temp = 5 + random.nextInt(46); // 5 to 50 inclusive
                        temperatures.append(temp).append(" ");
                    }

                    FileWriter fw = new FileWriter(FILE_PATH, true);
                    BufferedWriter bw = new BufferedWriter(fw);
                    bw.write(temperatures.toString());
                    bw.newLine();
                    bw.close();
                    fw.close();
                    System.out.println("Wrote temperatures: " + temperatures);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };

        timer.schedule(task, 0, 30 * 1000);
    }
}