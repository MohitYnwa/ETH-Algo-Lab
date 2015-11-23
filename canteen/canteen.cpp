#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <climits>
#include <queue>
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
typedef graph_traits<Graph>::vertex_iterator Vertex_it;
typedef graph_traits<Graph>::out_edge_iterator OutEdge_it;

struct EdgeAdder {
	EdgeAdder(Graph &G, EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge) : G(G), capacity(capacity), weight(weight), rev_edge(rev_edge) {}

void addEdge(int u,int v, long c,long w) {
	Edge e,rev;
	tie(e, tuples::ignore) = add_edge(u,v,G);
	tie(rev, tuples::ignore) = add_edge(v,u,G);
	capacity[e] = c;
	capacity[rev] = 0;
	rev_edge[e] = rev;
	rev_edge[rev] = e;
	weight[e] = w;
	weight[rev] = -w;
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
	int n;
	cin>>n;
	int nodes = n ; //n menus n -1freezers
	int source = nodes;
	int sink = nodes+1;
	Graph G(nodes+2);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	EdgeWeightMap weight = get(edge_weight,G);
	//ResidualCapacityMap res_capacity = get(edge_residual_capacity,G);
	
	EdgeAdder edgeAdder(G, capacity, weight, rev_edge);
	int cnt=0;
	int delta = 20;

	for (int i=0;i<n;i++)
	{
		int a,c;
		cin>>a>>c;
		edgeAdder.addEdge(source,i,a,c);
	}

	vector<int> wts;
	for (int i=0;i<n;i++)
	{
		int s,p;
		cin>>s>>p;
		cnt+=s;
		edgeAdder.addEdge(i,sink,s,-p+20);
		wts.push_back(p);
	}

	for (int i=0;i<n-1;i++)
	{
		int v,e;
		cin>>v>>e;
		edgeAdder.addEdge(i,i+1,v,e);
//		edgeAdder.addEdge(n+i,i+1,v,0);
	}


	ResidualCapacityMap res_capacity = get(edge_residual_capacity,G);
	successive_shortest_path_nonnegative_weights(G,source,sink);
	int cost = find_flow_cost(G);
	
	OutEdge_it e_i,e_end;
	int flow = 0;
	for ( tie(e_i,e_end) = out_edges(source, G); e_i != e_end; ++e_i)
		flow += capacity[*e_i] - res_capacity[*e_i];

	cost = cost - flow*delta;
/*
	int flow = push_relabel_max_flow(G,source,sink);
	cycle_canceling(G);
	int cost = find_flow_cost(G);
*/
//	cost = -(cost - profit);
	if (flow == cnt) cout<<"possible ";
	else cout<<"impossible ";
	cout<<flow<<" "<<-cost<<endl;
//	cout<<flow<<" "<<s<<endl;
    }
  return 0;
}

