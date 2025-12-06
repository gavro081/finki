import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


class Zbor implements Comparable<Zbor>{
    String zbor;

    public Zbor(String zbor) {
        this.zbor = zbor;
    }
    @Override
    public boolean equals(Object obj) {
        Zbor pom = (Zbor) obj;
        return this.zbor.equals(pom.zbor);
    }
    @Override
    public int hashCode() {
        return zbor.hashCode();
    }
    @Override
    public String toString() {
        return zbor;
    }
    @Override
    public int compareTo(Zbor arg0) {
        return zbor.compareTo(arg0.zbor);
    }
}

public class Speluvanje {
    public static boolean solve(String text, OBHT<Zbor, String> map){
        String []words = text.split(" ");
        boolean flag = false;
        for (String word : words) {
            char sign = word.charAt(word.length() - 1);
            if (sign == '!' || sign == '?' || sign == '.' || sign == ','){
                word = word.substring(0, word.length() - 1);
            }
            if (word.isEmpty()) continue;
            word = word.toLowerCase();
            if (map.search(new Zbor(word)) == -1){
                System.out.println(word);
                flag = true;
            }
        }
        return flag;
    }
    public static void main(String[] args) throws IOException {
        OBHT<Zbor, String> tabela;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());
        //---Vie odluchete za goleminata na hesh tabelata----
        tabela = new OBHT<Zbor,String>(N * 2);

        for (int i = 0; i < N; i++) {
            String str = br.readLine();
            tabela.insert(new Zbor(str), str);
        }
        String text = br.readLine();
        if (!solve(text, tabela)) System.out.println("Bravo");
    }
}
