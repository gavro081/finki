package labs.lab9;

import java.util.*;
import java.util.stream.Collectors;

interface XMLComponent{
    // <x attribute=value></x>
    void addAttribute(String attribute, String value);
    String toString(int depth);
}

abstract class XMLComponentImpl implements XMLComponent{
    protected final Map<String, String> attributes;
    protected final String tag;

    XMLComponentImpl(String tag){
        attributes = new LinkedHashMap<>();
        this.tag = tag;
    }

    @Override
    public void addAttribute(String attribute, String value) {
        attributes.put(attribute, value);
    }

    public String getAttributesAsString(){
        String attrStr = attributes.entrySet().stream()
                .map(e -> String.format("%s=\"%s\"", e.getKey(), e.getValue()))
                .collect(Collectors.toList())
                .toString();

        attrStr = attrStr
                .replaceAll(",","")
                .replaceAll("\\[","")
                .replaceAll("]","");

        if (!attrStr.isEmpty()) attrStr = " " + attrStr;
        return attrStr;
    }

    public String getTabStr(int depth){
        // \t ne raboti
        return "    ".repeat(depth);
    }

    // moze uste da se dodava tuka na primer opening i closing tagot e ist kaj site ...
}

class XMLLeaf extends XMLComponentImpl {
    String text;
    public XMLLeaf(String tag, String text) {
        // <tag>text</tag>
        super(tag);
        this.text = text;
    }

    @Override
    public String toString(int depth) {
        return String.format(
                    "%s<%s%s>%s</%s>",
                    getTabStr(depth), tag, getAttributesAsString(), text, tag
                );
    }
}

class XMLComposite extends XMLComponentImpl {
    List<XMLComponent> components;

    public XMLComposite(String tag) {
        // <tag> <child></child> </tag>
        super(tag);
        components = new ArrayList<>();
    }

    public void addComponent(XMLComponent component) {
        components.add(component);
    }

    @Override
    public String toString(int depth) {
        String attrStr = getAttributesAsString();
        String tabs = getTabStr(depth);

        StringBuilder sb = new StringBuilder();

        sb.append(String.format("%s<%s%s>\n",tabs, tag, attrStr));
        components.forEach(c ->
                sb
                        .append(c.toString(depth + 1))
                        .append('\n')
        );
        sb.append(String.format("%s</%s>",tabs, tag));
        return sb.toString();
    }
}


public class XMLTest {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int testCase = sc.nextInt();
        XMLComponent component = new XMLLeaf("student", "Trajce Trajkovski");
        component.addAttribute("type", "redoven");
        component.addAttribute("program", "KNI");

        XMLComposite composite = new XMLComposite("name");
        composite.addComponent(new XMLLeaf("first-name", "trajce"));
        composite.addComponent(new XMLLeaf("last-name", "trajkovski"));
        composite.addAttribute("type", "redoven");
        component.addAttribute("program", "KNI");

        if (testCase==1) {
            //TODO Print the component object
            System.out.println(component.toString(0));
        } else if(testCase==2) {
            //TODO print the composite object
            System.out.println(composite.toString(0));
        } else if (testCase==3) {
            XMLComposite main = new XMLComposite("level1");
            main.addAttribute("level","1");
            XMLComposite lvl2 = new XMLComposite("level2");
            lvl2.addAttribute("level","2");
            XMLComposite lvl3 = new XMLComposite("level3");
            lvl3.addAttribute("level","3");
            lvl3.addComponent(component);
            lvl2.addComponent(lvl3);
            lvl2.addComponent(composite);
            lvl2.addComponent(new XMLLeaf("something", "blabla"));
            main.addComponent(lvl2);
            main.addComponent(new XMLLeaf("course", "napredno programiranje"));

            //TODO print the main object
            System.out.println(main.toString(0));
        }
    }
}
