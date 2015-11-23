#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;
typedef adjacency_list < vecS,vecS, undirectedS,
			 no_property,
			 property< edge_weight_t, int> > Graph;
typedef graph_traits <Graph> ::edge_descriptor Edge;
typedef graph_traits <Graph> ::vertex_descriptor Vertex;
typedef property_map<Graph,edge_weight_t>::type WeightMap;

int getSpanningTreeWeight(Graph G,WeightMap wm)
{
  vector<Edge> mst;
  kruskal_minimum_spanning_tree(G,std::back_inserter(mst));
  int wt=0;

  for (int i=0;i<mst.size();i++)
    {
      wt+=wm[mst[i]];
    }

  return wt;
}

int getFarthestNodeDistance(Graph G,WeightMap wm,int V)
{
  vector<int> D(V);
  vector<int> P(V);
  dijkstra_shortest_paths(G,0,
			  predecessor_map(make_iterator_property_map(P.begin(),get(vertex_index,G))).
			 distance_map(make_iterator_property_map(D.begin(),get(vertex_index,G))));

  return *max_element(D.begin(),D.end());
}

int main()
{
  int n;
  cin>>n;
  while (n--)
    {
      int ve,e;
      cin>>ve>>e;
      Graph G(ve);

      WeightMap wm = get(edge_weight, G);
      for(int i=0;i<e;i++)
	{
	  int u,v,c;
	  cin>>u>>v>>c;
	  Edge e;
	  tie(e, tuples::ignore) = add_edge(u,v,G);
	  wm[e] = c;
	}
      int weight = getSpanningTreeWeight(G,wm);
      int farthest = getFarthestNodeDistance(G,wm,ve);
      cout<<weight<<" "<<farthest<<endl;
    }
  return 0;
}
