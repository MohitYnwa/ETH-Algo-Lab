#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;




struct point
{
	int x,y;
};

class moves
{
	public:
		int x,y,vx,vy,hop;	
		moves(int x1,int y1,int vx1, int vy1,int hop1)	
		{
			x=x1;
			y=y1;
			vx=vx1;
			vy=vy1;
			hop = hop1;
		}
};

int BFS(moves start,moves end,vector<vector<int> > graph,int M,int N);
void Initialize( int M, int N,vector<vector<int> > graph);
void print(vector<vector<int> > graph, int M, int N);
void setBarriers(vector<vector<int> > &graph, int x1, int y1, int x2, int y2);

int main()
{
	int n;
	cin>>n;
	
	for (int i=0;i<n;i++)
	{
		int M,N,P;
		cin>>M>>N;
		
		vector<vector<int> > graph(M, vector<int> (N));
		//Initialize(M,N,graph);
		//print(graph,M,N);
		int start_x,start_y,stop_x,stop_y;
		
		cin>>start_x>>start_y>>stop_x>>stop_y;
		
		moves start =  moves(start_x,start_y,0,0,0);
		moves stop =  moves(stop_x,stop_y,0,0,0);
		
		cin>>P;
		
		for (int j=0;j<P;j++)
		{
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			setBarriers(graph,x1,y1,x2,y2);
		}
		
		//print(graph,M,N);
		int hops = BFS(start,stop, graph,M,N);
		
		if (hops == -1) cout<<"No solution."<<endl;
		else cout<<"Optimal solution takes "<<hops<<" hops."<<endl;
	}
}

int BFS(moves start,moves end,vector<vector<int> > graph,int M,int N)
{
	queue<moves> q;
	int visited[M][N][7][7];
	for(int i=0;i<M;i++)
		for (int j=0;j<N;j++)
			for (int k=0;k<7;k++)
				for (int l=0;l<7;l++)
					visited[i][j][k][l]=0;
	
	q.push(start);
	
	//int depth = 0;
	while (!q.empty())
	{
		moves current = q.front();
		if ( current.x == end.x && current.y==end.y) return current.hop;
		//cout<<visited[current.x][current.y][current.vx + 3][current.vy + 3]<<endl;
	 	if (visited[current.x][current.y][current.vx + 3][current.vy + 3] == 0)
	 	{

			for (int i=-1;i<=1;i++)
			{
				for(int j=-1;j<=1;j++)
				{
					int vx_new = abs(current.vx + i) > 3 ? current.vx : current.vx + i;
					int vy_new = abs(current.vy + j) > 3 ? current.vy : current.vy + j;			
					
					int x_new = current.x + vx_new;
					int y_new = current.y + vy_new;
					
						if (!(x_new<0 || x_new >=M || y_new<0 || y_new>=N || graph[x_new][y_new]==-1 || (x_new == current.x && y_new == current.y)))
						{
							q.push(moves(x_new,y_new,vx_new,vy_new,current.hop + 1));					
						}
					
				}
			}
		}
		
		visited[current.x][current.y][current.vx + 3][current.vy + 3] = 1;
		q.pop();
	}
	
	return -1;
}

void Initialize( int M, int N,vector<vector<int> > graph)
{
	for (int i=0;i<M;i++)
		for (int j=0;j<N;j++)
			graph[i][j]= 0;
}

void setBarriers(vector<vector<int> > &graph, int x1, int y1, int x2, int y2)
{
	for (int i=x1;i<=x2;i++)
		for (int j=y1;j<=y2;j++)
			graph[i][j] = -1;
}

void print(vector<vector<int> > graph,int M,int N)
{
	for (int i=0;i<M;i++)
	{
		for (int j=0;j<N;j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
}
