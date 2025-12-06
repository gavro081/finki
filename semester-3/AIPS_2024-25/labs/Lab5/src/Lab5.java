
import java.util.Scanner;

public class Lab5 {
    static class Student{
        String name;
        int dava;
        int zema;
        int index;

        Student(String n, int a, int b, int c){
            name = n;
            dava = a;
            index = b;
            zema = c;
        }
        Student(){}
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        LinkedQueue<Student> dava = new LinkedQueue<Student>();
        LinkedQueue<Student> indeks = new LinkedQueue<Student>();
        LinkedQueue<Student> zema = new LinkedQueue<Student>();
        for (int i = 0; i < n; i++) {
            String name = in.nextLine();
            int a = Integer.parseInt(in.nextLine());
            int b = Integer.parseInt(in.nextLine());
            int c = Integer.parseInt(in.nextLine());
            Student s = new Student(name, a,b,c);
            if (a == 1){
                dava.enqueue(s);
            }
            else if ( b == 1){
                indeks.enqueue(s);
            }
            else
                zema.enqueue(s);
        }


        while (!dava.isEmpty() || !indeks.isEmpty() || !zema.isEmpty()){
            for (int i = 0; i < 2; i++) {
                if (dava.isEmpty()) break;
                Student st = dava.peek();
                if (st.index == 1){
                    indeks.enqueue(dava.dequeue());
                }
                else if (st.zema == 1){
                    zema.enqueue(dava.dequeue());
                }
                else {
                    System.out.println(st.name);
                    dava.dequeue();
                }
            }for (int i = 0; i < 3; i++) {
                if (indeks.isEmpty()) break;
                Student st = indeks.peek();
                if (st.zema == 1){
                    zema.enqueue(indeks.dequeue());
                }
                else {
                    System.out.println(st.name);
                    indeks.dequeue();
                }
            }
            if (!zema.isEmpty()){
                System.out.println(zema.peek().name);
                zema.dequeue();
            }


        }
    }
}