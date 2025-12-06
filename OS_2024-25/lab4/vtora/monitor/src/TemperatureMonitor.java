import java.io.*;
import java.util.Timer;
import java.util.TimerTask;

public class TemperatureMonitor {
    private static final String INPUT_FILE = "/data/temperature.txt";
    private static final String OUTPUT_FILE = "/data/temperaturelevel.txt";

    public static void main(String[] args) {
        Timer timer = new Timer();

        TimerTask task = new TimerTask() {
            public void run() {
                try {
                    double sum = 0.0;
                    int count = 0;
                    BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE));
                    String line;
                    while ((line = br.readLine()) != null) {
                        String[] temps = line.trim().split("\\s+");
                        for (String temp : temps) {
                            try {
                                double value = Double.parseDouble(temp);
                                sum += value;
                                count++;
                            } catch (NumberFormatException e) {
                            }
                        }
                    }
                    br.close();

                    double average = (count > 0) ? sum / count : 0.0;

                    String level;
                    if (average >= 5 && average < 19) {
                        level = "Low";
                    } else if (average >= 19 && average <= 35) {
                        level = "Medium";
                    } else if (average > 35) {
                        level = "High";
                    } else {
                        level = "Unknown";
                    }

                    FileWriter fw = new FileWriter(OUTPUT_FILE, true);
                    BufferedWriter bw = new BufferedWriter(fw);
                    bw.write(level);
                    bw.newLine();
                    bw.close();
                    fw.close();
                    System.out.println("Average temperature: " + String.format("%.2f", average) + "°C, Level: " + level);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };

        timer.schedule(task, 0, 60 * 1000);
    }
}
