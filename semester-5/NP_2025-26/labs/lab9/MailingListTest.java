package labs.lab9;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// TODO

interface MailingList {
    void subscribe(User user);
    void unsubscribe(User user);
    void publish(String text);
}

interface User{
    void notify(String mailingListName, String text);
}

class SimpleMailingList implements MailingList{
    private final String name;
    private final List<User> subscribers;

    SimpleMailingList(String name){
        this.name = name;
        this.subscribers = new ArrayList<>();
    }
    @Override
    public void subscribe(User user) {
        subscribers.add(user);
    }

    @Override
    public void unsubscribe(User user) {
        subscribers.remove(user);
    }

    @Override
    public void publish(String text) {
        for (User u : subscribers) {
            u.notify(this.name, text);
        }
    }
}

class MailingListUser implements User{
    private final String name;
    private final String email;

    public MailingListUser(String name, String email) {
        this.name = name;
        this.email = email;
    }

    @Override
    public void notify(String mailingListName, String text) {
        System.out.println(String.format(
                "[USER] %s received email from %s: %s",
                name, mailingListName, text
        ));
    }
}
class FilteredMailingListUser implements User{
    private final String name;
    private final String email;
    private final String keyword;
    public FilteredMailingListUser(String name, String email, String keyword) {
        this.name = name;
        this.email = email;
        this.keyword = keyword;
    }

    @Override
    public void notify(String mailingListName, String text) {
        if (!text.toLowerCase().contains(keyword.toLowerCase())) return;
        System.out.println(String.format(
                "[FILTERED USER] %s received filtered email from %s: %s",
                name, mailingListName, text
        ));
    }
}
class AdminUser implements User{
    private final String name;
    private final String email;
    public AdminUser(String name, String email) {
        this.name = name;
        this.email = email;
    }

    @Override
    public void notify(String mailingListName, String text) {
        System.out.println(String.format(
                "[ADMIN LOG] MailingList=%s | Message=%s",
                mailingListName, text
        ));
    }
}

public class MailingListTest {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());

        Map<String, MailingList> mailingLists = new HashMap<>();
        Map<String, User> usersByEmail = new HashMap<>();

        for (int i = 0; i < n; i++) {
            String line = br.readLine();
            String[] parts = line.split(" ");

            String command = parts[0];

            switch (command) {

                case "CREATE_LIST": {
                    String listName = parts[1];
                    mailingLists.put(listName, new SimpleMailingList(listName));
                    break;
                }

                case "ADD_USER": {
                    String listName = parts[1];
                    String type = parts[2];
                    String name = parts[3];
                    String email = parts[4];

                    User user;
                    if (type.equals("NORMAL")) {
                        user = new MailingListUser(name, email);
                    } else if (type.equals("FILTERED")) {
                        String keyword = parts[5];
                        user = new FilteredMailingListUser(name, email, keyword);
                    } else { // ADMIN
                        user = new AdminUser(name, email);
                    }

                    usersByEmail.put(email, user);
                    mailingLists.get(listName).subscribe(user);
                    break;
                }

                case "REMOVE_USER": {
                    String listName = parts[1];
                    String email = parts[2];

                    User user = usersByEmail.get(email);
                    mailingLists.get(listName).unsubscribe(user);
                    break;
                }

                case "PUBLISH": {
                    String listName = parts[1];
                    String text = line.substring(
                            line.indexOf(listName) + listName.length() + 1
                    );
                    mailingLists.get(listName).publish(text);
                    break;
                }
            }
        }
    }
}

