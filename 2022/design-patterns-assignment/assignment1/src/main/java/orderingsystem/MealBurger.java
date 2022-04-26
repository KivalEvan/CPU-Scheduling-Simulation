package orderingsystem;

/**
 *
 * @author kival
 */
public class MealBurger implements Item {

    private String name = "Burger";
    private int quantity;

    public MealBurger() {
        this.quantity = 1;
    }

    public MealBurger(int qty) {
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
        return 13.5d;
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
