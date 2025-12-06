import java.util.Arrays;
import java.util.Scanner;

public class Main {
//    Колку најмалку пати треба да одземеме квадрат на цел број за некој број Х да стане 0?
//
//    Влез: Цел број Х од 1 до 10^5.
//
//    Излез: Бараниот резултат.
    public static void main(String []args){
        Scanner in = new Scanner(System.in);

        int x = in.nextInt();

        int []res = new int[x+1];
        Arrays.fill(res,1000);

//        int sqr = (int)Math.sqrt(x);
        res[0] = 0;res[1] = 1;
        if (x == 0 || x == 1) {
            System.out.println(res[x]); return;
        }
        // res[Ai] = 1 + res[Ai - sqr]
        for (int i = 2; i <= x; i++) {
            int sqr = (int)Math.sqrt(i);
            for (int j = 1; j <= sqr; j++) {
                res[i] = Math.min(1 + res[i - j*j],res[i]);
            }
        }
        System.out.println(res[x]);
    }
}
