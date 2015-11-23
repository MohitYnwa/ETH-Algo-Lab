#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,
		       undirectedS,
		       no_property,
		       property<edge_weight_t,int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

int main()
{
  int t;
  cin>>t;
  while(t--)
    {
      int n,m,k,u,v;
      cin>>n>>m>>k>>u>>v;

      Graph G((k+1)*n);
      vector<Edge> rivers;
      vector<int> rw;
      WeightMap wm = get(edge_weight, G);
      int cnt=0;
      for (int i=0;i<m;i++)
	{
	  int a,b,c,d;
	  cin>>a>>b>>c>>d;

	  for (int j=0;j<=k;j++)
	    {
	      Edge e;
	      int x=a + n*j;
	      int y=b + n*j;
	      //	      cout<<x<<" "<<y<<" "<<c<<endl;
	      tie(e,tuples::ignore) = add_edge(x,y,G);
	      wm[e] = c;
	      cnt++;
	    }

	  if (d==1)
	    {
	      
	      for (int j=1;j<=k;j++)
		{
		  int x0,y0,x1,y1;
		  x0=a + n*(j-1);
		  y0=b + n*(j-1);
		  x1=a + n*j;
		  y1=b + n*j;

		  //		  cout<<x0<<" "<<y1<<" "<<c<<endl;

		  Edge e1,e2;
		  tie(e1, tuples::ignore) = add_edge(x0,y1,G);
		  wm[e1]=c;

		  //		  cout<<x1<<" "<<y0<<" "<<endl;
		  tie(e2, tuples::ignore) = add_edge(x1,y0,G);
		  wm[e2]=c;
		  cnt+=2;
		}
	    }
	}

      //find source to all vertex shortest paths
      vector<int> distx((k+1)*n);
      vector<int> predx((k+1)*n);
      dijkstra_shortest_paths(G,u,predecessor_map(make_iterator_property_map(predx.begin(),get(vertex_index,G))).
			      distance_map(make_iterator_property_map(distx.begin(),get(vertex_index,G))));

      //find target to all vertex shortest paths
      /*
      vector<int> disty(n);
      vector<int> predy(n);
      dijkstra_shortest_paths(G,y,predecessor_map(make_iterator_property_map(predy.begin(),get(vertex_index,G))).
			      distance_map(make_iterator_property_map(disty.begin(),get(vertex_index,G))));

     
      
      int min =INT_MAX;
      for (int i=0;i<rivers.size();i++)
	{
	  Edge e=rivers[i];
	  int a=source(e,G);
	  int b=target(e,G);
	  //	  cout<<"a"<<distx[a] + rw[i] + disty[b]<<endl;
	  //	  cout<<"b"<<distx[a]+disty[a] + 2*rw[i]<<endl;
	  //	  cout<<"c"<<distx[b] + disty[b] + 2*rw[i]<<endl;
	  min = std::min (min, mini(x,a,b,y,distx,disty,rw[i],predx,predy));
	  //	  min = std::min (min, mini(x,a,b,x,distx,distx,rw[i],pred[a],pred[b]) + distx[y]);
	  //	  min = std::min (min, mini(y,a,b,y,disty,disty,rw[i],pred[a],pred[b]) + disty[x]);
	}
      */
      //      cout<<"viola"<<endl;
      int min = distx[v+k*n];
      cout<<min<<endl;
      //      cout<<distx[x]<<endl;
      //      cout<<distx[y]<<endl;
    }
}
