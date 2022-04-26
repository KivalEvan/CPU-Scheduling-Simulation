package orderingsystem;

/**
 *
 * @author kival
 */
public abstract class ItemDecorator implements Item {

    private Item item;

    public ItemDecorator(Item item) {
        this.item = item;
    }

    @Override
    public void setQuantity(int qty) {
        item.setQuantity(qty);
    }

    @Override
    public int getQuantity() {
        return item.getQuantity();
    }

    @Override
    public double total() {
        return item.price() * this.getQuantity();
    }

    @Override
    public double price() {
        return item.price();
    }

    @Override
    public String print() {
        return item.print();
    }
}
