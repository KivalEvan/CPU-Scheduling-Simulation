package orderingsystem;

import java.util.ArrayList;

/**
 *
 * @author kival
 */
public class Ordering {

    private int tableNum;
    private ArrayList<Item> items;

    Ordering() {
        this.tableNum = 1;
        this.items = new ArrayList();
    }

    Ordering(int num) {
        this.tableNum = num;
        this.items = new ArrayList();
    }

    public int getTableNum() {
        return this.tableNum;
    }

    public void setTableNum(int num) {
        this.tableNum = num;
    }

    public ArrayList getItems() {
        return this.items;
    }

    public void insertItem(Item item) {
        this.items.add(item);
    }

    public void removeItem(Item item) {
        this.items.remove(item);
    }

    public void resetItems() {
        this.items = new ArrayList();
    }
}
