#include <iostream>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	int res[n];
	for(int i=0;i<n;i++)
	{
		int k;
		cin>>k;
		int prev=1;
		int j=0,max=1,sum=1;
		int val[k];
		for (j=0;j<k;j++)
		{
			cin>>val[j];
		}
		
		max=val[0];
		sum=val[0];
		for (j=0;j<sum && j<k;j++)
		{
			if ( val[j] >= max & val[j] != 1)
			{
				int diff = val[j]- max;
				max = val[j];
				sum+=diff;
			}
			max--;
		}
		res[i]= k < sum ? k : sum;
	}
	
	for (int i=0;i<n;i++)
	{
		cout<<res[i]<<endl;
	}
}
