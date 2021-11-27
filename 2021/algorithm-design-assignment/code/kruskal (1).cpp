#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <limits>
#include <utility>
#include <math.h>

using namespace std;

//vector<int> rank;
//vector<int> parent;
//pair<double, pair<int,int>> edge;
//list<edge> edges;

vector<string> planetName;
vector<int> x;
vector<int> y;
vector<int> z;
vector<int> w;
vector<int> p;
vector<float> dist;

class Edge{
public:

    int source;
    int destination;
    int edgeWeight;
    string pSource;
    string pDest;
};

class Map{
public:
    int node;
    int edges;

    Edge* edge;
};

class Mapsubset{
public:
    int parent;
    int rank;
};

//Calculate the distance between two  nodes
int distance(int x1,int x2, int y1, int y2, int z1, int z2)
{
    int d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) +  pow(z2 - z1, 2)); 
    return d;
}

//Creates a graph with n vertices and e edges
Map* constructMap(int n, int e)
{
    Map* map = new Map;
    map->node = n;
    map->edges = e;

    map->edge = new Edge[e];

    return map;
}

//Find set of an element i
int findPath(Mapsubset subsets[], int i)
{
    if(subsets[i].parent != i)
    {
        subsets[i].parent = findPath(subsets, subsets[i].parent);
    }

    return subsets[i].parent;
}

//Compare 2 edges according to their weight
int compWeight(const void* edge1, const void* edge2)
{
    Edge* e1 = (Edge*)edge1;
    Edge* e2 = (Edge*)edge2;

    return e1->edgeWeight > e2->edgeWeight;
}

//Do union of 2 sets
void Union(Mapsubset subsets[], int a, int b)
{
    int rootA = findPath(subsets, a);
    int rootB = findPath(subsets, b);

    //Put node with lower rank under the node with higher rank(root)
    if(subsets[rootA].rank < subsets[rootB].rank)
        subsets[rootA].parent = rootB;

    else if(subsets[rootA].rank > subsets[rootB].rank)
        subsets[rootB].parent = rootA;
    
    //If ranks are the same, make one as root & increase it's rank by 1
    else{
        subsets[rootB].parent = rootA;
        subsets[rootA].rank++;
    }
}

void kruskal(Map* map)
{
    int nodes = map->node;
    Edge mst[nodes];
    int edgeIndex = 0;
    int edgeSortedIndex = 0;

    //Sort all edges in increasing order of their weight
    qsort(map->edge, map->edges, sizeof(map->edge[0]), compWeight);

    //Allocate memory
    Mapsubset* subsets = new Mapsubset[(nodes * sizeof(Mapsubset))];

    //Create subsets with 1 tuple_element
    for(int i=0; i < nodes; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    //Create edges
    while(edgeIndex < nodes-1 && edgeSortedIndex < map->edges)
    {
        //Pick smallest edge and increase index
        Edge nextEdge = map->edge[edgeSortedIndex++]; 

        int a = findPath(subsets, nextEdge.source);
        int b = findPath(subsets, nextEdge.destination);

        //If adding the edge does not form a cycle, add it to the MST result
        if(a != b)
        {
            mst[edgeIndex++] = nextEdge;
            Union(subsets, a,b);
        }

    }

    cout << "Edges involved in MST based on Kruskal Algorithm" << endl;
    int minCost = 0;
    for(int i=0; i<edgeIndex; i++)
    {
        cout << planetName[mst[i].source] << " -- " << planetName[mst[i].destination] << " == " << mst[i].edgeWeight <<endl;

        minCost = minCost + mst[i].edgeWeight;
    }

    cout << "Minimum Cost of Spanning Tree: " << minCost << endl;
}

int main(){

    string name;
    int xcor, ycor, zcor, weight, profit;
    float distanceResult;
    ifstream inputFile("A2planets.txt");

    if(inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            inputFile >> name >> xcor >> ycor >> zcor >> weight >> profit;
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            planetName.push_back(name);
            x.push_back(xcor);
            y.push_back(ycor);
            z.push_back(zcor);
            w.push_back(weight);
            p.push_back(profit);
            
        }
    }
    /**
    for(int i = 0;i<9;i++)
    {     
        distanceResult = distance(x[i+1],x[i],y[i+1],y[i],z[i+1],z[i]);
        dist.push_back(distanceResult);
    }*/
    Map* map = constructMap(10,18);
    
    
    //Creating the edges
    //Node A to Node D
    map->edge[0].pSource = planetName[0];
    map->edge[0].source= 0;
    map->edge[0].pDest = planetName[3];
    map->edge[0].destination = 3;
    map->edge[0].edgeWeight = distance(x[0],x[3],y[0],y[3],z[0],z[3]);
    
    //Node A to Node J
    map->edge[1].pSource = planetName[0];
    map->edge[1].source= 0;
    map->edge[1].pDest = planetName[9];
    map->edge[1].destination = 9;
    map->edge[1].edgeWeight = distance(x[0],x[9],y[0],y[9],z[0],z[9]);

    //Node A to H
    map->edge[2].pSource = planetName[0];
    map->edge[2].source= 0;
    map->edge[2].pDest = planetName[7];
    map->edge[2].destination = 7;
    map->edge[2].edgeWeight = distance(x[0],x[7],y[0],y[7],z[0],z[7]);

    //Node A to F
    map->edge[3].pSource = planetName[0];
    map->edge[3].source= 0;
    map->edge[3].pDest = planetName[5];
    map->edge[3].destination = 5;
    map->edge[3].edgeWeight = distance(x[0],x[5],y[0],y[5],z[0],z[5]);

    //Node D to B
    map->edge[4].pSource = planetName[3];
    map->edge[4].source= 3;
    map->edge[4].pDest = planetName[1];
    map->edge[4].destination = 1;
    map->edge[4].edgeWeight = distance(x[3],x[1],y[3],y[1],z[3],z[1]);

    //Node J to G
    map->edge[5].pSource = planetName[9];
    map->edge[5].source= 9;
    map->edge[5].pDest = planetName[6];
    map->edge[5].destination = 6;
    map->edge[5].edgeWeight = distance(x[9],x[6],y[9],y[6],z[9],z[6]);

    //Node H to I
    map->edge[6].pSource = planetName[7];
    map->edge[6].source= 7;
    map->edge[6].pDest = planetName[8];
    map->edge[6].destination = 8;
    map->edge[6].edgeWeight = distance(x[7],x[8],y[7],y[8],z[7],z[8]);

    //Node F to C
    map->edge[7].pSource = planetName[5];
    map->edge[7].source= 5;
    map->edge[7].pDest = planetName[2];
    map->edge[7].destination = 2;
    map->edge[7].edgeWeight = distance(x[5],x[2],y[5],y[2],z[5],z[2]);

    //Node B to E
    map->edge[8].pSource = planetName[1];
    map->edge[8].source= 1;
    map->edge[8].pDest = planetName[4];
    map->edge[8].destination = 4;
    map->edge[8].edgeWeight = distance(x[1],x[4],y[1],y[4],z[1],z[4]);

    //Node G to E
    map->edge[9].pSource = planetName[6];
    map->edge[9].source= 6;
    map->edge[9].pDest = planetName[4];
    map->edge[9].destination = 4;
    map->edge[9].edgeWeight = distance(x[6],x[4],y[6],y[4],z[6],z[4]);

    //Node I to E
    map->edge[10].pSource = planetName[8];
    map->edge[10].source= 8;
    map->edge[10].pDest = planetName[4];
    map->edge[10].destination = 4;
    map->edge[10].edgeWeight = distance(x[8],x[4],y[8],y[4],z[8],z[4]);

    //Node C to E
    map->edge[11].pSource = planetName[2];
    map->edge[11].source= 2;
    map->edge[11].pDest = planetName[4];
    map->edge[11].destination = 4;
    map->edge[11].edgeWeight = distance(x[2],x[4],y[2],y[4],z[2],z[4]);

    //Printing distance (will be removed)
    /**
    for(int i=0;i<12;i++)
    {
        cout<<map->edge[i].edgeWeight<<endl;

    }*/

    kruskal(map);
    return 0;

}