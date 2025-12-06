import java.util.*;

public class Doma3 {
    static StringBuilder solve(int[] nums, int n){
        Arrays.sort(nums);
        StringBuilder res = new StringBuilder();
        for (int i = n - 1; i >= 0; i--) {
            res.append(nums[i]);
        }
        return res;
    }
    public static void main(String []args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();

        int[]nums = new int [n];

        for (int i = 0; i < n; i++) {
            nums[i] = in.nextInt();
        }

        System.out.println(solve(nums,n));
    }
}

