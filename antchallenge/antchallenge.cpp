#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS,
		       no_property,
		       property <edge_weight_t,int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

typedef property_map<Graph,edge_weight_t>::type WeightMap;

int main()
{
  int n;
  cin>>n;
  while(n--)
    {
      int v ,e ,no_t, src, tgt;
      cin>>v>>e>>no_t>>src>>tgt;
      Graph G[no_t];
      for (int i=0;i<no_t;i++)
	{
	  G[i] = Graph(v);
	}
      
      WeightMap wm[no_t];
      for (int i=0;i<no_t;i++)
	{
	  wm[i] = get(edge_weight, G[i]);
	}

      //      cout<<"Mohit1"<<endl;
      
      for (int i=0;i<e;i++)
	{
	  int a,b;
	  cin>>a>>b;

	  for (int j=0;j<no_t;j++)
	    {
	      Edge e;
	      tie(e, tuples::ignore) = add_edge(a,b,G[j]);
	      int wt;
	      cin>>wt;
	      wm[j][e] = wt;
	      //	      cout<<wm[j][e]<<endl;
	    }
	}

      //            cout<<"Mohit"<<endl;

      int hives[no_t];
      for (int j=0;j<no_t;j++)
	{
	  cin>>hives[j];
	}

      Graph min_G(v);
      WeightMap min_wm = get(edge_weight,min_G);
      for (int i=0;i<no_t;i++)
	{
	  vector<Edge> mst;
          kruskal_minimum_spanning_tree(G[i],std::back_inserter(mst));
	  WeightMap wmt = get(edge_weight, G[i]);
	  for (int j=0;j<v-1;j++)
	    {
	      Edge e;
	      bool a =false;
	      tie(e, a)= add_edge(source(mst[j],G[i]),target(mst[j],G[i]),min_G);
	      //  	      cout<<mst[j]<<endl;
	      min_wm[e] = wm[i][mst[j]];
	      //	      cout<<"Abc"<<endl;
	    }
	  //  cout<<"Done"<<endl;
	}


      //Run Dijkstra on the min graph to get min distance
      vector<int> dist(v);
      dijkstra_shortest_paths(min_G, src,
			     distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, min_G))));
			     
      cout<<dist[tgt]<<endl;
    }
  return 0;
}

		       
