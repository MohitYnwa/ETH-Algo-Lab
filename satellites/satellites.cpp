#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <climits>
#include <queue>

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
	EdgeWeightMap &weight;
};

int main()
{
  int t;
  cin>>t;
  while (t--)
    {
	int g,s,l;
	cin>>g>>s>>l;
	Graph G(g+s+2);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	EdgeWeightMap weight = get(edge_weight,G);
	
	int source = g + s;
	int sink = source+1;
	EdgeAdder edgeAdder(G, capacity, weight, rev_edge);

	for (int i=0;i<l;i++)
	{
		int u,v;
		cin>>u>>v;
		edgeAdder.addEdge(u,g+v,1);
	}

	for (int i=0;i<g;i++)
		edgeAdder.addEdge(source,i,1);
	
	for (int i=0;i<s;i++)
		edgeAdder.addEdge(i+g,sink,1);	

	ResidualCapacityMap rcMap = get(edge_residual_capacity,G);
	long flow = push_relabel_max_flow(G,source,sink);
	std::queue<int> q;
	q.push(source);
	vector<bool> visited(g+s+2,false);

	int n = g+s+2;
	int Gf[n][n];
	for (int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			Gf[i][j] = 0;

	Vertex_it v_i, v_end;
	OutEdge_it e_i, e_end;
	for (tie(v_i,v_end) = vertices(G); v_i!=v_end; ++v_i)
		for( tie(e_i,e_end) = out_edges(*v_i,G); e_i != e_end; ++e_i)
		{
			if (rcMap[*e_i] > 0)
				Gf[*v_i][ target(*e_i, G)] = 1;
			Edge rev = edgeAdder.rev_edge[*e_i];
			if (rcMap[rev] > 0)
			{// cout<<"H:"<<endl;
				Gf[target( *e_i, G)] [*v_i] =1;
			}
		}

	while(!q.empty())
	{
		int vertex = q.front();
		q.pop();
		visited[vertex] = true;

		for (int i=0;i<n;i++)
		{
			if (Gf[vertex][i] == 1 && visited[i] == false)
			{
				q.push(i);
			}	
		}	
	}

	int cnt=0;
	for (int i=0;i<g;i++)
		if (!visited[i]) cnt++;

	cout<<cnt<<" ";
	
	cnt =0;
	for (int i=g;i<g+s;i++)
		if (visited[i]) cnt++;
	
	cout<<cnt<<endl;

	for (int i=0;i<g;i++)
		if (!visited[i]) cout<<i<<" ";

	for (int i=g;i<g+s;i++)
		if (visited[i]) cout<<i-g<<" ";

	cout<<endl;
	
	
//	cout<<flow<<" "<<s<<endl;
    }
  return 0;
}

