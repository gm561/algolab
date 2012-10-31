#include <vector>
#include <map>

#include <iostream>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list <setS, vecS, undirectedS> Graph;
typedef Graph::edge_descriptor Edge;
typedef Graph::vertex_descriptor Vertex;

typedef map<string, vector<int> >::iterator MI ;
typedef vector<int>::iterator VI;

static const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin>>TC;
    for(int tc = 0; tc < TC; ++tc) {
	int n,c,f;
	cin>>n>>c>>f;

	Graph g(n);

	//number of common characteristics between students
	vector<vector<int> > commons(n, vector<int>(n,0));

	//map characteristics to students
	map<string, vector<int> > cars;

	//read all students characteristsics
	for(int i = 0; i < n; ++i) {
	    //student characeristics;
	    string scar;
	    for(int j = 0; j < c; ++j) {
		cin>>scar;
		//not a know characteristics
		if(cars.find(scar) == cars.end()) {
		    cars[scar] = vector<int>();
		}
		else {
		    for(VI it = cars[scar].begin() ; it != cars[scar].end(); ++it) {
			//create connection between students with common characterisitscs
			++commons[i][*it];
			++commons[*it][i];
		    }
		}
		cars[scar].push_back(i);
	    }
	}

	for(int i = 0; i < n; ++i) {
	    for(int j = i + 1; j < n; ++j) {
		if(commons[i][j] > f) {
		    Edge e; bool result;
		    tie(e,result) = add_edge(i, j, g);
		}
	    }
	}

	std::vector<Vertex> mate(n);
	edmonds_maximum_cardinality_matching(g, &mate[0]);

	bool stop = false;
	for(int i = 0 ; i < n; ++i) {
	    if(mate[i] == NULL_VERTEX) {
		stop = true;
		break;
	    }
	}

	if(stop) {
	    cout<<"optimal\n";
	}
	else {
	    cout<<"not optimal\n";
	}
    }

    return 0;
}
