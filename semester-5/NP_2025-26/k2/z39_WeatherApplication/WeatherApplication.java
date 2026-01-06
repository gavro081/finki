package k2.z39_WeatherApplication;

import java.util.*;

interface IObserver {
    void display(float temperature, float humidity, float pressure);

    // za da bide rasporedot kako vo testovite
    int priority();
}

class WeatherDispatcher{
    private float temperature;
    private float humidity;
    private float pressure;

    private Set<IObserver> observers;

    public WeatherDispatcher(){
        observers = new TreeSet<>(Comparator.comparing(IObserver::priority));
    }

    public void setMeasurements(float temperature, float humidity, float pressure){
        this.temperature = temperature;
        this.humidity = humidity;
        this.pressure = pressure;

        for (var o : observers) o.display(temperature, humidity, pressure);
        System.out.println();
    }

    public void register(IObserver observer){
        this.observers.add(observer);
    }

    public void remove(IObserver observer){
        observers.remove(observer);
    }
}

class CurrentConditionsDisplay implements IObserver{
    CurrentConditionsDisplay(WeatherDispatcher weatherDispatcher){
        weatherDispatcher.register(this);
    }

    @Override
    public void display(float temperature, float humidity, float pressure) {
        System.out.printf("Temperature: %.1fF%n", temperature);
        System.out.printf("Humidity: %.1f%%%n", humidity);
    }

    @Override
    public int priority() {
        return 0;
    }
}

class ForecastDisplay implements IObserver{
    private float lastPressure = 0.0f;

    ForecastDisplay(WeatherDispatcher weatherDispatcher){
        weatherDispatcher.register(this);
    }

    @Override
    public void display(float temperature, float humidity, float pressure) {
        if (pressure < lastPressure){
            System.out.println("Forecast: Cooler");
        } else if (pressure == lastPressure){
            System.out.println("Forecast: Same");
        } else System.out.println("Forecast: Improving");
        lastPressure = pressure;
    }

    @Override
    public int priority() {
        return 1;
    }
}

public class WeatherApplication {

    public static void main(String[] args) {
        WeatherDispatcher weatherDispatcher = new WeatherDispatcher();

        CurrentConditionsDisplay currentConditions = new CurrentConditionsDisplay(weatherDispatcher);
        ForecastDisplay forecastDisplay = new ForecastDisplay(weatherDispatcher);

        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            String[] parts = line.split("\\s+");
            weatherDispatcher.setMeasurements(Float.parseFloat(parts[0]), Float.parseFloat(parts[1]), Float.parseFloat(parts[2]));
            if(parts.length > 3) {
                int operation = Integer.parseInt(parts[3]);
                if(operation==1) {
                    weatherDispatcher.remove(forecastDisplay);
                }
                if(operation==2) {
                    weatherDispatcher.remove(currentConditions);
                }
                if(operation==3) {
                    weatherDispatcher.register(forecastDisplay);
                }
                if(operation==4) {
                    weatherDispatcher.register(currentConditions);
                }

            }
        }
    }
}
