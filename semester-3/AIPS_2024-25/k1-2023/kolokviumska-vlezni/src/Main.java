import java.util.Scanner;

public class Main {
    public static void makeZigZag(SLL<Integer> list){
        SLLNode<Integer> tmp = list.getFirst();
        if (tmp == null || tmp.succ == null) {
            return;
        }
        while (tmp != null){
            if (tmp.element == 0) list.delete(tmp);
            tmp = tmp.succ;
        }
        tmp = list.getFirst();
        while (tmp != null && tmp.succ != null) {
            while (tmp.succ != null && tmp.element > 0 && tmp.succ.element > 0){
                list.delete(tmp.succ);
            }
            if (tmp.succ != null && tmp.element < 0 && tmp.succ.element < 0) list.insertAfter(tmp.element * -1, tmp);
            tmp = tmp.succ;
        }
    }

    public static void putWordsTogether(SLL<String> list) {
        SLLNode<String> tmp = list.getFirst();
        while (tmp != null && tmp.succ != null) {
            if (!tmp.succ.element.equals(",")) {
                tmp.element += tmp.succ.element;
                list.delete(tmp.succ);
            }
            else {
                list.delete(tmp.succ);
                tmp = tmp.succ;
            }
        }
    }

    public static void main(String args[]){
//            Scanner input = new Scanner(System.in);
//            int n = input.nextInt();
//            SLL<Integer> list = new SLL<>();
//            for(int i=0;i<n;i++) {
//                list.insertLast(input.nextInt());
//            }
//            System.out.println(list);
//            makeZigZag(list);
//            System.out.println(list);

        Scanner input = new Scanner(System.in);

        String line = input.nextLine();

        String parts[] = line.split(" ");

        SLL<String> list = new SLL<>();

        for(String part: parts) {
            list.insertLast(part);
        }

        System.out.println(list);

        putWordsTogether(list);

        System.out.println(list);
    }
}