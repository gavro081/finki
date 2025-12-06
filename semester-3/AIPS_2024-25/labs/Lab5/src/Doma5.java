import java.util.Scanner;


public class Doma5 {
    public static boolean solve(LinkedStack<String> stack,String[] strings){
        for (String str : strings){
            if (str == null) break;
            if (!str.startsWith("end"))
                stack.push(str);
            else {
                if (stack.isEmpty() || !stack.peek().equals(str.substring(3))) return false;
                stack.pop();
            }
        }
        return stack.isEmpty();
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        LinkedStack<String> stack = new LinkedStack<>();
        String s = in.next();
        String[] strings = new String[100];
        int i = 0;
        while (!s.equals("x")){
            strings[i++] = s;
            s = in.next();
        }
        System.out.println(solve(stack, strings) ? "Valid" : "Invalid");
    }
}