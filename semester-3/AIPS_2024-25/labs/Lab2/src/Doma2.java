import java.util.Scanner;

public class Doma2 {
    static int solve(DLL<Integer> list){
        if (list.getFirst() == null || list.getFirst().succ == null) return 0;
        DLLNode<Integer> tmp = list.getFirst().succ;
        DLLNode<Integer> prev = list.getFirst();
        DLLNode<Integer> after = list.getFirst().succ;

        int sum1,sum2;
        int ctr1, ctr2;
        int res = 0;

        while (tmp != null && tmp.succ != null){
            sum1 = sum2 = 0;
            ctr1 = ctr2 = 0;
            prev = tmp.pred;
            after = tmp.succ;
            while (prev != null) {
                sum1 += prev.element;
                ctr1++;
                prev = prev.pred;
            }
            while (after != null){
                sum2 += after.element;
                ctr2++;
                after = after.succ;
            }
            if ((float)sum1 / ctr1 > (float)sum2 / ctr2) res++;
            tmp = tmp.succ;
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        DLL<Integer> list = new DLL<>();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.nextInt());
        }
        System.out.println(solve(list));
    }
}