#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unordered_set>
#include "../interfaces/graph.h"


Graph<int> generate_random_graph(int vertices, int edges) {

  typedef std::pair<int, int> Edge;
  srand(time(NULL));
  assert(edges <= vertices*(vertices-1));

  std::unordered_set<Edge, boost::hash<Edge>> used_edges;
  Graph<int> g;
  for(int i=0; i<vertices; i++) {
    g.add_vertex(i);
  }
  int g_vertices = 0;
  while(g_vertices < vertices) {
    int v1 = rand() % vertices;
    int v2 = rand() % vertices;
    int val = rand() % 512 - 216;
    if(used_edges.find({v1, v2}) == used_edges.end()) {
      g.add_edge(v1, v2);
      g.set_edge_property(v1, v2, val);
      used_edges.insert({v1, v2});
      g_vertices += 1;
    }
  }

  return g;
}
