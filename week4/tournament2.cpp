#include <iostream>
#include <iomanip>
#include <string>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#define DEBUG

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::setS, 
                              boost::vecS, 
                              boost::directedS,
                              boost::no_property,
                              boost::property<boost::edge_capacity_t, long, 
                                              boost::property<boost::edge_residual_capacity_t, long, 
                                                              boost::property<boost::edge_reverse_t, Traits::edge_descriptor>
                                                              >
                                              >
                              > Graph;

typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor     Edge;
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacity;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type   ReverseEdge;


struct TeamInfo {
    long points;
    int battlePoints;
    int neighbours;
    int index;
    TeamInfo(long points, int index) : points(points), battlePoints(0), neighbours(0), index(index) {}
    TeamInfo() : points(0), battlePoints(0), neighbours(0), index(-1) {}
};

int main() 
{
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);

    // Test sets: ca. 100
    int T; std::cin >> T;
    for (int t = 0; t < T; t++) {

        int V; std::cin >> V; // Teams; 1 <= V <= 100
        int E; std::cin >> E; // Matches; 0 <= E <= 100

        Graph graph(V+2);
        Vertex source(V);
        Vertex sink(V+1);
        long totalPoints = 0;
        std::map<std::string, TeamInfo> teams;
        EdgeCapacity capacities = boost::get(boost::edge_capacity, graph);
        ReverseEdge reverseEdges = boost::get(boost::edge_reverse, graph);

        // Read the teams and the points they already have
        for (int v = 0; v < V; v++) {
            long points; std::cin >> points;
            std::string name;  std::cin >> name;
            teams[name] = TeamInfo(points, v);
            totalPoints += points;
        }//v

        // Get the remaining matches
        for (int e = 0; e < E; e++) {
            std::string foo, team1, team2;
            std::cin >> team1 >> foo >> team2;
            teams[team1].neighbours++;
            teams[team1].battlePoints++; // This point will go to either team1 or team2 -- max flow will decide.
            teams[team2].neighbours++;
            totalPoints++;

            int u = teams[team1].index; int v = teams[team2].index;
            Edge edge, reverse; bool added;

            boost::tie(edge, added) = boost::add_edge(u, v, graph);
            boost::tie(reverse, added) = boost::add_edge(v, u, graph);

            capacities[edge] = 1;
            capacities[reverse] = 0;
            reverseEdges[edge] = reverse;
            reverseEdges[reverse] = edge;
        }//e

        // Add the point source
        for (std::map<std::string, TeamInfo>::iterator it = teams.begin(); it != teams.end(); it++) {
            Edge edge, reverse; bool added;
            int v = (*it).second.index;

            boost::tie(edge, added) = boost::add_edge(source, v, graph);
            boost::tie(reverse, added) = boost::add_edge(v, source, graph);

            capacities[edge] = (*it).second.points + (*it).second.battlePoints;

            std::cerr << "Edge " << edge << " has capacity " << capacities[edge] << "\n";
            capacities[reverse] = 0;
            reverseEdges[edge] = reverse;
            reverseEdges[reverse] = edge;
        }//v

        // Add the point sink
        for (std::map<std::string, TeamInfo>::iterator it = teams.begin(); it != teams.end(); it++) {
            Edge edge, reverse; bool added;
            int v = (*it).second.index;

            boost::tie(edge, added) = boost::add_edge(v, sink, graph);
            boost::tie(reverse, added) = boost::add_edge(sink, v, graph);

            capacities[edge] = 0; //< To be modified while testing
            capacities[reverse] = 0;
            reverseEdges[edge] = reverse;
            reverseEdges[reverse] = edge;
        }//v

        // For all teams check if it can win: Assume the team wins all games and set the number of points
        // it achieves as maximum for the other teams.
        for (std::map<std::string, TeamInfo>::iterator it = teams.begin(); it != teams.end(); it++) {
            long teamCanScore = (*it).second.points + (*it).second.neighbours;
            for (int v = 0; v < V; v++) {
                bool exists; Edge edge;
                boost::tie(edge, exists) = boost::edge(v, sink, graph);
                if (!exists) {
                    std::cerr << "Edge not found! " << edge << "\n";
                }
                capacities[edge] = teamCanScore;
            }//v

            long flow = boost::push_relabel_max_flow(graph, source, sink);
            std::cerr << "Team can score " << teamCanScore << " points if it wins all games.\n";
            std::cerr << "Flow: " << flow << " of " << totalPoints << " for " << std::setw(2) << (*it).second.index << " " << (*it).first << "\n";
        }

#ifdef DEBUG
        std::cerr << "—————————————————————————————————————————————\n";
        for (std::map<std::string, TeamInfo>::iterator it = teams.begin(); it != teams.end(); it++) {
            std::cerr << std::setw(2) <<  (*it).second.points << " points, " 
                      << std::setw(2) << (*it).second.neighbours << " neighbours and " 
                      << std::setw(2) << (*it).second.battlePoints << " battle points: " << (*it).first << "\n";
        }
#endif


    }//t
}
