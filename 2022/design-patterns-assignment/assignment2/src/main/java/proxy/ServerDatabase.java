package proxy;

import java.util.ArrayList;

/**
 *
 * @author kival
 */
public class ServerDatabase implements Database {

    private static ArrayList<String> data = new ArrayList<String>();

    static {
        data.add("accounts");
        data.add("subjects");
        data.add("secret information");
    }

    @Override
    public void add(String query) {
        System.out.println("Added to database: " + query);
        data.add(query);
    }

    @Override
    public void read(String query) {
        boolean result = data.contains(query);
        if (result) {
            System.out.println("Found result: " + query);
            return;
        }
        System.out.println("No result.");
    }
}
