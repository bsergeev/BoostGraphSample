#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cuthill_mckee_ordering.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>

#include <vector>
#include <iostream>

/*
  Output:
original bandwidth: 8
Reverse Cuthill-McKee ordering:
  0 8 5 7 3 6 4 2 1 9 
  bandwidth: 4
*/
int main(int , char* [])
{
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
                                      boost::property<boost::vertex_color_t, boost::default_color_type, boost::property<boost::vertex_degree_t,int>>>;
  Graph G(10);
  add_edge(0,3, G);
  add_edge(0,5, G);
  add_edge(1,2, G);
  add_edge(1,4, G);
  add_edge(1,6, G);
  add_edge(1,9, G);
  add_edge(2,3, G);
  add_edge(2,4, G);
  add_edge(3,5, G);
  add_edge(3,8, G);
  add_edge(4,6, G);
  add_edge(5,6, G);
  add_edge(5,7, G);
  add_edge(6,7, G); 
  const size_t N = boost::num_vertices(G);
  std::cout << "original bandwidth: "<< boost::bandwidth(G) <<" (graph size: "<< N <<")" << std::endl;
 
  std::vector<size_t> step2NodeIdx(N);
  boost::cuthill_mckee_ordering(G, step2NodeIdx.rbegin(), boost::get(boost::vertex_color, G), boost::make_degree_map(G));
    
  std::cout << "Reverse Cuthill-McKee ordering:\n  ";    
  boost::property_map<Graph, boost::vertex_index_t>::type index_map = boost::get(boost::vertex_index, G);
  for (size_t i : step2NodeIdx) { 
    std::cout << index_map[i] << " "; 
  } std::cout << std::endl;

  std::vector<size_t> perm(N);
  for (size_t c = 0; c < step2NodeIdx.size(); ++c) { perm[index_map[step2NodeIdx[c]]] = c; }
  std::cout << "  bandwidth: " << boost::bandwidth(G, boost::make_iterator_property_map(&perm[0], index_map, perm[0])) << std::endl;
}
