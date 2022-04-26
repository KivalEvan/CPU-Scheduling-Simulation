package orderingsystem;

/**
 *
 * @author kival
 */
public class SideColeslaw implements Item {

    private String name = "Coleslaw";
    private int quantity;

    public SideColeslaw() {
        this.quantity = 1;
    }

    public SideColeslaw(int qty) {
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
        return 3.2d;
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
