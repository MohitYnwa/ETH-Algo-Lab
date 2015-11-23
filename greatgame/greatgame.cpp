#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int solve(vector< vector<int> > game, int s, int n)
{
  vector<int> solm(n, 0);
  vector<int> solx(n, 0);

  for (int i=n-1;i>=s;i--)
    {
      solm[i] = INT_MAX;
      solx[i] = -1;
      for (int j=0;j<game[i].size();j++)
	{
	  int k = game[i][j];
	  solx[i] = max( solx[i], 1 + solm[k]);
	  solm[i] = min( solm[i] ,1 + solx[k]);
	}
    }
  return solm[s];
}

int main()
{
  int t;
  cin>>t;
  while(t--)
    {
      int n,m;

      cin>>n>>m;
      int r,b;
      cin>>r>>b;

      vector<vector <int> > game (n+1,vector<int>());

      //    cout<<"1"<<endl;
      for (int i=0;i<m;i++)
	{
	  int u,v;
	  cin>>u>>v;
	  game[u].push_back(v);
	}

      int sh = solve(game,r,n);
      int mor = solve(game,b,n);

      //      cout<<sh<<" "<<mor<<endl;
      if ( sh%2 == 1 && sh==mor) cout<<0<<endl;//Sherlock wins
      else if ( sh%2 == 0 && sh==mor) cout<<1<<endl; //moriaty wins
      else if ( sh < mor) {cout<<0<<endl;} else{ cout<<1<<endl;}


    }
  
}
