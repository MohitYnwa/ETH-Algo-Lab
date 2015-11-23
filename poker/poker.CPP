#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int main()
{
  int t;
  cin>>t;
  while(t--)
    {
      int n;
      cin>>n;

      int MAX = 5;
      vector <int> dim(MAX,0);
      for (int i=0;i<n;i++)
	{
	  cin>>dim[i];
	  //  cout<<dim[i]<<endl;
	}

      for (int i=0;i<MAX;i++)
	{
	  dim[i] = dim[i] + 1;
	}

      //      cout<<"Hey0"<<endl;
      //      int TCs[850][608][2][2][2];
      //      cout<<n<<endl;
      int TC[dim[0]][dim[1]][dim[2]][dim[3]][dim[4]];
      //      cout<<"heyf"<<endl;
      for (int i=0;i<dim[0];i++)
	for (int j=0;j<dim[1];j++)
	  for (int k=0;k<dim[2];k++)
	    for (int l=0;l<dim[3];l++)
	      for (int m=0;m<dim[4];m++)
	    {
	      TC[i][j][k][l][m] = 0;
	    }
      //      cout<<"Hey"<<endl;

      vector < vector <int> > chips(MAX,vector<int>());

      for (int i=0;i<n;i++)
	{
	  for (int j=0;j<dim[i]-1;j++)
	    {
	      int c;
	      cin>>c;
	      chips[i].push_back(c);
	    }
	}

      for (int a=0;a<dim[0];a++)
	for (int b= 0;b<dim[1];b++)
	  for (int c= 0;c<dim[2];c++)
	    for (int d=0;d<dim[3];d++)
	      for (int e=0;e<dim[4];e++)
	  {
	    int current_top[MAX];
	    current_top[0] = a>0 ? chips[0][a-1] : -1;
	    current_top[1] = b > 0 ? chips[1][b-1] : -1;
	    current_top[2] = c > 0 && chips[2].size() > 0 ? chips[2][c-1] : -1;
	    current_top[3] = d > 0 && chips[3].size() > 0 ? chips[3][d-1] : -1;
	    current_top[4] = e > 0 && chips[4].size() > 0 ? chips[4][e-1] : -1;
	    
	    for (int i=1;i<pow(2,n);i++)
	      {
		vector<int> index(MAX,0);
		int nx=i;
		for (int j=0;j<n;j++)
		  {
		    index [j] = (nx>>j) & 1;
		  }

		bool valid=true;
		int val = -1;
		int no = 0;
		for (int j=0;j<n;j++)
		  {
		    if (index[j])
		      {
			if (val == -1) val = current_top[j];
			if (val != current_top[j]) valid = false;
			no++;
		      }
		  }

		int score = ( no == 1) ? 0 : pow(2,no - 2);
		if (valid && val!=-1)
		  {
		    if( (a-index[0] >= 0) && (b-index[1] >= 0) && ( c-index[2] >=0 ) && (d-index[3] >= 0) && (e-index[4] >=0))
		      TC[a][b][c][d][e] = std::max( TC[a][b][c][d][e] , score + TC[a-index[0]][b-index[1]][c-index[2]][d-index[3]][e-index[4]]);
		  }
	      }
	  }

      cout<<TC[dim[0]-1][dim[1]-1][dim[2]-1][dim[3]-1][dim[4]-1]<<endl;
    }
}
