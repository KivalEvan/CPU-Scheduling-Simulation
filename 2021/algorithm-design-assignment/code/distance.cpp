#include <iostream>
#include <iomanip>
#include <chrono>
#include <math.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;


int edges[10][10];
string arr[60];
int Xcords[10];
int Ycords[10];
int Zcords[10];
float weight[10];
float profit[10];
float value[10];
int i=0;
int temp =0;
int countX = 0;
int countY = 0;
int countZ = 0;
int countW = 0;
int countP = 0;
vector<int> graph[10];
string planets[10];
map <string, float> edge;
map <string, float> planetvalues;
ifstream inputfile("A2planets.txt");

void setValues() {
    string line;
    if (inputfile.is_open()) {
    while (getline(inputfile, line)) {
        istringstream iss(line);
        
        while (getline(iss, arr[i], ' ')) {
            //getting X coords and save to its array
            if (i == 1 || i == 7 || i == 13 || i == 19 || i == 25 || i == 31 || i == 37 || i == 43 || i == 49 || i == 55) {
                Xcords[countX] = stoi(arr[i]);
                
                countX++;
            }
            //y coords
            if (i == 2 || i == 8 || i == 14 || i == 20 || i == 26 || i == 32 || i == 38 || i == 44 || i == 50 || i == 56) {
                Ycords[countY] = stoi(arr[i]);
                
                countY++;
            }
            //z coords
            if (i == 3 || i == 9 || i == 15 || i == 21 || i == 27 || i == 33 || i == 39 || i == 45 || i == 51 || i == 57) {
                Zcords[countZ] = stoi(arr[i]);

                countZ++;
            }
            //weight
            if (i == 4 || i == 10 || i == 16 || i == 22 || i == 28 || i == 34 || i == 40 || i == 46 || i == 52 || i == 58) {
                weight[countW] = stoi(arr[i]);
                countW++;
            }
            //profit
            if (i == 5 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35 || i == 41 || i == 47 || i == 53 || i == 59) {
                profit[countP] = stoi(arr[i]);
                countP++;
            }
            i++;
        }
    }
    }
    inputfile.close();
}

void setList(vector<int> adj[], int b, int e) {
    //setting the adjacency list
    if ( b < e) {
        //the smaller index gets priorities to set first, since it'll appear before the latter planets
    adj[b].push_back(e);
    }
    else 
    adj[e].push_back(b);
}

void setPlanet() {
    //planets array, look like this {"A","B","C"...}
    char letter[] = "A";
    planets[0] = letter[0];
    
    for (int i = 1; i < 10; i++) {
        planets[i] = static_cast<char>(letter[0] + i);
    }
}

void setPlanetValue() {
    //setting planet value using mapping look like this <planetname, value>
    for (int i = 0; i < 10; i++) {
        value[i] = profit[i] / weight[i];
        if (isnan(value[i])) {
            value[i] = 0;
        }
        planetvalues[planets[i]] = value[i];
    }
}

/*
    A=0
    B=1
    C=2
    D=3
    E=4
    F=5
    G=6
    H=7
    I=8
    J=9
*/
void calculateDistance(int a, int b) {
    int value = (Xcords[b] - Xcords[a])*(Xcords[b] - Xcords[a]) + (Ycords[b] - Ycords[a])*(Ycords[b] - Ycords[a]) + (Zcords[b] - Zcords[a])*(Zcords[b] - Zcords[a]);
    int result = sqrt(value);
    edges[a][b] = result;
    edges[b][a] = result;
    edge[planets[a]+planets[b]] = result;
    setList(graph, a, b);
}

void printGraph(vector<int> adj[], int V) {
  for (int d = 0; d < V; ++d) {
    cout << "\n Vertex "
       << planets[d] << ":";
    for (auto x : adj[d])
      cout << "-> " << planets[x];
    printf("\n");
  }
}



void displayMatrix() {
   for(int a = 0; a < 10; a++) {
      for(int b = 0; b < 10; b++) {
         cout <<  "|" << setw(5) << edges[a][b] << "|";
      }
      cout << endl;
   }
}

void displayMap() {
    for (auto values: edge) {
        cout << values.first << "\t";
        cout << values.second << endl;
    }
}



void printArray (float A[], int n) {
  for (int i = 0; i < n; ++i)
    cout << A[i] << ' ';
  cout << endl;
}

void merge (float A[], float Temp[], int p, int m, int r) {
  int i, j;
  for (i = m + 1; i > p; i--)
    Temp[i - 1] = A[i - 1];
  for (j = m; j < r; j++)
    Temp [r + m - j] = A[j + 1];
  // Misch-Schritt
  for (int k = p; k <= r; k++)
    if (Temp[j] < Temp [i])
      A[k] = Temp[j--];
    else
      A[k] = Temp[i++];
}

void descmerge (float A[], float Temp[], int p, int m, int r) {
  int i, j;
  for (i = m + 1; i > p; i--)
    Temp[i - 1] = A[i - 1];
  for (j = m; j < r; j++)
    Temp [r + m - j] = A[j + 1];
  // Misch-Schritt
  for (int k = p; k <= r; k++)
    if (Temp[j] > Temp [i])
      A[k] = Temp[j--];
    else
      A[k] = Temp[i++];
}

void mergesort (float A[], float Temp[], int p, int r) {
  // Put your code here!
    if (p<r) {
        int m = (p+r)/2;

        mergesort(A, Temp, p, m);
        mergesort(A, Temp, m+1, r);

        merge(A, Temp, p, m, r);
    }
}

void descmergesort (float A[], float Temp[], int p, int r) {
  // Put your code here!
    if (p<r) {
        int m = (p+r)/2;

        descmergesort(A, Temp, p, m);
        descmergesort(A, Temp, m+1, r);

        descmerge(A, Temp, p, m, r);
    }
}

void startMergeSort (float A[], int n) {
  float* Temp = new float[n];
  mergesort (A, Temp, 0, n-1);
  delete [] Temp;
}

void startDescMergeSort (float A[], int n) {
  float* Temp = new float[n];
  descmergesort (A, Temp, 0, n-1);
  delete [] Temp;
}



int main() {
    setValues();
    setPlanet();
    setPlanetValue();
    calculateDistance(3,0);
    calculateDistance(9,0);
    calculateDistance(7,0);
    calculateDistance(5,0);
    calculateDistance(3,9);
    calculateDistance(9,7);
    calculateDistance(7,5);
    calculateDistance(1,3);
    calculateDistance(1,6);
    calculateDistance(6,9);
    calculateDistance(6,8);
    calculateDistance(8,7);
    calculateDistance(8,2);
    calculateDistance(2,5);
    calculateDistance(4,1);
    calculateDistance(4,6);
    calculateDistance(4,8);
    calculateDistance(4,2);
    displayMatrix();
    cout << endl;
    printGraph(graph, 10);
    cout << endl;
    const int n = 18;
    int x = 0;
    float A[n];
    for (auto values : edge) {
        A[x] = values.second;
        x++;
    }
    cout << "Original Array" << endl;
    printArray(A, n);
    startMergeSort(A, n);
    //cout << "Sorted Array" << endl;
    
    cout << endl;
    int temp = 0;
    string sortedEdges[18];
    for (auto i : A) {
      for (auto j : edge) {
         if (j.second == i) {
             sortedEdges[temp]=j.first;
             temp++;
         }
      }
   }
   cout << "List of edges in asecnding order: " << endl;
   //printArray(A, n);
   for (int i = 0; i < 18; i++) {
       cout << sortedEdges[i] << ' ' << A[i] << endl;
   }
    cout << endl;
    cout << "Original Value Array" << endl;
    printArray(value, planetvalues.size());
    startDescMergeSort(value, planetvalues.size());
    int index = 0;
    string sortedPlanets[10];
    for (auto i : value) {
      for (auto j : planetvalues) {
         if (j.second == i) {
             sortedPlanets[index]=j.first;
             index++;
         }
      }
   }
   cout << endl;
   cout << "List of planets in descending order according to value: " << endl;
    for (int i = 0; i < 10; i++) {
       cout << sortedPlanets[i] << ' ' << value[i] << endl;
   }
   cout << endl;

   
}

