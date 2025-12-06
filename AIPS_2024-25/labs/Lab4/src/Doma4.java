import java.util.Scanner;

public class Doma4 {
    static int bsearch(int[]arr, int l, int r, int m){
        int middle = (l + r) / 2;

        if (arr[middle] == m) return middle;
        if (l >= r) return -1;

        if (arr[middle] > m ) return bsearch(arr,l,middle,m);
        else  return bsearch(arr,middle + 1, r,m);
    }

    public static void main(String []args){
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int m = in.nextInt();
        int []arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = in.nextInt();
        }
        int sol = bsearch(arr,0,n - 1,m);
        System.out.println(sol == -1 ? "Ne postoi" : sol);
    }
}
