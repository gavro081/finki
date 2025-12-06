// Следните класи веќе се импортирани, не е дозволено копирање на класи овде,
// директно користејте ги како кога седостапни во други локални фајлови:
// The following classes are already imported, copying classes here is not allowed,
// use them directly as when they are available in other local files:

// CBHT, OBHT, MapEntry, SLLNode веќе се импортирани
// CBHT, OBHT, MapEntry, SLLNode are already imported
import java.util.Scanner;

// Овде креирајте ги помошните класи за клуч и вредност
// Исполнете ги барањата од текстот за toString методите
// Дополнително осигурете се дека вашата клуч класа ќе ги имплементира потребните
// hashCode и equals методи

// Create the helper classes for key and value here
// Fulfill the requirements from the text for the toString methods
// Additionally, make sure that your key class will implement the required
// hashCode and equals methods
class Person {
    // поставете ги потребните полиња овде
    // declare the required fields here
    String name;
    int age;

    // имплементирајте соодветен конструктор
    // implement the constructor
    Person(String n, int age) {
        name = n;
        this.age = age;
    }

    Person(Person o){
        this.name = o.name;
        this.age = o.age;
    }

    @Override
    public String toString() {
        // имплементирајте го toString методот според барањето во текстот
        // implement the toString method as requested in the text
        return "<" + name + ", " + age + ">";
    }

    // имплементирајте ги следните два методи за да работи табелата правилно
    // implement the following two methods to make the table work properly
    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        Person p = new Person((Person) o);
        return this.name.equals(p.name) && this.age == p.age;
    }
    @Override
    public int hashCode() {
        return age * name.charAt(0);
    }
}

class Project {
    int time;
    int pay;

    Project(int t, int p) {
        time = t;
        pay = p;
    }

    int getPay(){
        return time * pay;
    }

    @Override
    public String toString() {
        return "<" + time + ", " + pay + ">";
    }
}

public class Doma6 {
    public static void main(String[] args) {
        // Креирајте ја табелата според барањата
        // Create the table as requested
        CBHT<Person,Project> table = new CBHT<>(10);


        // Прочитајте ги податоците од влезот и пополнете ја табелата
        // Read the input data and fill the table
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n; i++) {
            String line = in.nextLine();
            String []parts = line.split(" ");
            Person p = new Person(parts[0], Integer.parseInt(parts[1]));
            Project pr = new Project(Integer.parseInt(parts[2]), Integer.parseInt(parts[3]));
            if (table.search(p) == null){
                table.insert(p, pr);
            }
            else {
                SLLNode<MapEntry<Person, Project>> currbest = table.search(p);
                if (pr.getPay() > currbest.element.value.getPay())
                    table.insert(p, pr);
            }
        }

        // отпечатете ја вашата табела
        // print your table
        System.out.println(table);
    }
}

