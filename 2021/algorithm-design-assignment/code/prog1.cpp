#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <list>
#include <cmath>
#include<iterator>

using namespace std;

int matrix[10][10];

class Planet {
    public:
    string p_name;
    int x,y,z;
    int weight,profit, p_index;
    float value;
};

Planet P[10];

class Edge{
    public:
    int planet1; //source
    int planet2; //distance
    int distance; //distance between 2 vertices
};

Edge E[18];        ///array of class Edge

int distancez(Planet p1, Planet p2){ /// CALCULATING DISTANCE

    return sqrt(pow(p1.x-p2.x, 2)+pow(p1.y-p2.y, 2)+pow(p1.z-p2.z, 2));
};

void addEdgesMatrix(int edge1, int edge2, int weigth){
    matrix[edge1][edge2]= weigth;
    matrix[edge2][edge1]= weigth;
}

void addEdgesList(list<int> adj_list[], int u, int v) {    //add v into the list u, and u into list v
   adj_list[u].push_back(v);
   adj_list[v].push_back(u);
}

void displayAdjList(list<int> adj_list[], int v) {
   for(int i = 0; i<v; i++) {         ///loop 10 kali
      cout << i << " = ";
      list<int> :: iterator it;
      for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
         //cout << *it << " ";
         cout << P[*it].p_name<< " ";
      }
      cout << endl;
   }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swapPlanets(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

int partitionPlanets (float arr[], int low, int high)
{
    float pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swapPlanets(&arr[i], &arr[j]);
        }
    }
    swapPlanets(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortPlanets(float arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partitionPlanets(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSortPlanets(arr, low, pi - 1);
        quickSortPlanets(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size1){
    int left=0, right=0;

    for (int i=0; i < size1; i++){
        for(int j = 0; j < 18; j++){
            if(arr[i] == E[j].distance){
                left = E[j].planet1;
                right = E[j].planet2;
                cout<<left << " "<<right<<" = ";
            }
        }
        cout<<arr[i]<<endl;
    }
}

void printArrayPlanets(float arr[], int size1){
    string val;
    for (int i=0; i < size1; i++){
        for(int j = 0; j < 10; j++){
            if(arr[i] == arr[i-1] && arr[i] == P[j].value){  ///sebelum ada sama, sebabtu print selepas
                val = P[j+1].p_name;
                cout<<val <<" = ";
                break;

            }else if(arr[i] == P[j].value){
                val = P[j].p_name;
                cout<<val <<" = ";
                break;
            }


        }
        cout<<arr[i]<<endl;
    }
}


int main() {
    const int p_count = 10;    /// 10 meaning that there is 10 planet
    const int e_count = 18;
           ///array of class Planet

    int planet1, planet2;
    list<int> adj_list[p_count];

    for(int i = 0; i<p_count; i++){    ///give all matrix -1 value
        for(int j= 0; j<p_count; j++){
            matrix[i][j] = -1;
        }
    }
     /* Planet Reference
        0 - A
        1 - B
        2 - C
        3 - D
        4 - E
        5 - F
        6 - G
        7 - H
        8 - I
        9 - J */

    ifstream file_planet("A2planets.txt");
    ifstream MyReadFile2("edges.txt");

    string tmp;
    if (file_planet.is_open()) {
        for (int i = 0; i < p_count; i++) {
            file_planet >> P[i].p_name >> P[i].x >> P[i].y >> P[i].z >> P[i].weight >> P[i].profit;   ///store a lot of data from the txt to array of class Planet
        }
    }

    for(int i = 0; i < e_count; i++)
    {
        if(MyReadFile2 >> planet1 >> planet2)
        {
            E[i].planet1 = planet1;
            E[i].planet2 = planet2;
            E[i].distance = distancez(P[E[i].planet1], P[E[i].planet2]);
        }
    }

    cout<<"Planets List:"<<endl;
    for(int i = 0; i< p_count; i++){
        P[i].p_index = i;
    }
    for(int i = 0; i < p_count; i++){
        cout<<P[i].p_index<<":"<<P[i].p_name<<" ("<<P[i].x<<","<<P[i].y<<","<<P[i].z<<") Weight= "<<P[i].weight<<" Profit= "<<P[i].profit<<" Value= "<<(P[i].weight > 0 ? ((float)P[i].profit/P[i].weight) : 0) <<endl;
    }

    cout<<endl;

    cout<<"Edges: "<<endl;
    for(int i = 0; i < e_count; i++){

        cout << E[i].planet1 << " " << E[i].planet2 <<  " "<< E[i].distance << endl;
    }

    cout<<endl;
    addEdgesMatrix(0,3,E[0].distance);
    addEdgesMatrix(0,9,E[1].distance);
    addEdgesMatrix(0,7,E[2].distance);
    addEdgesMatrix(0,5,E[3].distance);
    addEdgesMatrix(1,3,E[4].distance);
    addEdgesMatrix(1,4,E[5].distance);
    addEdgesMatrix(1,6,E[6].distance);
    addEdgesMatrix(2,4,E[7].distance);
    addEdgesMatrix(2,5,E[8].distance);
    addEdgesMatrix(2,8,E[9].distance);
    addEdgesMatrix(3,9,E[10].distance);
    addEdgesMatrix(4,6,E[11].distance);
    addEdgesMatrix(4,8,E[12].distance);
    addEdgesMatrix(5,7,E[13].distance);
    addEdgesMatrix(6,8,E[14].distance);
    addEdgesMatrix(6,9,E[15].distance);
    addEdgesMatrix(7,8,E[16].distance);
    addEdgesMatrix(7,9,E[17].distance);

    cout<<"Matrix: "<<endl;
    for(int i = 0; i < p_count; i++){
        for(int j = 0; j < p_count; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    addEdgesList(adj_list,0,3);
    addEdgesList(adj_list,4,6);
    addEdgesList(adj_list,1,6);
    addEdgesList(adj_list,1,3);
    addEdgesList(adj_list,1,4);
    addEdgesList(adj_list,0,5);
    addEdgesList(adj_list,2,8);
    addEdgesList(adj_list,7,8);
    addEdgesList(adj_list,7,9);
    addEdgesList(adj_list,0,9);
    addEdgesList(adj_list,3,9);
    addEdgesList(adj_list,6,9);
    addEdgesList(adj_list,4,8);
    addEdgesList(adj_list,6,8);
    addEdgesList(adj_list,0,7);
    addEdgesList(adj_list,2,4);
    addEdgesList(adj_list,5,7);
    addEdgesList(adj_list,2,5);

    cout<<endl;

    cout<<"Adjacency List: "<<endl;
    displayAdjList(adj_list,p_count);

    int sortedEdges[18];
    float sortedPlanets[10];

    for(int i = 0; i<e_count; i++){
        sortedEdges[i] = E[i].distance;
    }

    cout<<endl;
    int n = sizeof(sortedEdges)/sizeof(sortedEdges[0]);
    quickSort(sortedEdges, 0, n-1);
    cout<< "Sorted Edges in Ascending Order: " <<endl;
    printArray(sortedEdges, n);

    cout<<endl;

    for(int i = 0; i< p_count; i++){
        P[i].value = (P[i].weight > 0 ? ((float)P[i].profit/P[i].weight) : 0);
        //cout << P[i].value<<endl;
        ///ni dalam float
    }

    for(int i = 0; i<p_count; i++){    ///give sortedPlanets a value
        sortedPlanets[i] = P[i].value;
        //cout<<sortedPlanets[i]<<endl;
    }
    cout<<endl;

    cout<<"Sorted Planets in Descending Order: "<<endl;
    int k = sizeof(sortedPlanets)/sizeof(sortedPlanets[0]);
    quickSortPlanets(sortedPlanets, 0, k-1);

    float descSorted[10];
    int value= 0;
    for(int i = 9; i > -1; i-- ){
        descSorted[i] = sortedPlanets[value];
        value++;
    }

    printArrayPlanets(descSorted, k);

    return 0;
}










