
#include <iostream>
#include <iostream>

#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list <setS, vecS, undirectedS> Graph;
typedef Graph::edge_descriptor Edge;
typedef Graph::vertex_descriptor Vertex;

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin>>TC;
    for(int tc = 0; tc < TC; ++tc) {
	int n; cin>>n;

	vector<vector<int> > blogs(n, vector<int>(n-1));
	for(int i = 0; i < n; ++i) {
	    for(int j = 0; j < n - 1 ; ++j) {
		cin>>blogs[i][j];
	    }
	}

	Graph g(n);

	int threhold = 0;
	//try to add edges as long as graph is plannar
	for(int i = 0; i < n - 1; ++i) {
	    //add all edges for the give round
	    for(int j = 0; j < n; ++j) {
		int u = blogs[j][i];
		add_edge(j,u,g);
	    }

	    bool is_planar = boyer_myrvold_planarity_test(g);
	    if(is_planar){
		++threhold;
	    }
	    else {
		for(int j = 0; j < n; ++j) {
		    int u = blogs[j][i];
		    remove_edge(u,i,g);
		}
		break;
	    }
	}

	//+ strongly connected component :).

	cout<<threhold<<"\n";
    }

    return 0;
}

