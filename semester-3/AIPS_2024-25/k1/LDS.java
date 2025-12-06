import java.util.Scanner;
import java.util.Arrays;


public class LDS {


    private static int najdolgaOpagackaSekvenca(int[] a) {
        int []dp = new int[a.length];
        Arrays.fill(dp,1);
        int max = 1;
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < i; j++) {
                if (a[j] > a[i])
                    dp[i] = Math.max(dp[j] + 1, dp[i]);
                max = Math.max(dp[i], max);
            }
        }
        return max;
    }

    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);

        int n = stdin.nextInt();
        int a[] = new int[n];
        for (int i = 0; i < a.length; i++) {
            a[i] = stdin.nextInt();
        }
        System.out.println(najdolgaOpagackaSekvenca(a));
    }


}
