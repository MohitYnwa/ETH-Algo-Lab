#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS,
		       no_property,
		       property<edge_weight_t,int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;

Graph buildGraph(vector<vector<string> > h, int f)
{
  int n=h.size();
  Graph G(n);
  
  for (int i=0;i<n;i++)
    {
      for (int j=i+1;j<n;j++)
	{
	    {
	      vector<string> c1 = h[i];
	      vector<string> c2 = h[j];
	      vector<string> temp(c1.size()*2);
	      
	      vector<string>::iterator it = set_intersection(c1.begin(),c1.end(),c2.begin(),c2.end(),temp.begin());
	      temp.resize(it -temp.begin());

	      if (temp.size() > f)
		{
		  Edge e;
		  tie(e,tuples::ignore) = add_edge(i,j,G);
		  //		  cout<<"Adding "<<e<<endl;
		}
	    }
	}
    }

  return G;
}

bool check(Graph G,int v)
{
  
  vector<Vertex> mate(v);
  edmonds_maximum_cardinality_matching(G,&mate[0]);

  Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();
  for (int i=0;i<v;i++)
    {
      if (mate[i] == NULL_VERTEX) return false;
    }
  return true;
  
}
  
int main()
{
  int t;
  cin>>t;
  while (t--)
    {
      int n,c,f;
      cin>>n>>c>>f;

      vector<vector<string> > h ( n, vector<string>(c));

      for (int i=0;i<n;i++)
	{
	  for (int j=0;j<c;j++)
	    {
	      cin>>h[i][j];
	    }
	  sort(h[i].begin(),h[i].end());
	}

      Graph G = buildGraph(h,f);
      bool isOptimal = check(G,n);

      if(isOptimal) cout<<"not optimal"<<endl;
      else cout<<"optimal"<<endl;
    }
}
