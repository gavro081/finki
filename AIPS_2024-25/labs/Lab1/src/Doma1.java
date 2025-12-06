import java.util.ArrayList;
import java.util.Scanner;

public class Doma1 {
    public static void print(ArrayList<Integer> arr, int n){
        System.out.print('{');
        for (int i = 0; i < n; i++) {
            System.out.print(arr.get(i));
            if (i != n - 1) System.out.print(",");
        }
        System.out.print('}');
        System.out.println();
    }

    public static void main(String []args){
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int sum = 0;
        ArrayList<Integer> arr = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            arr.add(in.nextInt());
            sum += arr.get(i);
        }

        print(arr,n);

        float avg = (float)sum / n;

        for (int i = 0; i < n; i++) {
            if (arr.get(i) < avg){
                arr.remove(i);
                n--;
                i--;
            }
        }

        print(arr,n);

    }
}