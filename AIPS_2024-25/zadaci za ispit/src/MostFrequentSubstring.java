import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;


public class MostFrequentSubstring {
    static String solve(CBHT<String,Integer> map, HashSet<String> values){
        String ans = "";
        int maxctr = 0;
        for (String val : values){
            int ctr = map.search(val).element.value;
            if (ctr > maxctr ||
                    (ctr == maxctr && (val.length() > ans.length() ||
                            (val.length() == ans.length() && val.compareTo(ans) < 0))))
            {
                ans = val;
                maxctr = ctr;
            }
        }
        return ans;
    }
    public static void main (String[] args) throws IOException {
        CBHT<String,Integer> tabela = new CBHT<String,Integer>(300);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String word = br.readLine().trim();

        HashSet<String> values = new HashSet<>();
        for (int i = 1; i < word.length(); i++) {
            for (int j = 0; j <= word.length() - i; j++) {
                String substr = word.substring(j,j + i);
                SLLNode<MapEntry<String, Integer>> entry = tabela.search(substr);
                tabela.insert(substr, entry == null ? 1 : entry.element.value + 1);
                values.add(substr);
            }
        }
        tabela.insert(word, 1);
        values.add(word);
        System.out.println(solve(tabela, values));
    }
}
