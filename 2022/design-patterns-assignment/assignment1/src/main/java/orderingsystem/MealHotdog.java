package orderingsystem;

/**
 *
 * @author kival
 */
public class MealHotdog implements Item {

    private String name = "Hotdog";
    private int quantity;

    public MealHotdog() {
        this.quantity = 1;
    }

    public MealHotdog(int qty) {
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
        return 12.0d;
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
