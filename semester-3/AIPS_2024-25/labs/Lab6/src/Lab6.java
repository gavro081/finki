import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Lab6 {
    static class Person{
        String name;
        String surname;
        int budget;
        String ip;
        String time;
        String city;
        int price;

        public Person(String name, String surname, int budget, String ip, String time, String city, int price) {
            this.name = name;
            this.price = price;
            this.surname = surname;
            this.budget = budget;
            this.time = time;
            this.ip = ip;
            this.city = city;
        }
        static void printPerson(Person p){
            System.out.println(p.name + " " + p.surname + " with salary " +
                    p.budget + " from address " +
                    p.ip + " who logged in at " + p.time);
        }

        static Person findMin(ArrayList<Person> people){
            Person ans = null;
            int minh = Integer.MAX_VALUE;
            int minm = Integer.MAX_VALUE;
            for (int i = 0; i < people.size(); i++) {
                Person currperson = people.get(i);
                String []time = currperson.time.split(":");
                int h = Integer.parseInt(time[0]);
                int m = Integer.parseInt(time[1]);
                if ((h < minh) || (h == minh && m < minm)){
                    minh = h;
                    minm = m;
                    ans = currperson;
                }
            }
            return ans;
        }
    }

    static void helper(HashMap<String, ArrayList<Person>> map, String ip){
        System.out.println("IP network: " + ip + " has the following number of users:");
        ArrayList<Person> people = map.get(ip);
        System.out.println(people.size());
        System.out.println("The user who logged on earliest after noon from that network is:");
        Person.printPerson(Person.findMin(people));
    }
    public static void main(String []args){
        Scanner in = new Scanner(System.in);
        HashMap<String, ArrayList<Person>> map = new HashMap<>();
        int n = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n; i++) {
            String []parts = in.nextLine().split("\\s+");
            String []octets = parts[3].split("\\.");
            String ip = octets[0] + "." + octets[1] + '.' + octets[2];
            if (Integer.parseInt(parts[4].split(":")[0]) < 12) continue;
            Person p = new Person(parts[0], parts[1], Integer.parseInt(parts[2]),
                    parts[3], parts[4], parts[5],Integer.parseInt(parts[6]));
            ArrayList<Person> people = map.getOrDefault(ip, new ArrayList<>());
            people.add(p);
            map.put(ip, people);
        }
        in.nextLine();
        int m = in.nextInt();
        in.nextLine();
        for (int i = 0; i < m; i++) {
            String []octets = in.nextLine().split("\\s+")[3].split("\\.");
            String ip = octets[0] + "." + octets[1] + '.' + octets[2];
            helper(map, ip);
        }

    }
}
