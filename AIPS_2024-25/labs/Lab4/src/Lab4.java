import java.util.Arrays;
import java.util.Scanner;

public class Lab4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int X = input.nextInt();
        int result;

        // vashiot kod ovde / your code goes here
        int[] dp = new int[X + 1];
        Arrays.fill(dp, 100000);
        dp[0] = 0;
        for (int i = 1; i <= X; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = Math.min(dp[i], dp[i - j * j] + 1);
            }
        }
        result = dp[X];
        System.out.println(result);
    }
}

