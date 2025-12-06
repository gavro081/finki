import java.util.Scanner;
public class Faks1 {
    public static void solve(SLL<String>list, int l){
        SLLNode<String> tmp = list.getFirst();
        SLLNode<String> prev = list.getFirst();
        for (int i = 0; i < list.size(); i++) {
            if (tmp.element.length() == l){
                prev = tmp;
                list.insertLast(tmp.element);
                list.delete(tmp);
                tmp = prev.succ;
            }
            else tmp = tmp.succ;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        SLL<String>list = new SLL<>();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.next());
        }
        int l = in.nextInt();
        System.out.println(list.toString());
        solve(list,l);
        System.out.println(list.toString());
    }
}
