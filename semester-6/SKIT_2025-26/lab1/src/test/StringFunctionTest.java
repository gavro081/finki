package test;

import main.StringFunctionClass;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.List;

public class StringFunctionTest {
    @Test
    void testCase1(){
        List<String> words1 = List.of("Apple", "banana", "Cherry");
        List<String> words2 = List.of("APPLE", "cherry", "Durian");
        var out = StringFunctionClass.findCommonIgnoreCase(words1, words2);
        Assertions.assertEquals(out, List.of("Apple", "Cherry"));
    }
    @Test
    void testCase3(){
        List<String> words1 = List.of("A");
        List<String> words2 = List.of();
        var out = StringFunctionClass.findCommonIgnoreCase(words1, words2);
        Assertions.assertEquals(out, List.of());
    }
    @Test
    void testCase4(){
        List<String> words1 = List.of("A", "B", "a");
        List<String> words2 = List.of("a","b");
        var out = StringFunctionClass.findCommonIgnoreCase(words1, words2);
        Assertions.assertEquals(out, List.of("A", "B"));
    }
    @Test
    void testCase5(){
        List<String> words1 = List.of("A", "B");
        List<String> words2 = List.of("C", "D");
        var out = StringFunctionClass.findCommonIgnoreCase(words1, words2);
        Assertions.assertEquals(out, List.of());
    }
    @Test
    void testCase6(){
        List<String> words1 = List.of("a", "b");
        List<String> words2 = List.of("B", "C");
        var out = StringFunctionClass.findCommonIgnoreCase(words1, words2);
        Assertions.assertEquals(out, List.of("b"));
    }
}
