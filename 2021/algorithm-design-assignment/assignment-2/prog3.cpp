#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//disjoint set data structure
int fathers[100];

int find(int x){
	if(fathers[x] == x){
		return x;
	}
	return find(fathers[x]);
}

void unite(int x, int y){
	int fx =  find(x);
	int fy =  find(y);
	fathers[fx] = fy;
}

int main(){
	// inititialize  fathers for the disjoint sets
	for(int i =0;i<100;i++){
		fathers[i]=i;
	}
	// declaring the variables to load input
	int n,m;
	int a,b;
	double w;
	vector < pair < int , pair < int , int > > > edges;
	//loading the input
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>a>>b>>w;
		edges.push_back(make_pair(w,make_pair(a,b)));
	}
	//we print a linne to separate input from output 
	cout<<endl;
	//now the  kruskal algo start
	//first delcare variable for mst
	double mst_weight = 0.0;
	int mst_edges  = 0;
	int mst_ni = 0;
	//step 1 sort the list
	sort(edges.begin(),edges.end());
	//step 2-3:
	while((mst_edges < n-1) || (mst_ni < m)){
		// we brake the edge into the three integers they describe it 
		a = edges[mst_ni].second.first;
		b = edges[mst_ni].second.second;
		w = edges[mst_ni].first;
		// we check if the edge is ok to be included in the mst 
		// if a and b are in different trees (if they are on the same we will create a cycle)
		if(find(a) != find(b)){
			// we unite the two trees the edge connects
			unite(a,b);
			// we add the weight of the edge
			mst_weight += w;
			// we print the edge and count it 
			cout<<a<<" "<<b<<" "<<w<<endl;
			mst_edges++;
		}
		// increase the index of the edge we will be checking
		mst_ni++;
	}
	// presenting the weight 
	cout<<"\nWeight of the MST is "<<mst_weight<<endl;
}