package labs.lab9;

import java.util.*;
import java.util.stream.Collectors;

interface Document {
    String getText();
    String getId();
    void display();
}

class BasicDocument implements Document {
    private final String id;
    private String text;
    
    public BasicDocument(String id, String text) {
        this.id = id;
        this.text = text;
    }

    public String getText(){
        return text;
    }
    public String getId(){
        return id;
    }

    @Override
    public void display() {
        System.out.println("=== Document " + id + " ===");
        System.out.println(getText());
    }
}

abstract class DocumentDecorator implements Document {
    protected Document decoratedDocument;
    public DocumentDecorator(Document decoratedDocument) {
        this.decoratedDocument = decoratedDocument;
    }

    @Override
    public String getText() {
        return decoratedDocument.getText();
    }

    @Override
    public String getId() {
        return decoratedDocument.getId();
    }

    @Override
    public void display() {
        System.out.println("=== Document " + decoratedDocument.getId() + " ===");
        System.out.println(getText());
    }
}

class LineNumberDecorator extends DocumentDecorator {
    public LineNumberDecorator(Document decoratedDocument) {
        super(decoratedDocument);
    }
    
    @Override
    public String getText(){
        String text = this.decoratedDocument.getText();
        String []lines = text.split("\n");
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < lines.length; i++) {
            sb.append(String.format("%d: %s", i+1, lines[i]));
            if (i != lines.length - 1) sb.append("\n");
        }
        return sb.toString();
    }
}

class WordCountDecorator extends DocumentDecorator {
    public WordCountDecorator(Document decoratedDocument){
        super(decoratedDocument);
    }
    
    @Override
    public String getText(){
        String originalText = this.decoratedDocument.getText();
        int length = originalText.split("\\s+").length;
        return originalText + String.format("\nWords: %d", length);
    }
}
class RedactionDecorator extends DocumentDecorator {
    private final List<String> forbiddenWords;

    public RedactionDecorator(Document decoratedDocument, List<String> forbiddenWords){
        super(decoratedDocument);
        this.forbiddenWords = forbiddenWords.stream().map(String::toLowerCase).collect(Collectors.toList());
    }
    
    @Override
    public String getText(){
        String text = this.decoratedDocument.getText();
        StringBuilder newText = new StringBuilder();
        String []lines = text.split("\n");
        for (int l = 0; l < lines.length; l++) {
            String []words = lines[l].split("\\s+");
            for (int i = 0; i < words.length; i++) {
                if (forbiddenWords.contains(words[i].toLowerCase())){
                    newText.append("*");
                } else newText.append(words[i]);
                if (i != words.length - 1) newText.append(" ");
            }
            if (l != lines.length - 1) newText.append("\n");
        }
        return newText.toString();
    }
}

class DocumentViewer {
    private final Map<String, Document> documents;
    DocumentViewer(){
        documents = new TreeMap<>();
    }

    public void addDocument(String id, String text){
        documents.put(id, new BasicDocument(id, text));
    }

    public void enableLineNumbers(String id){
        documents.put(id, new LineNumberDecorator(documents.get(id)));
    }

    public void enableWordCount(String id){
        documents.put(id, new WordCountDecorator(documents.get(id)));
    }

    public void enableRedaction(String id, List<String> forbiddenWords){
        documents.put(id, new RedactionDecorator(documents.get(id), forbiddenWords));
    }

    public void display(String id){
        documents.get(id).display();
    }

}

public class DocumentViewerTester {
    public static void main(String[] args) {
        DocumentViewer viewer = new DocumentViewer();
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.nextLine();
        for (int i = 0; i < n; i++) {
            String id = sc.nextLine();
            int lineNum = Integer.parseInt(sc.nextLine());
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < lineNum; j++) {
                sb.append(sc.nextLine());
                if (j != lineNum - 1) sb.append("\n");
            }
            viewer.addDocument(id, sb.toString());
        }

        while (true){
            String []parts = sc.nextLine().split("\\s+");
            String command = parts[0];
            switch (command){
                case "enableLineNumbers": viewer.enableLineNumbers(parts[1]); break;
                case "display": viewer.display(parts[1]); break;
                case "enableWordCount": viewer.enableWordCount(parts[1]); break;
                case "enableRedaction": viewer.enableRedaction(parts[1], Arrays.stream(parts).skip(2).collect(Collectors.toList())); break;
                case "exit": return;

            }
        }

    }
}
