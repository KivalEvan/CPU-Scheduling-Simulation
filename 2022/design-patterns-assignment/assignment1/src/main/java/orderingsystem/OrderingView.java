package orderingsystem;

import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import javax.swing.*;
import javax.swing.event.ChangeListener;

/**
 *
 * @author kival
 */
// i really dont like java gui
public class OrderingView extends JFrame {

    private String title;

    private int width = 800;
    private int height = 600;

    private final JPanel headerPanel, subHeaderPanel, mainPanel, menuPanel, tablePanel, mealPanelGrid, mealPanel, beveragePanelGrid, beveragePanel, sidePanelGrid, sidePanel, receiptPanel, controlPanel;
    private JLabel titleLabel, subtitleLabel, tableLabel;
    public JSpinner tableSpinner;
    public JButton orderBtn, resetBtn;

    public ArrayList<JRadioButton> mealRadioBtns = new ArrayList();
    public ArrayList<JSpinner> mealSpinners = new ArrayList();
    public ArrayList<JCheckBox> beverageCheckBoxes = new ArrayList();
    public ArrayList<JSpinner> beverageSpinners = new ArrayList();
    public ArrayList<JCheckBox> sideCheckBoxes = new ArrayList();
    public ArrayList<JSpinner> sideSpinners = new ArrayList();
    public ButtonGroup mealBtnGroup;

    OrderingView(String title) {
        super(title);
        this.title = title;
        this.setSize(width, height);
        this.setResizable(false);

        this.titleLabel = new JLabel(title + " Menu");
        this.titleLabel.setSize(300, 40);
        this.titleLabel.setFont(new Font("Sans Serif", Font.PLAIN, 32));

        this.subtitleLabel = new JLabel("Developed by x");
        this.subtitleLabel.setSize(300, 24);
        this.subtitleLabel.setFont(new Font("Arial", Font.PLAIN, 16));

        this.tableLabel = new JLabel("Table No.");

        this.tableSpinner = new JSpinner(new SpinnerNumberModel(1, 1, 20, 1)) {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        // idk why this sets alignment for all in box
        this.tableSpinner.setAlignmentX(Component.LEFT_ALIGNMENT);

        this.tablePanel = new JPanel();
        this.tablePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        this.tablePanel.add(tableLabel);
        this.tablePanel.add(tableSpinner);

        this.mealBtnGroup = new ButtonGroup();

        this.orderBtn = new JButton("Order");
        this.resetBtn = new JButton("Reset");

        this.headerPanel = new JPanel();
        this.headerPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        this.headerPanel.setBounds(0, 0, width, 56);
        this.headerPanel.setBackground(new Color(64, 192, 32));
        this.headerPanel.add(titleLabel);

        this.subHeaderPanel = new JPanel();
        this.subHeaderPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        this.subHeaderPanel.setBounds(0, 56, width, 32);
        this.subHeaderPanel.setBackground(new Color(32, 160, 224));
        this.subHeaderPanel.add(subtitleLabel);

        this.mealPanelGrid = new JPanel();
        this.mealPanelGrid.setLayout(new GridLayout(0, 3, 0, 0));

        this.mealPanel = new JPanel();
        this.mealPanel.setLayout(new BoxLayout(this.mealPanel, BoxLayout.Y_AXIS));
        // im lazy to look for margin
        this.mealPanel.add(new JLabel(" "));
        this.mealPanel.add(new JLabel("Main Meal"));
        this.mealPanel.add(mealPanelGrid);

        this.beveragePanelGrid = new JPanel();
        this.beveragePanelGrid.setLayout(new GridLayout(0, 3, 0, 0));

        this.beveragePanel = new JPanel();
        this.beveragePanel.setLayout(new BoxLayout(this.beveragePanel, BoxLayout.Y_AXIS));
        this.beveragePanel.add(new JLabel(" "));
        this.beveragePanel.add(new JLabel("Beverage"));
        this.beveragePanel.add(beveragePanelGrid);

        this.sidePanelGrid = new JPanel();
        this.sidePanelGrid.setLayout(new GridLayout(0, 3, 0, 0));

        this.sidePanel = new JPanel();
        this.sidePanel.setLayout(new BoxLayout(this.sidePanel, BoxLayout.Y_AXIS));
        this.sidePanel.add(new JLabel(" "));
        this.sidePanel.add(new JLabel("Side Dish"));
        this.sidePanel.add(sidePanelGrid);

        this.menuPanel = new JPanel();
        this.menuPanel.setLayout(new BoxLayout(this.menuPanel, BoxLayout.Y_AXIS));
        this.menuPanel.setBounds(0, 88, width / 2, height - 152);
        this.menuPanel.add(new JLabel(" "));
        this.menuPanel.add(tablePanel);
        this.menuPanel.add(mealPanel);
        this.menuPanel.add(beveragePanel);
        this.menuPanel.add(sidePanel);

        this.receiptPanel = new JPanel();
        this.receiptPanel.setLayout(new GridLayout(0, 1, 0, 0));
        this.receiptPanel.setBounds(0, 88, width / 2, height - 152);
        this.receiptPanel.setBackground(Color.GRAY);

        this.mainPanel = new JPanel();
        this.mainPanel.setLayout(new GridLayout(0, 2, 0, 0));
        this.mainPanel.setBounds(0, 88, width, height - 152);
        this.mainPanel.setBackground(Color.WHITE);
        this.mainPanel.add(menuPanel);
        this.mainPanel.add(receiptPanel);

        this.controlPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        this.controlPanel.setLayout(new GridLayout(0, 2, 0, 0));
        this.controlPanel.setBounds(0, height - 64, width, 32);
        this.controlPanel.setBackground(Color.GRAY);
        this.controlPanel.add(resetBtn);
        this.controlPanel.add(orderBtn);

        this.setLayout(null);
        this.add(headerPanel);
        this.add(subHeaderPanel);
        this.add(mainPanel);
        this.add(controlPanel);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    public void addMeal(Item item, ActionListener al, ChangeListener cl) {
        JRadioButton mealBtn = new JRadioButton(item.print());
        mealBtn.addActionListener(al);

        JSpinner spinner = new JSpinner(new SpinnerNumberModel(1, 1, 20, 1)) {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        spinner.setAlignmentX(Component.LEFT_ALIGNMENT);
        spinner.addChangeListener(cl);
        this.mealSpinners.add(spinner);

        JLabel blank = new JLabel(" ") {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };

        this.mealRadioBtns.add(mealBtn);
        this.mealBtnGroup.add(mealBtn);
        this.mealPanelGrid.add(mealBtn);
        this.mealPanelGrid.add(spinner);
        this.mealPanelGrid.add(blank);
    }

    public void addBeverage(Item item, ItemListener il, ChangeListener cl) {
        JCheckBox beverageBtn = new JCheckBox(item.print());
        beverageBtn.addItemListener(il);

        JSpinner spinner = new JSpinner(new SpinnerNumberModel(1, 1, 20, 1)) {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        spinner.setAlignmentX(Component.LEFT_ALIGNMENT);
        spinner.addChangeListener(cl);
        this.beverageSpinners.add(spinner);

        JLabel blank = new JLabel(" ") {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };

        this.beverageCheckBoxes.add(beverageBtn);
        this.beveragePanelGrid.add(beverageBtn);
        this.beveragePanelGrid.add(spinner);
        this.beveragePanelGrid.add(blank);
    }

    public void addBeverage(JCheckBox jc, JSpinner js, JComboBox jcb) {
        js.setAlignmentX(Component.LEFT_ALIGNMENT);
        this.beverageCheckBoxes.add(jc);
        this.beverageSpinners.add(js);
        this.beveragePanelGrid.add(jc);
        this.beveragePanelGrid.add(js);
        this.beveragePanelGrid.add(jcb);
    }

    public void addSide(Item item, ItemListener il, ChangeListener cl) {
        JCheckBox sideBtn = new JCheckBox(item.print());
        sideBtn.addItemListener(il);

        JSpinner spinner = new JSpinner(new SpinnerNumberModel(1, 1, 20, 1)) {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        spinner.setAlignmentX(Component.LEFT_ALIGNMENT);
        spinner.addChangeListener(cl);
        this.sideSpinners.add(spinner);

        JLabel blank = new JLabel(" ") {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };

        this.sideCheckBoxes.add(sideBtn);
        this.sidePanelGrid.add(sideBtn);
        this.sidePanelGrid.add(spinner);
        this.sidePanelGrid.add(blank);
    }

    public void popUp(String text) {
        JPanel jp = new JPanel(new FlowLayout());
        JOptionPane.showMessageDialog(jp, text);
    }

    // yea no im not gonna format this anymore
    public void printReceipt(int num, ArrayList<Item> items) {
        System.out.println("\nPrinting Receipt:");
        Date d = new Date();
        String separatorLine = " ";
        double netPrice = 0.0d;
        double taxPrice;
        double totalPrice = 0.0d;

        JPanel main = new JPanel();
        main.setLayout(new BoxLayout(main, BoxLayout.Y_AXIS));

        JLabel titleLabel = new JLabel(this.title);
        titleLabel.setFont(new Font("Sans Serif", Font.PLAIN, 32));
        JPanel titlePanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        titlePanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        titlePanel.setSize(width / 2, 56);
        titlePanel.add(titleLabel);

        JLabel dateTitleLabel = new JLabel("Date:");
        JLabel dateLabel = new JLabel(new SimpleDateFormat("dd/MM/yyyy").format(d));
        JPanel datePanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        datePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        datePanel.add(dateTitleLabel);
        datePanel.add(dateLabel);

        JLabel timeTitleLabel = new JLabel("Time:");
        JLabel timeLabel = new JLabel(new SimpleDateFormat("hh:mm:ss a").format(d));
        JPanel timePanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        timePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        timePanel.add(timeTitleLabel);
        timePanel.add(timeLabel);

        main.add(titlePanel);
        main.add(datePanel);
        main.add(timePanel);
        main.add(new JLabel("Table - " + Integer.toString(num)));

        JPanel itemPanel = new JPanel();
        itemPanel.setLayout(new GridLayout(0, 4, 0, 0));
        itemPanel.add(new JLabel("QTY"));
        itemPanel.add(new JLabel("Item Name"));
        itemPanel.add(new JLabel("Price"));
        itemPanel.add(new JLabel("Amount"));
        for (int i = 0; i < items.size(); i++) {
            netPrice += items.get(i).total();

            JLabel qty = new JLabel(Integer.toString(items.get(i).getQuantity()));
            JLabel name = new JLabel(items.get(i).print());
            JLabel price = new JLabel(String.format("%.2f", items.get(i).price()));
            JLabel total = new JLabel(String.format("%.2f", items.get(i).total()));

            itemPanel.add(qty);
            itemPanel.add(name);
            itemPanel.add(price);
            itemPanel.add(total);
            System.out.println(items.get(i).getQuantity() + "x " + items.get(i).print() + ": " + items.get(i).price() + " (" + items.get(i).total() + ")");
        }
        taxPrice = netPrice * 0.06;
        totalPrice = netPrice + taxPrice;

        main.add(itemPanel);
        main.add(new JLabel(separatorLine));

        JPanel netSubTotalPanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        netSubTotalPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
        netSubTotalPanel.add(new JLabel("Net Subtotal:"));
        netSubTotalPanel.add(new JLabel(String.format("%.2f", netPrice)));
        System.out.println("Net Subtotal: " + netPrice);

        JPanel salesTaxPanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        salesTaxPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
        salesTaxPanel.add(new JLabel("Tax"));
        salesTaxPanel.add(new JLabel(String.format("%.2f", taxPrice)));
        System.out.println("Tax: " + taxPrice);

        JPanel totalPanel = new JPanel() {
            @Override
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        totalPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
        totalPanel.add(new JLabel("Total to Pay:"));
        totalPanel.add(new JLabel(String.format("%.2f", totalPrice)));
        System.out.println("Total: " + totalPrice);
        System.out.println("");

        main.add(netSubTotalPanel);
        main.add(salesTaxPanel);
        main.add(totalPanel);
        main.add(new JLabel(separatorLine));

        this.receiptPanel.removeAll();
        this.receiptPanel.add(main);

        // refreshes frame because it doesnt rerender
        // this is also what's been broken
        this.invalidate();
        this.validate();
        this.repaint();
    }
}
