#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

#define INT_MAX 2147483647

const int planetNum = 10;
char map[7][7];

class Planet {
   public:
    int p_number;   //planet number
    string p_name;  //planet
    int x;
    int y;
    int z;  // coordinates
    int weight;
    int profit;
};

class Edge {
   public:
    int planet1;   //source
    int planet2;   //distance
    int distance;  //distance between 2 vertices
};

vector<int> pathStore;

void initmap(char m[7][7]) {
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            m[i][j] = ' ';
}

void planets(char m[7][7]) {
    m[0][3] = 'A';
    m[4][0] = 'B';
    m[4][6] = 'C';
    m[2][0] = 'D';
    m[6][3] = 'E';
    m[2][6] = 'F';
    m[4][2] = 'G';
    m[2][4] = 'H';
    m[4][4] = 'I';
    m[2][2] = 'J';
}

void connect(char m[7][7], int a, int b) {
    switch (a) {
        case 1:          // A
            if (b == 4)  // connect to D
            {
                m[0][0] = '+';
                m[0][1] = '-';
                m[0][2] = '-';
                m[1][0] = '|';
            }
            if (b == 6)  // connect to F
            {
                m[0][6] = '+';
                m[0][5] = '-';
                m[1][6] = '|';
            }
            if (b == 10)  // connect to J
            {
                m[0][2] = '+';
                m[1][2] = '|';
            }
            if (b == 8)  // connect to H
            {
                m[0][4] = '+';
                m[1][4] = '|';
            }
            break;
        case 2:          // B
            if (b == 4)  // connect to D
            {
                m[3][0] = '|';
            }
            if (b == 5)  // connect to E
            {
                m[6][0] = '+';
                m[6][1] = '-';
                m[6][2] = '-';
                m[5][0] = '|';
            }
            if (b == 7)  // connect to G
            {
                m[4][1] = '-';
            }
            break;
        case 3:          // C
            if (b == 6)  // connect to F
            {
                m[3][6] = '|';
            }
            if (b == 5)  // connect to E
            {
                m[6][6] = '+';
                m[6][5] = '-';
                m[6][4] = '-';
                m[5][6] = '|';
            }
            if (b == 9)  // connect to I
            {
                m[4][5] = '-';
            }
            break;
        case 4:           // D
            if (b == 10)  // connect to J
            {
                m[2][1] = '-';
            }
            break;
        case 5:          // E
            if (b == 7)  // connect to G
            {
                m[6][2] = '+';
                m[5][2] = '|';
            }
            if (b == 9)  // connect to I
            {
                m[6][4] = '+';
                m[5][4] = '|';
            }
            break;
        case 6:          //
            if (b == 8)  // connect to H
            {
                m[2][5] = '-';
            }
            break;
        case 7:           // G
            if (b == 10)  // connect to J
            {
                m[3][2] = '|';
            }
            if (b == 9)  // connect to I
            {
                m[4][3] = '-';
            }
            break;
        case 8:           // H
            if (b == 10)  // connect to J
            {
                m[2][3] = '-';
            }
            if (b == 9)  // connect to I
            {
                m[3][4] = '|';
            }
            break;
    }
}

void edges(char m[7][7], int a, int b) {
    connect(m, a, b);
}

void display(char m[7][7]) {
    cout << endl;
    for (int i = 0; i < 7; i++) {
        cout << "  ";
        for (int j = 0; j < 7; j++)
            cout << m[i][j];
        cout << endl;
    }
}

int distancez(Planet p1, Planet p2)  /////////// CALCULATING DISTANCE
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
};

int minDistance(int outDistance[], bool sptSet[], int planetNum) {
    int minimum = INT_MAX, minimum_index;

    for (int i = 0; i < planetNum; i++) {
        if (sptSet[i] == false && outDistance[i] <= minimum) {
            minimum = outDistance[i], minimum_index = i;
        }
    }
    return minimum_index;
}

void printPath(int parents[], int i) {
    if (parents[i] == -1)  //stop the iteration
        return;

    printPath(parents, parents[i]);

    cout << i << " ";

    pathStore.push_back(i);
}

void printSolution(int outDistance[], int planetNum, int parents[], Planet P[], char m[7][7]) {
    int src = 0;
    int destination = 0;
    int alphabetValSrc = 0;
    int alphabetValDes = 0;

    cout << "Planet lists:" << endl;

    for (int i = 0; i < planetNum; i++) {
        if (i == 0) {
            cout << endl;
            cout << P[0].p_name << " --> " << P[i].p_name << " (" << P[i].x << "," << P[i].y << "," << P[i].z << ") Distance: " << outDistance[i];
        } else {
            cout << endl;
            cout << P[0].p_name << " --> " << P[i].p_name << " (" << P[i].x << "," << P[i].y << "," << P[i].z << ") Distance: " << outDistance[i];
        }

        if (i != 0) {
            cout << " "
                 << "Path: " << src << " ";
            printPath(parents, i);

            cout << endl;

            destination = pathStore.front();  //taking the 1st element in the vector
            //cout << destination;

            for (int i = 0; i < pathStore.size(); i++) {
                alphabetValSrc = src + 1;  //plus 1 untuk dapatkan nombor alphabet 'A'
                alphabetValDes = destination + 1;

                //cout<<" Test "<<i<<": "<< alphabetValSrc<<" "<<alphabetValDes<<endl;
                edges(map, alphabetValSrc, alphabetValDes);
                edges(map, alphabetValDes, alphabetValSrc);

                src = pathStore[i];
                destination = pathStore[i + 1];
            }
        } else {
            cout << endl;
        }

        pathStore.clear();  //clear the vector
        src = 0;            //set the source to 0 back
    }
}

void dijkstra(int graf[planetNum][planetNum], int source, Planet P[], char m[7][7]) {
    int outDistance[planetNum];  //shortest distance from source to planets

    bool sptSet[planetNum];  //true if planets included in shortest distance or path

    int parents[planetNum];  //for storing shortest path

    for (int i = 0; i < planetNum; i++)  //initialize all distances infinity
    {
        parents[0] = -1;
        outDistance[i] = INT_MAX;  //infinity
        sptSet[i] = false;
    }

    outDistance[source] = 0;  //starting of program the source will always be zero

    /////// FINDING SHORTEST PATH FOR ALL VERTICES ///////
    for (int i = 0; i < planetNum - 1; i++) {
        int u = minDistance(outDistance, sptSet, planetNum);  //taking the minimum distance planet from the planets

        //cout << u << " " ;

        sptSet[u] = true;  //flag the selected planets processes

        for (int j = 0; j < planetNum; j++) {
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[j] && graf[u][j] && outDistance[u] + graf[u][j] < outDistance[j]) {
                parents[j] = u;
                outDistance[j] = outDistance[u] + graf[u][j];
            }
        }
    }
    printSolution(outDistance, planetNum, parents, P, m);
}

///////// DISPLAY PLANET DETAILS ////////////
void disp(Edge E[], Planet P[], int planetNum, int conezion) {
    cout << "Planet lists:" << endl;
    for (int i = 0; i < planetNum; i++) {
        cout << P[i].p_number << ":" << P[i].p_name << " (" << P[i].x << "," << P[i].y << "," << P[i].z << ") Distance="
             << "NA" /*P[i].weight*/ << " Predecessor="
             << "NA" /*P[i].profit*/ << endl;
    }

    cout << endl
         << endl;

    for (int i = 0; i < conezion; i++) {
        cout << E[i].planet1 << " " << E[i].planet2 << " " << E[i].distance << endl;
    }
};

int main() {
    //number of planets available in this assignment A-J
    const int conezion = 18;  //number of connection between all edges

    ////////// PLANET FILES DATA ////////////
    string p_name;
    int x, y, z;
    int weight;
    int profit;
    int p_number;
    int distance;

    ////////// EDGES FILES DATA ////////////
    int planet1;
    int planet2;

    Planet P[planetNum];  //planets object array
    Edge E[conezion];     //planets object array

    ifstream MyReadFile("A2planets.txt");  //planets file
    ifstream MyReadFile2("Edges.txt");     //edges file

    for (int i = 0; i < planetNum; i++) {
        if (MyReadFile >> p_name >> x >> y >> z >> weight >> profit) {
            P[i].p_number = i;
            P[i].p_name = p_name;
            P[i].x = x;
            P[i].y = y;
            P[i].z = z;
            P[i].weight = weight;
            P[i].profit = profit;
        }
    }

    for (int i = 0; i < conezion; i++) {
        if (MyReadFile2 >> planet1 >> planet2) {
            E[i].planet1 = planet1;
            E[i].planet2 = planet2;
            E[i].distance = distancez(P[E[i].planet1], P[E[i].planet2]);
        }
    }

    int graf[planetNum][planetNum] = {{0, 0, 0, distancez(P[0], P[3]), 0, distancez(P[0], P[5]), 0, distancez(P[0], P[7]), 0, distancez(P[0], P[9])},
                                      {0, 0, 0, distancez(P[1], P[3]), distancez(P[1], P[4]), 0, distancez(P[1], P[6]), 0, 0, 0},
                                      {0, 0, 0, 0, distancez(P[2], P[4]), distancez(P[2], P[5]), 0, 0, distancez(P[2], P[8]), 0},
                                      {distancez(P[0], P[3]), distancez(P[1], P[3]), 0, 0, 0, 0, 0, 0, 0, distancez(P[3], P[9])},
                                      {0, distancez(P[1], P[4]), distancez(P[2], P[4]), 0, 0, 0, distancez(P[4], P[6]), 0, distancez(P[4], P[8]), 0},
                                      {distancez(P[0], P[5]), 0, distancez(P[2], P[5]), 0, 0, 0, 0, distancez(P[5], P[7]), 0, 0},
                                      {0, distancez(P[1], P[6]), 0, 0, distancez(P[4], P[6]), 0, 0, 0, distancez(P[6], P[8]), distancez(P[6], P[9])},
                                      {distancez(P[0], P[7]), 0, 0, 0, 0, distancez(P[5], P[7]), 0, 0, distancez(P[7], P[8]), distancez(P[7], P[9])},
                                      {0, 0, distancez(P[2], P[8]), 0, distancez(P[4], P[8]), 0, distancez(P[6], P[8]), distancez(P[7], P[8]), 0, 0},
                                      {distancez(P[0], P[9]), 0, 0, distancez(P[3], P[9]), 0, 0, distancez(P[6], P[9]), distancez(P[7], P[9]), 0, 0}};

    initmap(map);  //initialize matrix with ' ' value

    planets(map);  // update matrix with the planet name

    dijkstra(graf, 0, P, map);

    display(map);
    //disp( E,  P,  planetNum,  conezion);
}
