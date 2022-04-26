package orderingsystem;

/**
 *
 * @author kival
 */
public class MealChopstick implements Item {

    private String name = "Chopstick";
    private int quantity;

    public MealChopstick() {
        this.quantity = 1;
    }

    public MealChopstick(int qty) {
        this.quantity = qty;
    }

    @Override
    public void setQuantity(int qty) {
        this.quantity = qty;
    }

    @Override
    public int getQuantity() {
        return this.quantity;
    }

    @Override
    public double price() {
        return 17.0d;
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
