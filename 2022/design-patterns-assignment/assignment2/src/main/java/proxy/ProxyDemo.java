package proxy;

/**
 *
 * @author kival
 */
public class ProxyDemo {

    public static void main(String[] args) {
        Database db = new ClientDatabase();

        try {
            db.read("example");
            db.add("example");
            db.read("example");
            db.read("secret information");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
