#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
		       property<edge_residual_capacity_t, long,
				property<edge_reverse_t, Traits::edge_descriptor> > > >  Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

struct EdgeAdder {
	EdgeAdder(Graph &G, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge) : G(G), capacity(capacity), rev_edge(rev_edge) {}

void addEdge(int u,int v, long c) {
	Edge e,rev;
	tie(e, tuples::ignore) = add_edge(u,v,G);
	tie(rev, tuples::ignore) = add_edge(v,u,G);
	capacity[e] = c;
	capacity[rev] = 0;
	rev_edge[e] = rev;
	rev_edge[rev] = e;
}

	Graph &G;
	EdgeCapacityMap &capacity;
	ReverseEdgeMap &rev_edge;
};
int main()
{
  int t;
  cin>>t;
  while (t--)
    {
	int n,m;
	cin>>n>>m;

	int v = m + n + 2;
	Graph G(v);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	
	EdgeAdder edgeAdder(G, capacity, rev_edge);

	//source sink m n
	for (int i =0;i<m;i++) 
	{
		int a,b,c;
		cin>>a>>b>>c;
		if (c!=0)
//			edgeAdder.addEdge(0, c==1? i+2 + a : i+2+ b,1);
		{
			edgeAdder.addEdge(0,  2 + i, 1);
			edgeAdder.addEdge( 2+i, c==1? 2 + m + a : 2 + m + b, 1);
		}
		else 
		{
			edgeAdder.addEdge(0, 2 + i, 1);
			edgeAdder.addEdge( 2+i, 2+m+a, 1);
			edgeAdder.addEdge ( 2+i, 2+m+b, 1);
		}			
	}

	int sum = 0;
	for (int i=0;i<n;i++)
	{
		int sc;
		cin>>sc;
		sum+=sc;
		edgeAdder.addEdge( 2 + m + i, 1, sc);		
	}

	if (sum!=m) { cout<<"no"<<endl; continue; }
	long flow = push_relabel_max_flow(G, 0, 1);
	if (flow != sum) cout<<"no"<<endl;
	else cout<<"yes"<<endl;	
    }
  return 0;
}

