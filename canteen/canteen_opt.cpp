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
	Graph G1(nodes+2);
	Graph G2(nodes+2);
	EdgeCapacityMap capacity1 = get(edge_capacity, G1);
	ReverseEdgeMap rev_edge1 = get(edge_reverse, G1);
	EdgeWeightMap weight1 = get(edge_weight,G1);

	EdgeCapacityMap capacity2 = get(edge_capacity, G2);
	ReverseEdgeMap rev_edge2 = get(edge_reverse, G2);
	EdgeWeightMap weight2 = get(edge_weight, G2);
	//ResidualCapacityMap res_capacity = get(edge_residual_capacity,G);
	
	EdgeAdder edgeAdder1(G1, capacity1, weight1, rev_edge1);
	EdgeAdder edgeAdder2(G2, capacity2, weight2, rev_edge2);

	int cnt=0;

	for (int i=0;i<n;i++)
	{
		int a,c;
		cin>>a>>c;
		edgeAdder1.addEdge(source,i,a,+c);
		edgeAdder2.addEdge(source,i,a,0);
	}

	for (int i=0;i<n;i++)
	{
		int s,p;
		cin>>s>>p;
		cnt+=s;
		edgeAdder1.addEdge(i,sink,s,0);
		edgeAdder2.addEdge(i,sink,s,p);
	}

	for (int i=0;i<n-1;i++)
	{
		int v,e;
		cin>>v>>e;
		edgeAdder1.addEdge(i,i+1,v,+e);
		edgeAdder2.addEdge(i,i+1,v,0);
	}


	ResidualCapacityMap res_capacity1 = get(edge_residual_capacity,G1);
	successive_shortest_path_nonnegative_weights(G1,source,sink); //minimizes expense cost
	int expense = find_flow_cost(G1);

	successive_shortest_path_nonnegative_weights(G2, source,sink);
	int sales = find_flow_cost(G2); //minimizes sales cost
	
	//minimized losses = minimized expenses + maximized sales 
	int loss = expense - sales;
	int cost = -loss;

	OutEdge_it e_i,e_end;
	int flow = 0;
	for ( tie(e_i,e_end) = out_edges(source, G1); e_i != e_end; ++e_i)
		flow += capacity1[*e_i] - res_capacity1[*e_i];

//	cost = -(cost - profit);
	if (flow == cnt) cout<<"possible ";
	else cout<<"impossible ";
	cout<<flow<<" "<<cost<<" "<<cnt<<endl;
//	cout<<flow<<" "<<s<<endl;
    }
  return 0;
}

