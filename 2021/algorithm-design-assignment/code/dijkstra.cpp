#include <math.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#define V 10
using namespace std;

int edges[10][10];
string arr[60];
int Xcords[10];
int Ycords[10];
int Zcords[10];
float weight[10];
float profit[10];
float value[10];
int i = 0;
int temp = 0;
int countX = 0;
int countY = 0;
int countZ = 0;
int countW = 0;
int countP = 0;
vector<int> graph[10];
string planets[10];
map<string, float> edge;
map<string, float> planetvalues;
ifstream inputfile("A2planets.txt");

class Planet {
   public:
    string p_name;
    int x, y, z;
    int weight, profit;
};

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
    if (b < e) {
        //the smaller index gets priorities to set first, since it'll appear before the latter planets
        adj[b].push_back(e);
    } else
        adj[e].push_back(b);
}

int minDistance(int distance[], bool sptSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;

    return min_index;
}

void setPlanet() {
    //planets array, look like this {"A","B","C"...}
    char letter[] = "A";
    planets[0] = letter[0];

    for (int i = 1; i < 10; i++) {
        planets[i] = static_cast<char>(letter[0] + i);
    }
}

// Function to print shortest
// path from source to j
// using parent array
void printPath(int parent[], int j) {
    // Base Case : If j is source
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}

int printSolution(int distance[], int n,
                  int parent[]) {
    int source = 0;
    printf("Planet\t Distance\tShortest Path");
    for (int i = 1; i < V; i++) {
        printf("\n%d -> %d \t %d\t\t%d ",
               source, i, distance[i], source);
        printPath(parent, i);
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

void dijkstra(int graph[V][V], int source) {
    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    int distance[V];

    // sptSet[i] will true if planet
    // i is included / in shortest
    // path tree or shortest distance
    // from src to i is finalized
    bool sptSet[V];

    // Parent array to store
    // shortest path tree
    int parent[V];

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        parent[0] = -1, distance[i] = INT_MAX, sptSet[i] = false;
    }

    // Distance of source planet
    // from itself is always 0
    distance[source] = 0;

    // Find shortest path
    // for all planet
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance
        // planet from the set of
        // planets not yet processed.
        // u is always equal to src
        // in first iteration.
        int u = minDistance(distance, sptSet);

        // Mark the picked planet
        // as processed
        sptSet[u] = true;

        // Update dist value of the
        // adjacent planets of the
        // picked planet.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                distance[u] + graph[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = distance[u] + graph[u][v];
            }
    }
    // print the constructed
    // distance array
    printSolution(distance, V, parent);
}

void calculateDistance(int a, int b) {
    int value = (Xcords[b] - Xcords[a]) * (Xcords[b] - Xcords[a]) + (Ycords[b] - Ycords[a]) * (Ycords[b] - Ycords[a]) + (Zcords[b] - Zcords[a]) * (Zcords[b] - Zcords[a]);
    int result = sqrt(value);
    edges[a][b] = result;
    edges[b][a] = result;
    edge[planets[a] + planets[b]] = result;
    setList(graph, a, b);
}

int main() {
    setValues();
    setPlanet();
    setPlanetValue();
    calculateDistance(3, 0);
    calculateDistance(9, 0);
    calculateDistance(7, 0);
    calculateDistance(5, 0);
    calculateDistance(3, 9);
    calculateDistance(9, 7);
    calculateDistance(7, 5);
    calculateDistance(1, 3);
    calculateDistance(1, 6);
    calculateDistance(6, 9);
    calculateDistance(6, 8);
    calculateDistance(8, 7);
    calculateDistance(8, 2);
    calculateDistance(2, 5);
    calculateDistance(4, 1);
    calculateDistance(4, 6);
    calculateDistance(4, 8);
    calculateDistance(4, 2);
    dijkstra(edges, 0);
}
