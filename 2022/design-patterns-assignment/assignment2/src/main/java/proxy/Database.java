package proxy;

/**
 *
 * @author kival
 */
public interface Database {

    public void add(String query) throws Exception;

    public void read(String query) throws Exception;
}
