package orderingsystem;

/**
 *
 * @author kival
 */
public class SoftDrinkCoke extends SoftDrinkDecorator {

    public SoftDrinkCoke(SoftDrink item) {
        super(item);
    }
    
    @Override
    public String print() {
        return "Coca-Cola";
    }
}
