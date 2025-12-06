import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class KumanovskiDijalekt {
    static String solve(CBHT<String, String> map, String text){
        String []words = text.split(" ");
        for (int i = 0; i < words.length; i++) {
            char sign = words[i].charAt(words[i].length() - 1);
            if (sign == '!' || sign == '?' || sign == '.' || sign == ',') {
                words[i] = words[i].substring(0, words[i].length() - 1);
            } else sign = 'X';
            boolean firstCapital = Character.isUpperCase(words[i].charAt(0));
            SLLNode<MapEntry<String,String>> currword = map.search(words[i].toLowerCase());
            if (currword != null) {
                words[i] = currword.element.value;
                if (firstCapital)
                    words[i] = Character.toUpperCase(words[i].charAt(0)) + words[i].substring(1);
            }

            if (sign != 'X') words[i] += sign;
        }
        return String.join(" ", words);
    }
    public static void main (String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(
                System.in));
        int N = Integer.parseInt(br.readLine());

        String rechnik[]=new String[N];
        for(int i=0;i<N;i++){
            rechnik[i]=br.readLine();
        }

        String tekst=br.readLine();

        //Vasiot kod tuka
        CBHT<String, String> map = new CBHT<>(2*N);
        for (int i = 0; i < N; i++) {
            String []parts = rechnik[i].split(" ");
            map.insert(parts[0], parts[1]);
        }
        if (N == 0) System.out.println(tekst);
        else System.out.println(solve(map, tekst));
    }
}
