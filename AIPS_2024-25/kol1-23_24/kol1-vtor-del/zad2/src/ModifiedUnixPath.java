//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

import java.util.ArrayList;
import java.util.Scanner;

public class ModifiedUnixPath {
    public ModifiedUnixPath() {
    }

    public static boolean isNumber(String s) {
        for(int i = 0; i < s.length(); ++i) {
            if (!Character.isDigit(s.charAt(i))) {
                return false;
            }
        }

        return true;
    }

    public static String simplifyPath(String path) {
        String[] parts = path.split("/");
        int ctrBack = 0;
        ArrayList<String> as = new ArrayList();

        for(int i = parts.length - 1; i > 0; --i) {
            if (!parts[i].isEmpty() && !parts[i].equals(".")) {
                if (parts[i].charAt(0) == '.' && isNumber(parts[i].substring(1))) {
                    if (ctrBack < 0) {
                        ctrBack = 0;
                    }

                    ctrBack += Integer.parseInt(parts[i].substring(1)) + 1;
                }

                if (ctrBack <= 0) {
                    as.add(parts[i]);
                }

                --ctrBack;
            }
        }

        path = "/" + String.join("/", as.reversed());
        return path;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String path = input.nextLine();
        input.close();
        System.out.println(simplifyPath(path));
    }
}
