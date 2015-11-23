#include <iostream>
#include <vector>

using namespace std;

class weighing {
	public:
	vector<int> wt_arr;
	char balance;
	int len;
	
	weighing(){	};
};
int main()
{
	std::ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	
	
	for (int i=0;i<n;i++)
	{
		int coins, weighings;
		cin>>coins;
		cin>>weighings;
		//0.undermined 1.small 2.equal 3. greater
		int arr[coins];
		for (int j=0;j<coins;j++)
		{
			arr[j]=0;
		}
		vector<weighing> wgs;
		
		for (int j=0;j<weighings;j++)
		{
			int wts;
			cin>>wts;
			vector<int> wt_arr;
			char balance;
			for (int k=0;k<wts*2;k++)
			{
				int val;
				cin>>val;
				wt_arr.push_back(val - 1);
			}
			
			cin>>balance;	
			
			if (balance=='=')
			{
				for (int k=0;k<wts*2;k++)
				{
					arr[wt_arr[k]]= 2; //implies equal wts
				}
			}
			else if (balance == '<')
			{
				weighing wg;
				wg.wt_arr= wt_arr;
				wg.balance=balance;
				wg.len = wts*2;
				
				wgs.push_back(wg);
				for (int k=0;k<wts;k++)
				{
					int index = wt_arr[k];
					if (arr[index]!=2)
					arr[index] = arr[index] - 1 == 2 ? 2 : 1; //small wts
				}
				
				for (int k=wts;k<2*wts;k++)
				{
					int index = wt_arr[k];
					if (arr[index]!=2)
					arr[index] = 3 - arr[index] == 2 ? 2 : 3;
				}
			}
			else if (balance == '>')
			{
				weighing wg;
				wg.wt_arr= wt_arr;
				wg.balance=balance;
				wg.len = wts*2;
				
				wgs.push_back(wg);
				for (int k=0;k<wts;k++)
				{
					int index = wt_arr[k];
					if (arr[index]!=2)					
					arr[index] = 3 - arr[index] == 2 ? 2 : 3; //small wts
				}
				
				for (int k=wts;k<2*wts;k++)
				{
					int index = wt_arr[k];
					if (arr[index]!=2)
					arr[index] = arr[index] - 1 == 2 ? 2 : 1;
				}
			}
	
	/*
			cout<<arr[0]<<endl;
			cout<<arr[1]<<endl;
			cout<<arr[2]<<endl;
			cout<<arr[3]<<endl;
			cout<<arr[4]<<endl;
			*/
		}
		
		//cout<<"Pringint "<<coins<<endl;
		vector<int> faulty;
		for (int j=0;j<coins;j++)
		{
			//cout<<arr[j]<<endl;
			if (arr[j] == 0 || arr[j] != 2)
			{
				//cout<<"Faulty : "<<j<<" "<<arr[j]<<endl;
				faulty.push_back(j);
			}
		}
		
		if ( faulty.size()  == 1 ) cout<<faulty[0] + 1<<endl;
		else
		{
			for (int i1=0;i1<faulty.size();i1++)
			{
				//cout<<"looping for "<<wgs.size()<<endl;
				for (int j=0;j<wgs.size();j++)
				{
					int sum=0;
					int containsFaulty = 0;
					//cout<<"loop"<<wgs[j].len<<endl;
					for(int k=0; k<wgs[j].len; k++)
					{
						sum += arr[wgs[j].wt_arr[k]];
						//cout<<"p"<<wgs[j].wt_arr[k]<<endl;
						//cout<<wgs[j].wt_arr[k]<<" "<<faulty[i1]<<endl;
						if (wgs[j].wt_arr[k]== faulty[i1]) 
						{
							//cout<<"here"<<endl;
							containsFaulty = 1;
							
						}
					}
					
			//		cout<<sum<<containsFaulty<<endl;
					if (containsFaulty == 1 && sum == 2*wgs[j].len + 1){ 
						cout<<faulty[i1] + 1<<endl;
						goto end;
					}
				}
				
			}
			
			int ctr=0;
			int val=-1;
			for (int j=0;j<coins;j++ )
			{
				if (arr[j] == 0) ctr++;
				val=j;
			}
			
			if (ctr == 1) 
			{
				cout<<val+1<<endl;
				goto end;
			}
			cout<<0<<endl;
			end:
				continue;
		}
	}
	
}
