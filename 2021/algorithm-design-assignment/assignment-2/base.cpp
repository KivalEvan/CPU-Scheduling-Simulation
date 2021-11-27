#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Planet {
   public:
    string p_name;
    int x, y, z;
    int weight, profit;
    Planet() {
        this->p_name = "";
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->weight = 0;
        this->profit = 0;
    }
    Planet(const Planet& p) {
        this->p_name = p.p_name;
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
        this->weight = p.weight;
        this->profit = p.profit;
    }
    double calcValue() const {
        return this->weight > 0 ? static_cast<double>(this->profit) / static_cast<double>(this->weight) : 0;
    }
};

class Edge {
   public:
    string point_a, point_b;
    double distance;
};

double calcDistancePlanet(const Planet a, const Planet b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

// for now it go bidirectional
void connectVertex(double** am, vector<pair<int, double>> al[], Planet* p, const int x, const int y) {
    double dist = calcDistancePlanet(p[x], p[y]);
    al[x].push_back(make_pair(y, dist));
    al[y].push_back(make_pair(x, dist));
    am[x][y] = dist;
    am[y][x] = dist;
}

int countEdge(vector<pair<int, double>> al[], const int V) {
    int total = 0;
    for (int i = 0; i < V; i++) {
        total += al[i].size();
    }
    return total / 2;
}

void getEdgeList(const Planet* p, double** const am, Edge* ed, const int V, const int E) {
    int count = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i; j < V; j++) {
            if (am[i][j] != 0 && count < E) {
                ed[count].point_a = p[i].p_name;
                ed[count].point_b = p[j].p_name;
                ed[count].distance = am[i][j];
                count++;
            }
        }
    }
}

template <typename T>
void swap(T* a, T* b) {
    T t = *a;
    *a = *b;
    *b = t;
}

// template <typename T>
// int partition(T* arr, int low, int high) {
//     T pivot = arr[high];  // pivot
//     int i = (low - 1);    // Index of smaller element

//     for (int j = low; j <= high - 1; j++) {
//         // If current element is smaller than or
//         // equal to pivot
//         if (arr[j] <= pivot) {
//             i++;  // increment index of smaller element
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]);
//     return (i + 1);
// }

// template <typename T>
// void quickSort(T* arr, int low, int high) {
//     if (low < high) {
//         // pi is partitioning index, arr[p] is now
//         // at right place
//         int pi = partition(arr, low, high);

//         // Separately sort elements before
//         // partition and after partition
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }
// }

int partitionEdge(Edge* ed, const int low, const int high) {
    double pivot = ed[high].distance;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (ed[j].distance <= pivot) {
            i++;
            swap(&ed[i], &ed[j]);
        }
    }
    swap(&ed[i + 1], &ed[high]);
    return (i + 1);
}

void quickSortEdge(Edge* ed, const int low, const int high) {
    if (low < high) {
        int pi = partitionEdge(ed, low, high);
        quickSortEdge(ed, low, pi - 1);
        quickSortEdge(ed, pi + 1, high);
    }
}

int partitionPlanet(Planet* p, const int low, const int high) {
    double pivot = p[high].calcValue();
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (p[j].calcValue() <= pivot) {
            i++;
            swap(&p[i], &p[j]);
        }
    }
    swap(&p[i + 1], &p[high]);
    return (i + 1);
}

void quickSortPlanet(Planet* p, const int low, const int high) {
    if (low < high) {
        int pi = partitionPlanet(p, low, high);
        quickSortPlanet(p, low, pi - 1);
        quickSortPlanet(p, pi + 1, high);
    }
}

// since array is sorted, we can just reverse them to get either descending or ascending order
template <typename T>
void reverseArray(T* arr, int start, int end) {
    while (start < end) {
        T temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int** OIKnapsackAlgorithm(const Planet* p, const int V, const int W) {
    // new set + empty set of planet
    Planet* p_set = new Planet[V + 1];
    for (int i = 0; i < V; i++) {
        p_set[i + 1] = p[i];
    }
    // matrix[item + 1][weight + 1]
    int** matrix;
    matrix = new int*[V + 1];
    for (int i = 0; i < V + 1; i++) {
        matrix[i] = new int[W + 1];
        for (int w = 0; w < W + 1; w++) {
            matrix[i][w] = 0;
        }
    }
    // do algo and fill matrix
    for (int i = 0; i < V + 1; i++) {
        for (int w = 0; w < W + 1; w++) {
            if (p_set[i].weight <= w) {
                matrix[i][w] = i - 1 >= 0 ? max(p_set[i].profit + matrix[i - 1][w - p_set[i].weight], matrix[i - 1][w]) : 0;
            } else {
                matrix[i][w] = i - 1 >= 0 ? matrix[i - 1][w] : 0;
            }
        }
    }
    return matrix;
}

int* OIKnapsackGetSet(const Planet* p, int** const matrix, const int V, const int W) {
    int* set = new int[V];
    int i = V;
    int j = W;
    while (i > 0 && j > 0) {
        if (matrix[i][j] == (i - 1 > 0 ? matrix[i - 1][j] : 0)) {
            set[i - 1] = 0;
            i--;
        } else {
            set[i - 1] = 1;
            i--;
            j = j - p[i].weight;
        }
    }
    return set;
}

void OIKnapsackResult(const Planet* p, const int* set, const int V) {
    string order = "";
    int profit = 0;
    int weight = 0;
    cout << "0/1 Knapsack Result: " << endl;
    for (int i = 0; i < V; i++) {
        if (set[i] == 1) {
            if (order != "") {
                order += " -> ";
            }
            cout << p[i].p_name << endl;
            cout << "Profit: " << p[i].profit << '$' << endl;
            cout << "Weight: " << p[i].weight << " ton(s)" << endl;
            cout << "Value: " << p[i].calcValue() << endl;
            cout << endl;
            order += p[i].p_name;
            profit += p[i].profit;
            weight += p[i].weight;
        }
    }
    cout << "Planet to visit: " << order << endl;
    cout << "Total Profit: " << profit << endl;
    cout << "Total Weight: " << weight << endl;
}

void printList(const Planet* p, vector<pair<int, double>> al[], const int V) {
    int v;
    double w;
    for (int i = 0; i < V; i++) {
        cout << p[i].p_name;
        for (auto it = al[i].begin(); it != al[i].end(); it++) {
            v = it->first;
            w = it->second;
            cout << " -> " << p[v].p_name << " | "
                 << static_cast<int>(w);
        }
        cout << endl;
    }
}

template <typename T>
void printMatrix(const Planet* p, T** const am, const int V) {
    cout << "        ";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].p_name;
    }
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << p[i].p_name;
        for (int j = 0; j < V; j++) {
            cout << setw(10) << static_cast<int>(am[i][j]);
        }
        cout << endl;
    }
}

template <typename T>
void printOIKnapsackMatrix(const Planet* p, T** const am, const int V, const int W) {
    cout << "0/1 Knapsack Table:" << endl;
    cout << "            ";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].p_name;
    }
    cout << endl
         << "  ";
    for (int i = 0; i < V + 1; i++) {
        cout << setw(10) << i;
    }
    cout << endl;
    for (int i = 0; i < W + 1; i++) {
        cout << setw(2) << i;
        for (int j = 0; j < V + 1; j++) {
            cout << setw(10) << static_cast<int>(am[j][i]);
        }
        cout << endl;
    }
}

void printGraph(const Planet* p, vector<pair<int, double>> al[], double** const am, const int V) {
    cout << "Adjacency List:" << endl;
    printList(p, al, V);
    cout << endl;
    cout << "Adjacency Matrix:" << endl;
    printMatrix(p, am, V);
}

template <typename T>
void printArray(const T* arr, int count) {
    for (int i = 0; i < count; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void printPlanetEdge(const Edge* ed, const int E) {
    for (int i = 0; i < E; i++) {
        cout << ed[i].point_a << " -- " << ed[i].point_b << " distance: " << static_cast<int>(ed[i].distance) << endl;
    }
}

void printPlanetValue(const Planet* p, const int V) {
    for (int i = 0; i < V; i++) {
        cout << p[i].p_name << " value: " << p[i].calcValue() << endl;
    }
}

void printKnapsackTable(const Planet* p, const int V) {
    cout << "Knapsack Table:";
    cout << endl
         << setw(10) << "Planet";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].p_name;
    }
    cout << endl
         << setw(10) << "Profit";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].profit;
    }
    cout << endl
         << setw(10) << "Weigth";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].weight;
    }
    cout << endl
         << setw(10) << "Value";
    for (int i = 0; i < V; i++) {
        cout << setw(10) << p[i].calcValue();
    }
    cout << endl;
}

int main() {
    const int P_COUNT = 10;
    Planet* p = new Planet[P_COUNT];
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
    if (file_planet.is_open()) {
        for (int i = 0; i < P_COUNT; i++) {
            file_planet >> p[i].p_name >> p[i].x >> p[i].y >> p[i].z >> p[i].weight >> p[i].profit;
        }
    }
    file_planet.close();

    // ADJACENCY LIST
    // pair<planet_id, distance>
    vector<pair<int, double>> adj_list[P_COUNT];

    // ADJACENCY MATRIX
    // ah yes, pointer to pointer
    double** adj_matrix;
    adj_matrix = new double*[P_COUNT];
    for (int i = 0; i < P_COUNT; i++) {
        adj_matrix[i] = new double[P_COUNT];
        for (int j = 0; j < P_COUNT; j++) {
            adj_matrix[i][j] = 0;
        }
    }

    // connect the planet the game
    // for now it connects both way
    connectVertex(adj_matrix, adj_list, p, 0, 3);
    connectVertex(adj_matrix, adj_list, p, 0, 5);
    connectVertex(adj_matrix, adj_list, p, 0, 7);
    connectVertex(adj_matrix, adj_list, p, 0, 9);
    connectVertex(adj_matrix, adj_list, p, 1, 3);
    connectVertex(adj_matrix, adj_list, p, 1, 4);
    connectVertex(adj_matrix, adj_list, p, 1, 6);
    connectVertex(adj_matrix, adj_list, p, 2, 4);
    connectVertex(adj_matrix, adj_list, p, 2, 5);
    connectVertex(adj_matrix, adj_list, p, 2, 8);
    connectVertex(adj_matrix, adj_list, p, 3, 9);
    connectVertex(adj_matrix, adj_list, p, 4, 6);
    connectVertex(adj_matrix, adj_list, p, 4, 8);
    connectVertex(adj_matrix, adj_list, p, 5, 7);
    connectVertex(adj_matrix, adj_list, p, 6, 8);
    connectVertex(adj_matrix, adj_list, p, 6, 9);
    connectVertex(adj_matrix, adj_list, p, 7, 8);
    connectVertex(adj_matrix, adj_list, p, 7, 9);

    // PRINT BOTH ADJACENCY MATRIX AND ADJANCENCY LIST
    // print some info for verification
    printGraph(p, adj_list, adj_matrix, P_COUNT);

    // SORT EDGE DISTANCE BY ASCENDING ORDER
    // get edge list
    const int E_COUNT = countEdge(adj_list, P_COUNT);
    Edge* planet_edge = new Edge[E_COUNT];
    getEdgeList(p, adj_matrix, planet_edge, P_COUNT, E_COUNT);
    // cout << endl
    //      << "Original Edge:" << endl;
    // printPlanetEdge(planet_edge, E_COUNT);
    quickSortEdge(planet_edge, 0, E_COUNT - 1);
    cout << endl
         << "Sorted edge distance in ascending order:" << endl;
    printPlanetEdge(planet_edge, E_COUNT);

    // SORT PLANET VALUE BY DESCENDING ORDER
    // copy planet to sort for value
    Planet* planet_value = new Planet[P_COUNT];
    for (int i = 0; i < P_COUNT; i++) {
        planet_value[i] = p[i];
    }
    // cout << endl
    //      << "Original Value:" << endl;
    // printPlanetValue(planet_value, P_COUNT);
    quickSortPlanet(planet_value, 0, P_COUNT - 1);
    // cout << endl
    //      << "Sorted Value:" << endl;
    // printPlanetValue(planet_value, P_COUNT);
    reverseArray(planet_value, 0, P_COUNT - 1);
    cout << endl
         << "Sorted planet Value in descending order:" << endl;
    printPlanetValue(planet_value, P_COUNT);

    // PROGRAM 4 - DYNAMIC PROGRAMMING
    // 1/0 Knapsack Algorithm
    // use either 'p' or 'planet_value'
    // 'planet_value' as it is sorted by value
    // would use shortest path to find planet visting order but i dont have them at the time of writing this code
    const int MAX_WEIGHT = 80;
    cout << endl;
    printKnapsackTable(p, P_COUNT);
    int** knapsackMatrix = OIKnapsackAlgorithm(p, P_COUNT, MAX_WEIGHT);
    int* knapsackSet = OIKnapsackGetSet(p, knapsackMatrix, P_COUNT, MAX_WEIGHT);
    cout << endl;
    printOIKnapsackMatrix(p, knapsackMatrix, P_COUNT, MAX_WEIGHT);
    cout << endl;
    // printArray(knapsackSet, P_COUNT);
    OIKnapsackResult(p, knapsackSet, P_COUNT);

    cout << endl
         << "Enter anything to exit...";
    cin.get();
    return 0;
}
