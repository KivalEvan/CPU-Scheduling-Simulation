package orderingsystem;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;
import javax.swing.ButtonModel;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 *
 * @author kival
 */
// i really really dont like java gui
// why is it randomly broken
public class OrderingController {

    private Ordering model;
    private OrderingView view;

    private final ArrayList<Item> meals = new ArrayList();
    private final ArrayList<Item> sides = new ArrayList();

    OrderingController(String restaurantName) {
        this.model = new Ordering();
        this.view = new OrderingView(restaurantName);

        this.view.orderBtn.addActionListener(new OrderHandler());
        this.view.resetBtn.addActionListener(new ResetHandler());

        this.view.tableSpinner.addChangeListener((ChangeEvent ce) -> {
            model.setTableNum((Integer) ((JSpinner) ce.getSource()).getValue());
            view.printReceipt(model.getTableNum(), model.getItems());
            System.out.println("Set table number to to " + model.getTableNum());
        });

        meals.add(new MealBurger());
        meals.add(new MealHotdog());
        meals.add(new MealChopstick());

        sides.add(new SideFrenchFries());
        sides.add(new SideCorn());
        sides.add(new SideColeslaw());

        for (int i = 0; i < meals.size(); i++) {
            Item meal = meals.get(i);
            ActionListener al = (ActionEvent ae) -> {
                ButtonModel selected = view.mealBtnGroup.getSelection();
                if (selected != null) {
                    for (int i1 = 0; i1 < meals.size(); i1++) {
                        if (model.getItems().contains(meals.get(i1))) {
                            model.removeItem(meals.get(i1));
                        }
                    }
                    model.insertItem(meal);
                    System.out.println("Changed meal to " + meal.print());
                    view.printReceipt(model.getTableNum(), model.getItems());
                }
            };
            ChangeListener cl = (ChangeEvent ce) -> {
                meal.setQuantity((Integer) ((JSpinner) ce.getSource()).getValue());
                view.printReceipt(model.getTableNum(), model.getItems());
                System.out.println("Set " + meal.print() + " quantity to " + meal.getQuantity());
            };
            this.view.addMeal(meal, al, cl);
            System.out.println(meal.print() + " added to meal list.");
        }

        for (int i = 0; i < sides.size(); i++) {
            Item side = sides.get(i);
            ItemListener il = (ItemEvent ie) -> {
                if (ie.getStateChange() == 1) {
                    if (!model.getItems().contains(side)) {
                        model.insertItem(side);
                        System.out.println(side.print() + " added to order.");
                    }
                } else {
                    if (model.getItems().contains(side)) {
                        model.removeItem(side);
                        System.out.println(side.print() + " removed from order.");
                    }
                }
                view.printReceipt(model.getTableNum(), model.getItems());
            };
            ChangeListener cl = (ChangeEvent ie) -> {
                side.setQuantity((Integer) ((JSpinner) ie.getSource()).getValue());
                view.printReceipt(model.getTableNum(), model.getItems());
                System.out.println("Set " + side.print() + " quantity to " + side.getQuantity());
            };
            this.view.addSide(side, il, cl);
            System.out.println(side.print() + " added to side list.");
        }

        // excuse me as i commit sin
        Coffee coffee = new Coffee();
        this.view.addBeverage(coffee, (ItemEvent ie) -> {
            if (ie.getStateChange() == 1) {
                if (!model.getItems().contains(coffee)) {
                    model.insertItem(coffee);
                    System.out.println(coffee.print() + " added to order.");
                }
            } else {
                if (model.getItems().contains(coffee)) {
                    model.removeItem(coffee);
                    System.out.println(coffee.print() + " removed from order.");
                }
            }
            view.printReceipt(model.getTableNum(), model.getItems());
        }, (ChangeEvent ce) -> {
            coffee.setQuantity((Integer) ((JSpinner) ce.getSource()).getValue());
            view.printReceipt(model.getTableNum(), model.getItems());
            System.out.println("Set " + coffee.print() + " quantity to " + coffee.getQuantity());
        });

        // this will definitely put me into programming hell, but i dont care anymore i want to get this done
        SoftDrink sd = new SoftDrink();
        ArrayList<ItemDecorator> sdd = new ArrayList();
        sdd.add(new SoftDrinkCoke(sd));
        sdd.add(new SoftDrinkMug(sd));
        sdd.add(new SoftDrinkPepsi(sd));

        JSpinner spinner = new JSpinner(new SpinnerNumberModel(1, 1, 20, 1)) {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        spinner.addChangeListener((ChangeEvent ce) -> {
            sd.setQuantity((Integer) ((JSpinner) ce.getSource()).getValue());
            view.printReceipt(model.getTableNum(), model.getItems());
            System.out.println("Set " + sd.print() + " quantity to " + sd.getQuantity());
        });

        JComboBox decs = new JComboBox();
        for (int i = 0; i < sdd.size(); i++) {
            decs.addItem(sdd.get(i).print());
        }
        decs.addItemListener((ItemEvent ie) -> {
            for (int i = 0; i < sdd.size(); i++) {
                if (model.getItems().contains(sdd.get(i))) {
                    model.removeItem(sdd.get(i));
                }
                if (decs.getSelectedItem() == sdd.get(i).print()) {
                    if (!model.getItems().contains(sdd.get(i))) {
                        model.insertItem(sdd.get(i));
                        System.out.println("Swapped to " + sdd.get(i).print() + " for " + sd.print());
                    }
                }
            }
            view.printReceipt(model.getTableNum(), model.getItems());
        });

        JCheckBox beverageBtn = new JCheckBox(sd.print());
        beverageBtn.addItemListener((ItemEvent ie) -> {
            for (int i = 0; i < sdd.size(); i++) {
                if (ie.getStateChange() == 1) {
                    if (decs.getSelectedItem() == sdd.get(i).print()) {
                        if (!model.getItems().contains(sdd.get(i))) {
                            model.insertItem(sdd.get(i));
                            System.out.println(sdd.get(i).print() + " added to order.");
                        }
                    }
                } else {
                    if (model.getItems().contains(sdd.get(i))) {
                        model.removeItem(sdd.get(i));
                        System.out.println(sdd.get(i).print() + " removed from order.");
                    }
                }
            }
            view.printReceipt(model.getTableNum(), model.getItems());
        });

        this.view.addBeverage(beverageBtn, spinner, decs);

        // no more hell
    }

    private void reset() {
        this.model.getItems().clear();
        this.view.tableSpinner.setValue(1);
        this.view.mealBtnGroup.clearSelection();
        for (int i = 0; i < this.view.mealRadioBtns.size(); i++) {
            this.view.mealRadioBtns.get(i).setSelected(false);
            this.view.mealSpinners.get(i).setValue(1);
        }
        for (int i = 0; i < this.view.beverageCheckBoxes.size(); i++) {
            this.view.beverageCheckBoxes.get(i).setSelected(false);
            this.view.beverageSpinners.get(i).setValue(1);
        }
        for (int i = 0; i < this.view.sideCheckBoxes.size(); i++) {
            this.view.sideCheckBoxes.get(i).setSelected(false);
            this.view.sideSpinners.get(i).setValue(1);
        }
    }

    private class OrderHandler implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent ae) {
            if (view.mealBtnGroup.getSelection() == null) {
                view.popUp("Please select your main meal.");
                return;
            }
            view.popUp("Order has been received for table no. " + model.getTableNum());
            reset();
        }
    }

    private class ResetHandler implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent ae) {
            reset();
            view.popUp("Order is reset.");
        }
    }
}
