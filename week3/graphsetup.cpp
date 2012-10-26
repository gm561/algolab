#include <boost/config.hpp>
#include <iostream>                         // for std::cout
#include <utility>                          // for std::pair
#include <algorithm>                        // for std::for_each
#include <boost/utility.hpp>                // for boost::tie
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;

int main(int argc, char *argv[])
{
    typedef adjacency_list<vecS, vecS, bidirectionalS,
			   no_property, property<edge_weight_t, float> > Graph;

    enum {A,B,C,D,E,N};
    const int num_vertices = N;
    const char name[] = "ABCDE";

    typedef std::pair<int, int> Edge;

    Edge edge_array[] =
	{Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C), Edge(C,E), Edge(B,D), Edge(D,E), };

    const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

    float transmission_delay[] = { 1.2, 4.5, 2.6, 0.4, 5.2, 1.8, 3.3, 9.1 };

    Graph g(edge_array, edge_array + num_edges, transmission_delay, num_vertices);

    property_map<Graph, vertex_index_t>::type
	vertex_id = get(vertex_index,g);

    property_map<Graph, edge_weight_t>::type
	trans_delay = get(edge_weight, g);

    std::cout<<"vertices(g) = ";

    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;

    for(vp = vertices(g); vp.first != vp.second; ++vp.first)
	std::cout<<name[get(vertex_id, *vp.first)] << " ";
    std::cout<<std::endl;

    graph_traits<Graph>::edge_iterator ei, ei_end;
    for(boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
	std::cout<<"(" <<name[get(vertex_id, source(*ei,g))]
              << "," << name[get(vertex_id, target(*ei, g))] << ") ";
    }

    graph_traits<Graph>::outgoing_edge_iterator oei, oei_end;
    vp = vertices(g);
    tie(oei,oei_end) = out_edges(*vp.first, g);
    for_each(oei, oei_end, std::cout<<name[get(vertex_id, source(*oei,g))];
    std::cout<<std::endl;

    // typedef adjacency_list<listS, vecS, directedS, property<vertex_name_t, string>,
    // 			   property<edge_weight_t, int> > Graph;

    // Traits::vertex_iterator vert_it, vert_end;
    // Traits::edge_iterator edge_it, edge_end;

    // for(tie(vert_i, vert_end) = verticies(g); vert_itt != vert_end; ++vert_it)
    // 	for(tie(edige_it, edge_end) = out_edges(*vert_it g); edge_it != edge_end; ++edge_it)


    return 0;
}
