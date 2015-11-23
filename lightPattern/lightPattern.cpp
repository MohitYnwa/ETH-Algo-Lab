#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int solve(int x,int y)
{
  unsigned int z=x^y;
  int cnt=0;
  
  //  cout<<x<<" "<<" "<<y<<" "<<z<<endl;
 while (z)
    {
      int l =1 & z;
           //      cout<<l<<endl;
      if (l == 1) cnt++;
      z>>=1;
      //      cout<<"z "<<z<<endl;
    }
 //  cout<<cnt<<endl;
  return cnt;
}


int main()
{
  int t;
  cin>>t;
  while(t--)
    {
      int n,k,x;
      cin>>n>>k>>x;

      int p = n/k;
      vector <int> FC(p+1,0), C(p+1, 0), FF(p+1,0);

      for (int i=0;i<p;i++)
	{
	  int y=0;
	  for(int j=k-1;j>=0;j--)
	    {
	      int bit;
	      cin>>bit;
	      int z = bit<<j;
	      y |= bit<<j;
	    }
	  int cbits = solve(x,y);
	  C[i+1] = cbits;
	  FC[i+1] = k - cbits;
	  //	  FF[i+1] = cbits == 0 ? 2 : 1;
	  //	  cout<<"Y "<<y<<endl;
	  //	  cout<<cbits<<endl;
	}

      for (int i=p-1;i>0;i--)
	{
	  C[i] = C[i] + C[i+1];
	}

      for (int i=1;i<=p;i++)
	{
	  FC[i]= FC[i] + FC[i-1];
	}
	  
      int mina = std::min(FC[p] + 1, C[1]);
      int minb = std::min(FF[p], C[1]);
      for (int i=1;i<p;i++)
	{
	  mina = std::min(mina,FC[i] + 1 + C[i+1]);
	  minb = std::min(minb, FF[i] + C[i+1]);
	}

      cout<<mina<<" "<<minb<<endl;
      cout<<std::min(mina,minb)<<endl;
    }
}

