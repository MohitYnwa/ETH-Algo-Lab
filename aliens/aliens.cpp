#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct range
{
	int l;
	int r;
	range(int l1,int r1)
	{
		l=l1;
		r=r1;
	}
	range() {}	
};

int min(int a,int b)
{
	if ( b ==0 ) return a;
	if ( a==0 ) return b;
	return a < b ? a: b;
}

int max(int a,int b)
{
	return a > b ? a : b;
}

bool issuperiorTo(int j, int k , vector<range> &graph)
{
	if (graph[j].l==graph[k].l && graph[j].r == graph[k].r) return false;
	/*
	if (j==k) return true;
	
	if (graph[j].l==0 && graph[j].r==0)
		return false;
	
	if (!(graph[j].l >= graph[k].l && graph[j].r <= graph[k].r))
	{
		return true;
	}
	*/
	return true;
}

bool compare(range r1,range r2)
{
	if (r1.r == 0 && r1.l == 0) return false;
	if (r2.r == 0 && r2.l == 0) return true;
	if (r1.l == r2.l ) return r1.r > r2.r;
	return r1.l < r2.l;
//	if (r1.r - r1.l == r2.r - r2.l) return r1.l >= r2.l;
	//if (r1.r - r1.l == r2.r - r2.l) return r1.l < r2.l;
//	return r1.r-r1.l > r2.r - r2.l;
}

void print(vector<range> graph)
{
	for (int i=0;i<graph.size();i++)
		cout<<graph[i].l<<" "<<graph[i].r<<endl;	
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	int res[n];
	for (int i=0;i<n;i++)
	{
		int count=0;
		int A,H;
		cin>>A>>H;
			
		vector<range> graph(A);
		
		for (int j=0;j<A;j++)
		{
			int p,q;
			cin>>p>>q;
			graph[j] = range(p,q);
		}
				
		sort(graph.begin(),graph.end(),compare);
		//print(graph);
		int superiorTo[A];
		for (int j=0;j<A;j++) superiorTo[j]=0;

		int rMax=0;
		
		for (int j=0;j<A;j++)
		{	
			rMax= max(rMax, graph[j].r);
				
			if (graph[j].l==0 && graph[j].r==0) continue;
			if (graph[j].r <= rMax) continue;
			if (j+1<A) 
				if (!issuperiorTo(j,j+1,graph)) continue;//Wont be superior in case of complete overlap
				
		//if (graph[j].l < lMax  || graph[j].r > rMax)
			superiorTo[j]=1;
		}
		
		if (graph[0].l == 1 && rMax == H)
		{
			for (int j=0;j<A;j++)
			{
				if(superiorTo[j]==1) count++;
			}
		}
		res[i]= count;
	}
	
	for(int i=0;i<n;i++)
	{
		cout<<res[i]<<endl;
	}
}
