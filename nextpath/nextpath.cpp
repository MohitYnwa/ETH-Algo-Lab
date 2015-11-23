#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct nd
{
	int node;
	int len;
	nd() {
	}
	nd(int a,int b) 
	{
		node=a;
		len=b;
	}
};

int BFS(vector<vector<int> > graph,int s,int t,int v)
{
	vector<int> length(v+1);
	
	for (int i=0;i<v+1;i++)
	{
		length[i]=0;
	}
	queue<nd> q;
	q.push(nd(s,0));
	

	int first_min = -1;
	while (!q.empty())
	{
		nd node = q.front();
		//cout<<"queue "<<node.node<<endl;
		if ((node.node == t)	&& length[t]==1) return node.len;
		if (length[node.node] < 2 )
		{
			//cout<<"Expanding "<<node.node<<" currentnode"<<node.len<<" visited"<<length[node.node]<<endl;
			
			//visited[node.node] +=1;//Expanding
			for (int j=0;j<graph[node.node].size();j++)
			{
				int i = graph[node.node][j];
				q.push(nd(i,node.len+1));
			}
		}
		
		q.pop();
		length[node.node]++;
	}
	return -1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	
	for (int i=0;i<n;i++)
	{
		int v,e;
		cin>>v>>e;
		
		int s,t;
		cin>>s>>t;
		
		vector<vector<int> > graph(v+1,vector<int> ());
		
		
		for (int j=0;j<e;j++)
		{
			int src,tgt;
			cin>>src>>tgt;
			graph[src].push_back(tgt);
		}
		
		int len = BFS(graph, s,t,v);
		
		if (len == -1 ) cout<<"no"<<endl;
		else cout<<len<<endl;
		
		
	}
	
}
