package main;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * Given two lists of strings, return a list of all unique strings that appear in both lists,
 * ignoring case differences.
 *
 * Example:
 * list1 = ["Apple", "banana", "Cherry", "apple"]
 * list2 = ["BANANA", "cherry", "Durian"]
 * Output: ["banana", "Cherry"]
 *
 * The result should contain the matching strings from the first list only,
 * preserving their original casing and order, but without duplicates.
 */

public class StringFunctionClass {
    public static List<String> findCommonIgnoreCase(List<String> list1, List<String> list2){
        Set<String> list2words = list2.stream().map(String::toLowerCase).collect(Collectors.toSet());

        return list1.stream()
                .filter(w -> list2words.remove(w.toLowerCase()))
                .toList();
    }
}
