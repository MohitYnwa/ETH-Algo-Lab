#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <climits>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
		       property<edge_residual_capacity_t, long,
				property<edge_reverse_t, Traits::edge_descriptor,
					property<edge_weight_t, long > > > > >  Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_weight_t>::type EdgeWeightMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::out_edge_iterator OutEdge_it;
struct EdgeAdder {
	EdgeAdder(Graph &G, EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge) : G(G), capacity(capacity), weight(weight), rev_edge(rev_edge) {}

void addEdge(int u,int v, long c,long w) {
	Edge e,rev;
	tie(e, tuples::ignore) = add_edge(u,v,G);
	tie(rev, tuples::ignore) = add_edge(v,u,G);
	capacity[e] = c;
	weight[e] = w;
	capacity[rev] = 0;
	weight[rev] = -w;
	rev_edge[e] = rev;
	rev_edge[rev] = e;
}

	Graph &G;
	EdgeCapacityMap &capacity;
	ReverseEdgeMap &rev_edge;
	EdgeWeightMap &weight;
};
int main()
{
  int t;
  cin>>t;
  while (t--)
    {
	int n,m,s;
	cin>>n>>m>>s;

	Graph G(n+m+2+s);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	EdgeWeightMap weight = get(edge_weight,G);
	
	int source = n+m+s;
	int sink = source+1;
	EdgeAdder edgeAdder(G, capacity, weight, rev_edge);
	for (int i=0;i<s;i++)
	{
		int l;
		cin>>l;
		edgeAdder.addEdge(n+m+i,sink,l,0);
		//edgeAdder.addEdge(x+n,y,1);
//		edgeAdder.addEdge(y,y+n,1);
	}

	for (int i=0;i<m;i++)
	{
		int st;
		cin>>st;
		edgeAdder.addEdge(n+i,n+m+st-1,1,0);
	}

	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			int bid;
			cin>>bid;
			edgeAdder.addEdge(i,n+j,1,-bid+100);
		}
	}

	for (int i=0;i<n;i++)
		edgeAdder.addEdge(source,i,1,0);

	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	successive_shortest_path_nonnegative_weights(G,source,sink);	
	int cost = find_flow_cost(G);

	int flow=0;
	OutEdge_it e_i,e_end;
	for (tie(e_i,e_end) = out_edges(source,G); e_i !=e_end; ++e_i)
		flow += capacity[*e_i] - res_capacity[*e_i];

	cost = cost- flow*100;
	cout<<flow<<" "<<-cost<<endl;
	
	
//	cout<<flow<<" "<<s<<endl;
    }
  return 0;
}

