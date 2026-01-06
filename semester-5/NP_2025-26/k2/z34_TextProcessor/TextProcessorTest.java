package k2.z34_TextProcessor;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class CosineSimilarityCalculator {
    public static double cosineSimilarity(Collection<Integer> c1, Collection<Integer> c2) {
        int[] array1;
        int[] array2;
        array1 = c1.stream().mapToInt(i -> i).toArray();
        array2 = c2.stream().mapToInt(i -> i).toArray();
        double up = 0.0;
        double down1 = 0, down2 = 0;

        for (int i = 0; i < c1.size(); i++) {
            up += (array1[i] * array2[i]);
        }

        for (int i = 0; i < c1.size(); i++) {
            down1 += (array1[i] * array1[i]);
        }

        for (int i = 0; i < c1.size(); i++) {
            down2 += (array2[i] * array2[i]);
        }

        return up / (Math.sqrt(down1) * Math.sqrt(down2));
    }
}

class TextProcessor {
    private final Set<String> dictionary;
    private final List<String> texts;
    private final Map<String, Integer> wordCounts;
    private final List<List<Integer>> vectors;

    public TextProcessor() {
        texts = new ArrayList<>();
        dictionary = new TreeSet<>();
        wordCounts = new TreeMap<>();
        vectors = new ArrayList<>();
    }

    public void readText(InputStream is) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            texts.add(line);
            line = cleanLine(line);
            String[] words = line.split("\\s+");
            dictionary.addAll(Arrays.asList(words));
        }
    }

    private String cleanLine(String line) {
        return line
                .replaceAll("[^a-zA-Z ]", "")
                .toLowerCase();
    }

    public void printTextsVectors(PrintStream out) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
        for (String text : texts) {
            text = cleanLine(text);
            String[] words = text.split("\\s+");
            Map<String, Integer> wordCount = new HashMap<>();
            for (String word : words) {
                wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
                wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
            }
            ArrayList<Integer> vector = new ArrayList<>();
            for (String word : dictionary) {
                vector.add(wordCount.getOrDefault(word, 0));
            }
            vectors.add(vector);
            writer.write(vector.toString());
            writer.newLine();
        }
        writer.flush();
    }

    public void printCorpus(PrintStream os, int n, boolean ascending)
            throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));

        Comparator<Map.Entry<String, Integer>> comparator =
                ascending ?
                        Map.Entry.comparingByValue() :
                        Map.Entry.<String, Integer>comparingByValue().reversed();

        List<String> collect = wordCounts.entrySet().stream()
                .sorted(comparator)
                .map(e -> e.getKey() + " : " + e.getValue())
                .limit(n)
                .collect(Collectors.toList());

        for (String s : collect) {
            writer.write(s);
            writer.newLine();
        }

        writer.flush();
    }

    public void mostSimilarTexts(PrintStream out) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
        double maxScore = 0;
        String text1 = null;
        String text2 = null;
        for (int i = 0; i < vectors.size(); i++){
            for (int j = i+1; j < vectors.size(); j++){
                double score = CosineSimilarityCalculator.cosineSimilarity(vectors.get(i), vectors.get(j));
                if (score > maxScore){
                    maxScore = score;
                    text1 = texts.get(i);
                    text2 = texts.get(j);
                }
            }
        }
        writer.write(text1 + "\n");
        writer.write(text2 + "\n");
        writer.write(String.format("%.10f", maxScore));
        writer.flush();
    }
}

public class TextProcessorTest {

    public static void main(String[] args) throws IOException {
        TextProcessor textProcessor = new TextProcessor();

        textProcessor.readText(System.in);

        System.out.println("===PRINT VECTORS===");
        textProcessor.printTextsVectors(System.out);

        System.out.println("PRINT FIRST 20 WORDS SORTED ASCENDING BY FREQUENCY ");
        textProcessor.printCorpus(System.out, 20, true);

        System.out.println("PRINT FIRST 20 WORDS SORTED DESCENDING BY FREQUENCY");
        textProcessor.printCorpus(System.out, 20, false);

        System.out.println("===MOST SIMILAR TEXTS===");
        textProcessor.mostSimilarTexts(System.out);
    }
}