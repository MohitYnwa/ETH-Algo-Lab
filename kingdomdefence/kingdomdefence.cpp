
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>

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
	int l,p;
	cin>>l>>p;

	Graph G(2*l + 2);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	
	int source = 2*l;
	int sink = source + 1;
	map<int,int> count;
	EdgeAdder edgeAdder(G, capacity, rev_edge);
	int sum=0;
	for (int i=0;i<l;i++)
	{
		int x,y;
		cin>>x>>y;
		
		edgeAdder.addEdge(source,i,x); //Max Flow
		edgeAdder.addEdge(i,sink,y);
		sum+=y;
//		edgeAdder.addEdge(y,y+n,1);
	}

	for (int i=0;i<p;i++)
	{
		int f,t,cmin, cmax;
		cin>>f>>t>>cmin>>cmax;
		edgeAdder.addEdge(f,f+l,cmax);
		edgeAdder.addEdge(f+l,sink,cmin);
		edgeAdder.addEdge(f+l,t,cmax-cmin);
		edgeAdder.addEdge(source,t,cmin);
		edgeAdder.addEdge(t,t+l,cmax);
		sum+=cmin;
	}

	int flow = push_relabel_max_flow(G,source, sink);
	
//	cout<<flow<<" "<<s<<endl;
	if (flow == sum) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
    }
  return 0;
}

