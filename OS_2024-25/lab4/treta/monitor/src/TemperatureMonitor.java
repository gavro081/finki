import java.io.*;
import java.util.Timer;
import java.util.TimerTask;

public class TemperatureMonitor {
    private static final String INPUT_FILE = "/temperature/temperature.txt";
    private static final String OUTPUT_FILE = "/temperaturelevel/temperaturelevel.txt";

    public static void main(String[] args) {
        double lowTemp = Double.parseDouble(System.getenv().getOrDefault("LOW_TEMPERATURE", "19"));
        double mediumTemp = Double.parseDouble(System.getenv().getOrDefault("MEDIUM_TEMPERATURE", "35"));
        double highTemp = Double.parseDouble(System.getenv().getOrDefault("HIGH_TEMPERATURE", "50"));

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
                    if (average >= 5 && average < lowTemp) {
                        level = "Low";
                    } else if (average >= lowTemp && average <= mediumTemp) {
                        level = "Medium";
                    } else if (average > mediumTemp) {
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