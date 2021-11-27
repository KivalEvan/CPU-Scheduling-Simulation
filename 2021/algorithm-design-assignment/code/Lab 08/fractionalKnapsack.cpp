// filename: fractionalKnapsack.cpp

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item
{
    int iNo;
    float weight;
    float benefit;
    float value;
};

void printItems (vector<Item>& items)
{
    cout << "Item\tWeight\tBenefit\tValue\n";
    for (int i=0; i<items.size(); i++)
        cout << items[i].iNo << "\t" << items[i].weight <<"\t"
             << items[i].benefit << "\t" << items[i].value << endl;
}

bool sortByValDesc(const Item &itm1, const Item &itm2)
{
    return itm1.value > itm2.value;
}

int main()
{
    int maxW, n;

    maxW = 20;
    n = 7;

    vector<Item> items(n);

    items[0].weight = 7;
    items[0].benefit = 70;
    items[1].weight = 4;
    items[1].benefit = 16;
    items[2].weight = 3;
    items[2].benefit = 45;
    items[3].weight = 9;
    items[3].benefit = 45;
    items[4].weight = 8;
    items[4].benefit = 40;
    items[5].weight = 4;
    items[5].benefit = 80;
    items[6].weight = 5;
    items[6].benefit = 10;

    for( vector<Item>::size_type i=0; i<n; i++)
    {
        items[i].iNo=i;
        items[i].value=items[i].benefit/items[i].weight;
    }

    printItems (items);

    sort (items.begin(), items.end(), sortByValDesc);

    cout<<"\n\nAfter sort based on value:\n";
    printItems (items);
    cout << "\n\n";

    int currentItem=0;
    int totalW=0;
    int totalBen=0;
    int remW;

    while ((totalW < maxW) && (items[currentItem].weight <= remW))
    {
        // Add code to include current item into the knapsack.
        // Then update total weight, total benefit, remaining weight,
        // and move to next item.
		totalBen += items[currentItem].benefit;
		totalW += items[currenItem].weight;
		currentItem++;
		remW = maxW - totalW;
    }

    if (totalW < maxW)
    {
        // Add code to include a fraction of current item into the knapsack,
        // update total weight and total benefit.
		totalBen += remW * items[currentItem].value;
		totalW += remW;
    }

    cout << "\nMaximum total benefit = " << totalBen;
    cout << "\nTotal weight = " << totalW;

    return 0;
}
