package orderingsystem;

/**
 *
 * @author kival
 */
public class SideCorn implements Item {

    private String name = "Corn";
    private int quantity;

    public SideCorn() {
        this.quantity = 1;
    }

    public SideCorn(int qty) {
        this.quantity = qty;
    }

    @Override
    public int getQuantity() {
        return this.quantity;
    }

    @Override
    public void setQuantity(int qty) {
        this.quantity = qty;
    }

    @Override
    public double price() {
        return 3.5d;
    }

    @Override
    public double total() {
        return this.price() * this.quantity;
    }

    @Override
    public String print() {
        return this.name;
    }
}
