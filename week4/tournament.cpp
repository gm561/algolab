#include<iostream>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS,
		       no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > >
		       > Graph;


typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;

struct Team {
    int points;
    string name;
    int matches;
    int toWin;
    int index;

    Team() : points(0), matches(0), index(-1), toWin(0) {}
};

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin>>TC;
    for(int tc = 0; tc < TC; ++tc) {
	map<string, Team> teams;

	int teams_number; cin>>teams_number;
	int matchups; cin>>matchups;

	Graph g(teams_number + 2);
	property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
	property_map<Graph, edge_reverse_t>::type reverse_edges = get(edge_reverse, g);

	Vertex source(teams_number);
	Vertex sink(teams_number + 1);

	int total_points = 0;

	//read teams
	for(int t = 0; t < teams_number; ++t) {
	    int points; cin>>points;
	    string name; cin>>name;
	    Team team; team.points = points; team.name = name; team.index = t;
	    // cerr<<"Team: " <<team.name<<" scored: " << team.points <<"\n";
	    teams[name] = team;
	    total_points += points;
	}

	//read matches, add to the graph as edges
	for(int m = 0; m < matchups; ++m) {
	    string t1,t2,empty;
	    cin>>t1>>empty>>t2;

	    int u = teams[t1].index;
	    int v = teams[t2].index;

	    ++teams[t1].matches;
	    ++teams[t2].matches;
	    teams[t1].toWin += 1;

	    Edge edge, reverse; bool result;
	    tie(edge, result) = add_edge(u,v,g); assert(result);
	    tie(reverse, result) = add_edge(v,u,g); assert(result);

	    capacity[edge] = 1;
	    capacity[reverse] = 0;
	    reverse_edges[edge] = reverse;
	    reverse_edges[reverse] = edge;

	    ++total_points;
	}

	//add source
	for(std::map<string, Team>::iterator it = teams.begin();
	    it != teams.end();
	    ++it) {
	    Edge edge, reverse; bool result;
	    int v = (*it).second.index;
	    tie(edge, result) = add_edge(source, v, g);
	    tie(reverse, result) = add_edge(v, source, g);

	    capacity[edge] = (*it).second.points + (*it).second.toWin;
	    capacity[reverse] = 0;
	    reverse_edges[edge] = reverse;
	    reverse_edges[reverse] = edge;
	}

	//add sink
	for(std::map<string, Team>::iterator it = teams.begin();
	    it != teams.end();
	    ++it) {
	    Edge edge, reverse; bool result;
	    int v = (*it).second.index;
	    tie(edge, result) = add_edge(sink, v, g);
	    tie(reverse, result) = add_edge(v, sink, g);

	    capacity[edge] = 0;
	    capacity[reverse] = 0;
	    reverse_edges[edge] = reverse;
	    reverse_edges[reverse] = edge;
	}

	//run algorithm
	for(std::map<string, Team>::iterator it = teams.begin();
	    it != teams.end();
	    ++it) {
	    int winningPoints = (*it).second.matches + (*it).second.points;

	    for(int i = 0; i < teams_number; ++i) {
		bool result; Edge edge;
		tie(edge,result) = boost::edge(i, sink, g);
		assert(result);
		capacity[edge] = winningPoints;
	    }

	    long flow = push_relabel_max_flow(g, source, sink);

	    // cerr<<"Flow: "<<flow<<" from " << total_points<< " winning points "
	    // 	<<winningPoints<<"\n";

	    if(flow == total_points) {
		cout<<(*it).second.name << " ";
	    }

	}
	cout<<"\n";
    }

    return 0;
}
