#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS,
		      no_property,
		      property<edge_weight_t,int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator EdgeIt;

struct bridges
{
  int u,v;
};

bool cmp(bridges a, bridges b)
{
  if (a.u == b.u) return a.v < b.v;
  return a.u < b.u;
}
  void Bridge(int u, vector<bool> &visited, vector<int> &low, vector<int> &parent, vector<int> &disc, int time, Graph &G,vector<bridges> &results)
{
  int n=visited.size();

  low[u]=disc[u]= ++time;
  visited[u] = true;


  EdgeIt ebeg,eend;
  tie(ebeg,eend) = out_edges(u,G);
  
  for(;ebeg!=eend;ebeg++)
    {
      int v=target(*ebeg,G);
      if (!visited[v])
	{
	  parent[v]=u;
	  Bridge(v,visited,low,parent,disc,time,G,results);

	  low[u] = std::min(low[u],low[v]);
	  if (low[v] > disc[u])
	    {
	      bridges b;
	      b.u = std::min(u+1,v+1);
	      b.v = std::max(u+1,v+1);
	      results.push_back(b);
	    }
	}
      else if (parent[u]!=v)
	{
	  low[u] = std::min( low[u] , disc[v]);
	}
    }
}

int main()
{
  int t;
  cin>>t;
  for(int k=0;k<t;k++)
    {
      int n,m;
      cin>>n>>m;
      Graph G(n);
      for (int i=0;i<m;i++)
	{
	  Edge e;
	  int a,b;
	  cin>>a>>b;
	  tie(e, tuples::ignore) = add_edge(a-1,b-1,G);
	  //	  tie(e, tuples::ignore) = add_edge(b-1,a-1,G);
	}

      vector<int> parent(n,-1), low(n),disc(n);
      vector<bridges> results;
      int time = 0;
      vector<bool> visited(n,false);
      
      if (n>0) Bridge(0,visited,low,parent,disc,time,G,results);
      sort(results.begin(),results.end(),cmp);
      cout<<results.size()<<endl;
      for (int i=0;i<results.size();i++)
	{
	  cout<<results[i].u<<" "<<results[i].v<<endl;
	}
    }
}


