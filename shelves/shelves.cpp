#include <iostream>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	
	int arr[3*n];
	for ( int i=0;i<n;i++)
	{
		cin>>arr[3*i]>>arr[3*i+1]>>arr[3*i+2];
	}
	int res[n*3];
	
	for (int i=0;i<n;i++)
	{
		int t,s,l;
		t=arr[3*i];
		s=arr[3*i+1];
		l=arr[3*i+2];
		
		int tl = t/l;
		int best_l,best_s,best_r = t%l + 1;
		for ( int k=tl; k>tl-s && k>=0; k-- )
		{
			int r_1= t-k*l;
			int r_2 = r_1/s;
			int rem = r_1 - (r_2 * s);
			//cout<<rem<<endl;
			if (rem < best_r)
			{
				best_r = ( rem < best_r ) ? rem : best_r;
				best_l = k;
				best_s = r_2;
				
				if (rem == 0) break;
			}
		}
		
		cout<<best_s<<" "<<best_l<<" "<<best_r<<endl;
	}	
}
