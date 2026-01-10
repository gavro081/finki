package juni2023.z1_delivery;

import java.util.*;

/*
YOUR CODE HERE
DO NOT MODIFY THE interfaces and classes below!!!
*/


class DeliveryPerson implements Comparable<DeliveryPerson>{
    private final String id;
    private final String name;
    private Location location;
    private float earnings = 0;
    private int orders = 0;

    public DeliveryPerson(String id, String name, Location location) {
        this.id = id;
        this.name = name;
        this.location = location;
    }

    public Location getLocation() {
        return location;
    }

    public float getEarnings(){
        return earnings;
    }


    public int getOrders() {
        return orders;
    }

    void processOrder(Location userLocation, Location restaurantLocation){
        int bonus = (restaurantLocation.distance(this.location)) / 10 * 10;
        earnings += 90 + bonus;
        orders++;
        this.location = userLocation;
    }

    @Override
    public int compareTo(DeliveryPerson o) {
        int diff = Double.compare(o.earnings, earnings);
        if (diff != 0) return diff;
        return o.id.compareTo(id);
    }

    public String toString(){
        return String.format("ID: %s Name: %s Total deliveries: %d Total delivery fee: %.2f Average delivery fee: %.2f",
               id, name, orders, earnings,
                orders == 0 ? 0 : earnings / orders);
    }

    public String getId() {
        return id;
    }
}

class Restaurant implements Comparable<Restaurant>{
    private final String id;
    private final String name;
    private final Location location;
    private final List<Float> orderPrices;

    public Restaurant(String id, String name, Location location) {
        this.id = id;
        this.name = name;
        this.location = location;
        this.orderPrices = new ArrayList<>();
    }

    public Location getLocation() {
        return location;
    }

    public String getId() {
        return id;
    }

    public void processOrder(float cost){
        orderPrices.add(cost);
    }

    public double getSortCriteria(){
        return orderPrices.isEmpty() ? 0 :
                orderPrices.stream().mapToDouble(d -> (double)d).average().getAsDouble();
    }

    @Override
    public int compareTo(Restaurant o) {
        double a = getSortCriteria();
        double b = o.getSortCriteria();
        if (a != b) return Double.compare(b,a);
        return o.id.compareTo(id);
    }

    public String toString(){
        return String.format("ID: %s Name: %s Total orders: %d Total amount earned: %.2f Average amount earned: %.2f",
                id, name, orderPrices.size(),
                orderPrices.isEmpty() ? 0 : orderPrices.stream().mapToDouble(d -> d).sum(),
                orderPrices.isEmpty() ? 0 : orderPrices.stream().mapToDouble(d -> d).average().getAsDouble());
    }
}

class User implements Comparable<User>{
    private final String id;
    private final String name;
    private final Map<String, Location> addresses;
    private final List<Float> orders;

    public User(String id, String name) {
        this.id = id;
        this.name = name;
        this.addresses = new HashMap<>();
        orders = new ArrayList<>();
    }

    public void addAddress(String name, Location location){
        addresses.put(name, location);
    }

    public Location getLocationByName(String name){
        return addresses.get(name);
    }


    public double getSortCriteria() {
        return orders.isEmpty() ? 0
                : orders.stream().mapToDouble(d -> -(double)d).sum();
    }

    @Override
    public int compareTo(User o) {
        double a = getSortCriteria();
        double b = o.getSortCriteria();
        if (a != b) return Double.compare(a,b);
        return o.id.compareTo(id);
    }

    public String getId() {
        return id;
    }

    public void processOrder(float cost){
        orders.add(cost);
    }

    public String toString(){
        return String.format("ID: %s Name: %s Total orders: %d Total amount spent: %.2f Average amount spent: %.2f",
                id, name, orders.size(),
                orders.isEmpty() ? 0 : orders.stream().mapToDouble(d -> d).sum(),
                orders.isEmpty() ? 0 : orders.stream().mapToDouble(d -> d).average().getAsDouble());
    }

}

class DeliveryApp {
    private final String name;
    private final Map<String, DeliveryPerson> deliveryPersonMap;
    private final Map<String, Restaurant> restaurantMap;
    private final Map<String, User> userMap;

    public DeliveryApp(String name) {
        this.name = name;
        this.deliveryPersonMap = new HashMap<>();
        this.restaurantMap = new HashMap<>();
        this.userMap = new HashMap<>();
    }

    void registerDeliveryPerson (String id, String name, Location currentLocation){
        deliveryPersonMap.put(id, new DeliveryPerson(id, name, currentLocation));
    }

    void addRestaurant (String id, String name, Location location){
        restaurantMap.put(id, new Restaurant(id, name, location));
    }

    void addUser (String id, String name){
        userMap.put(id, new User(id, name));
    }

    void addAddress (String id, String addressName, Location location){
        userMap.get(id).addAddress(addressName, location);
    }

    void orderFood(String userId, String userAddressName, String restaurantId, float cost){
        User user = userMap.get(userId);
        Location userLocation = user.getLocationByName(userAddressName);
        Restaurant restaurant = restaurantMap.get(restaurantId);
        Location restaurantLocation = restaurant.getLocation();

        DeliveryPerson deliveryPerson = deliveryPersonMap.values().stream()
                .min(Comparator.comparing((DeliveryPerson p) -> p.getLocation().distance(restaurantLocation))
                        .thenComparing(DeliveryPerson::getOrders))
                .get();

        // ne znam dali treba so observer ova ili ne ama ja go pravam bez
        deliveryPerson.processOrder(userLocation, restaurantLocation);
        user.processOrder(cost);
        restaurant.processOrder(cost);
    }

    void printUsers(){
        userMap.values().stream()
                .sorted()
                .forEach(System.out::println);
    }

    void printRestaurants(){
        restaurantMap.values().stream()
                .sorted()
                .forEach(System.out::println);
    }

    void printDeliveryPeople(){
        deliveryPersonMap.values().stream()
                .sorted()
                .forEach(System.out::println);
    }
}

interface Location {
    int getX();

    int getY();

    default int distance(Location other) {
        int xDiff = Math.abs(getX() - other.getX());
        int yDiff = Math.abs(getY() - other.getY());
        return xDiff + yDiff;
    }
}

class LocationCreator {
    public static Location create(int x, int y) {

        return new Location() {
            @Override
            public int getX() {
                return x;
            }

            @Override
            public int getY() {
                return y;
            }
        };
    }
}

public class DeliveryAppTester {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String appName = sc.nextLine();
        DeliveryApp app = new DeliveryApp(appName);
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(" ");

            if (parts[0].equals("addUser")) {
                String id = parts[1];
                String name = parts[2];
                app.addUser(id, name);
            } else if (parts[0].equals("registerDeliveryPerson")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.registerDeliveryPerson(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("addRestaurant")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.addRestaurant(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("addAddress")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.addAddress(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("orderFood")) {
                String userId = parts[1];
                String userAddressName = parts[2];
                String restaurantId = parts[3];
                float cost = Float.parseFloat(parts[4]);
                app.orderFood(userId, userAddressName, restaurantId, cost);
            } else if (parts[0].equals("printUsers")) {
                app.printUsers();
            } else if (parts[0].equals("printRestaurants")) {
                app.printRestaurants();
            } else {
                app.printDeliveryPeople();
            }

        }
    }
}
