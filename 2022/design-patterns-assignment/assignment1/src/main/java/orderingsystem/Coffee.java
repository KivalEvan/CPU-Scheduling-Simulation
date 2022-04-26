package orderingsystem;

/**
 *
 * @author kival
 */
public class Coffee implements Item {

    private String name = "Coffee";
    private int quantity;

    public Coffee() {
        this.quantity = 1;
    }

    public Coffee(int qty) {
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
        return 5.2d;
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
