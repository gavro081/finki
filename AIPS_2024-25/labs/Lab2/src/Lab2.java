
import java.util.Scanner;

public class Lab2 {

    static void solve(DLL<Integer> dll, int k){
        DLLNode<Integer> tmp = dll.getFirst();
        while (k != 0){
            dll.insertLast(tmp.element);
            dll.delete(tmp);
            tmp = tmp.succ;
            k--;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        DLL<Integer> dll = new DLL<>();
        for (int i = 0; i < n; i++) {
            dll.insertLast(in.nextInt());
        }

        int k = in.nextInt();

        solve(dll,k);

        System.out.println(dll.toString());
    }
}