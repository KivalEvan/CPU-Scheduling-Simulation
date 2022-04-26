package orderingsystem;

/**
 *
 * @author kival
 */
public class SoftDrinkMug extends SoftDrinkDecorator {

    public SoftDrinkMug(SoftDrink item) {
        super(item);
    }

    @Override
    public String print() {
        return "Mug";
    }
}
