package orderingsystem;

/**
 *
 * @author kival
 */
public class SoftDrinkPepsi extends SoftDrinkDecorator {

    public SoftDrinkPepsi(SoftDrink item) {
        super(item);
    }

    @Override
    public String print() {
        return "Pepsi";
    }
}
