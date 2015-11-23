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
	int n,m,s;
	cin>>n>>m>>s;

	Graph G(n+1);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	
	map<int,int> count;
	EdgeAdder edgeAdder(G, capacity, rev_edge);
	for (int i=0;i<s;i++)
	{
		int sh;
		cin>>sh;
		count[sh]++;
	}

//	int sum=0;
	for (std::map<int,int>::iterator iter=count.begin();iter!=count.end();iter++)
	{
	//	cout<<iter->first<<" "<<n<<" "<<iter->second<<endl;
		edgeAdder.addEdge(iter->first,n,iter->second);
		//sum+=iter->second;
	}

	for (int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		//cout<<a<<" "<<b<<endl;
		edgeAdder.addEdge(a,b,1);
		edgeAdder.addEdge(b,a,1);
	}

	long flow = push_relabel_max_flow(G, 0, n);
//	cout<<flow<<" "<<s<<endl;
	if (flow != s) cout<<"no"<<endl;
	else cout<<"yes"<<endl;	
    }
  return 0;
}

