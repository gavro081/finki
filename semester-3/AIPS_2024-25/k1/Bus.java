import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Bus {

    public static void main(String[] args) throws Exception {
        int i,j,k;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());
        int M = Integer.parseInt(br.readLine());

        br.close();

        // Vasiot kod tuka
        int min;
        int max;
        if (M == 0){
            System.out.println(N*100 + "\n" + N*100);
            return;
        }
        if (N > M) min = N*100;
        else {
            min = N * 100 + (M - N) * 100;
        }

        max = N*100 + (M-1) * 100;

        System.out.println(min);
        System.out.println(max);


    }

}
