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
	int n,m;
	cin>>n>>m;;
	Graph G(n);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	EdgeWeightMap weight = get(edge_weight,G);
	
	EdgeAdder edgeAdder(G, capacity, weight, rev_edge);

	for (int i=0;i<m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		edgeAdder.addEdge(u,v,c,0);
	}


	int min_cost = INT_MAX;
	int min_source,min_sink;

	//Only interested in the cut. Choose minimum cost wrt to a fixed vertex 0
	for (int i=1;i<n;i++)
	{
		int source = 0;
		int sink = i;
		int cost = push_relabel_max_flow(G,source,sink);

		if ( cost<min_cost ) {
			min_cost = cost;
			min_source = source;
			min_sink = sink;	
		} 
		
		source =i;
		sink = 0;
		cost = push_relabel_max_flow(G,source,sink);
		if (cost < min_cost) {
			min_cost = cost;
			min_source = source;
			min_sink = sink;
		}
	}

	ResidualCapacityMap rcMap = get(edge_residual_capacity,G);
	push_relabel_max_flow(G,min_source,min_sink);
	OutEdge_it e_i, e_end;

	
	std::queue<int> q;
	q.push(min_source);
	vector<bool> visited(n,false);
	
	while(!q.empty())
	{
		int vertex = q.front();
		q.pop();
		visited[vertex] = true;
		
		for (tie(e_i,e_end) = out_edges(vertex, G); e_i != e_end; ++e_i)
		{
			int tgt = target(*e_i, G);
			if ( rcMap[*e_i] > 0 && visited[tgt] == false) 
				q.push(tgt);
		}
	}

	int cnt = 0;
	for (int i=0;i<n;i++)
		if (visited[i]) cnt++;

	cout<<min_cost<<endl;
	cout<<cnt<<" ";


	for (int i=0;i<n;i++)
		if (visited[i]) cout<<i<<" ";

	cout<<endl;
	
//	cout<<flow<<" "<<s<<endl;
    }
  return 0;
}

