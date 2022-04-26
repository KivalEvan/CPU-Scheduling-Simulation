package orderingsystem;

/**
 *
 * @author kival
 */
public class SoftDrink implements Item {

    private String name = "Soft Drink";
    private int quantity;

    public SoftDrink() {
        this.quantity = 1;
    }

    public SoftDrink(int qty) {
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
        return 1.5d;
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
