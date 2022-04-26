package orderingsystem;

/**
 *
 * @author kival
 */
public interface Item {

    public void setQuantity(int qty);

    public int getQuantity();

    public double total();

    public double price();

    public String print();
}
