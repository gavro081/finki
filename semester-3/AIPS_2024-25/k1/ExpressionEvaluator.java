import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class ExpressionEvaluator {

    public static int evaluateExpression(String expression){
        int res = 0;
        char[] exp = expression.toCharArray();
        int num=0;
        for (int i = 0; i < exp.length; i++) {
            if (Character.isDigit(exp[i])) {
                if (i != 0 && Character.isDigit(exp[i-1]))
                    num = 10*num + exp[i] - '0';
                else num = exp[i] - '0';
            }
            else if (exp[i] == '+') res += num;
            else if (exp[i] == '*') {
                i++;
                int tmp = 0;
                while (i < exp.length &&  Character.isDigit(exp[i])){
                    tmp = tmp*10 + (exp[i] - '0');
                    i++;
                }
                i--;
                num = num * tmp;
            }
        }
        // for (int i = exp.length - 1; i >= 0; i--) {
        //     if (exp[i] == '+') return res;
        //     if (exp[i] == '*') return res+num;
        // }
        return res+num;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader input=new BufferedReader(new InputStreamReader(System.in));
        System.out.println(evaluateExpression(input.readLine()));
    }

}