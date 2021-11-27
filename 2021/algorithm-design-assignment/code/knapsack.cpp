#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


int knapsack(int sack, string name[], double weight[], double value[], double profit[]){
    cout << setw(10) << left << "Planet" << setw(10) << left << "Value" << setw(10) << left << "Weight" << setw(10) << left << "Profit" << endl;

    int currentWeight = 0;
    int currentProfit = 0;
    while (currentWeight < sack)
    {
        int biggestIndex = 0;

        for (int i = 1; i < 10; i++)
        {
            if (value[i] > value[biggestIndex])
            {
                biggestIndex = i;
            }

            if (value[i] == value[biggestIndex])
            {
                if (weight[i] > weight[biggestIndex] && (currentWeight + weight[i]) <= sack)
                {
                    biggestIndex = i;
                }
                
            }
            
                       
        }

        if ((currentWeight + weight[biggestIndex]) <= sack)
        {
            cout << setw(10) << left << name[biggestIndex] << setw(10) << left << value[biggestIndex] << setw(10) << left << weight[biggestIndex] << setw(10) << left << profit[biggestIndex] << endl;
            currentWeight = currentWeight + weight[biggestIndex];
            currentProfit = currentProfit + profit[biggestIndex];
            value[biggestIndex] = 0;
            weight[biggestIndex] = 0;
        }
        else {
            break;
        }
    }

    cout << endl << "The totaled weight is " << currentWeight << " and the totaled profit is " << currentProfit;
    
    return 0;
}

int main()
{
    ifstream file;
    file.open("A2planets.txt");
    
    //max weight possible
    int sack = 80;

    string name[10];

    //coordinates, but won't be used
    int x[10];
    int y[10];
    int z[10];

    double weight[10];
    double profit[10];
    double value[10];

    int i = 0;
    //reads file data into arrays
    while (!file.eof())
    {
        file >> name[i] >> x[i] >> y[i] >> z[i] >> weight[i] >> profit[i];
        i++;
    }
    file.close();

    value[0]=0;


    for (int i = 1; i < 10; i++)
    {
        value[i] = profit[i] / weight[i];
    }
    
    cout << "Collected data:" << endl << endl;
    cout << setw(10) << left << "Planet" << setw(10) << left << "Value" << setw(10) << left << "Weight" << setw(10) << left << "Profit" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << setw(10) << left << name[i] << setw(10) << left << value[i] << setw(10) << left << weight[i] << setw(10) << left << profit[i] << endl;
    }
    

    cout << endl << endl;

    cout << "0/1 knapsack algorithm result:" << endl;
    knapsack(sack, name, weight, value, profit);

    return 0;
}