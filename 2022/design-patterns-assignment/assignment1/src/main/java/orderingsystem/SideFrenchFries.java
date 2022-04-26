package orderingsystem;

/**
 *
 * @author kival
 */
public class SideFrenchFries implements Item {

    private String name = "French Fries";
    private int quantity;

    public SideFrenchFries() {
        this.quantity = 1;
    }

    public SideFrenchFries(int qty) {
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
        return 5.0d;
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
