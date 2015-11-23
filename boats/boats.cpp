#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boat
{
	int min_end;
	int max_end;
	
	boat(int l,int r)
	{
		min_end = l;
		max_end = r;
	}
	
	boat() {
	}
};

int boatCount(vector<boat> boats);

bool boatcompare(struct boat lhs, struct boat rhs)
{
	return lhs.min_end < rhs.min_end;
}

void print(vector<boat> boats)
{
	for(int i=0;i<boats.size();i++)	
	{
		cout<<boats[i].min_end<<" "<<boats[i].max_end<<endl;
	}
}

int main()
{
	int n;
	cin>>n;
	int res[n];
	
	for (int i=0;i<n;i++)
	{
		int wiz;
		cin>>wiz;
		
		vector<boat> boats(wiz);

		for (int j=0;j<wiz;j++)
		{
			int wt,pos;
			cin>>wt>>pos;
			boats[j] = boat(pos, pos +wt);
		}
		//print(boats);
		sort(boats.begin(),boats.end(),boatcompare);
		
		int count = boatCount(boats);
		
		res[i]=count;
	}
	
	for (int i=0;i<n;i++)
	{
		cout<<res[i]<<endl;
	}
}

int max(int a,int b)
{
	return a > b ? a : b;
}
int boatCount(vector<boat> boats)
{
	print(boats);
	int N=boats.size();
	int ctr = 1;
	boat last=boats[0];
	int current_end = boats[0].min_end;
	int i = 1;
	while (i!=N)
	{
		
		boat min_choice =boats[i]; 
		int min_index = i;
		int min_end = max ( boats[i].min_end, current_end + boats[i].max_end - boats[i].min_end);
		
		i++;
		while (i<N && boats[i].min_end < min_choice.max_end)
		{
			if (max( current_end +  boats[i].max_end - boats[i].min_end, boats[i].min_end) < min_end )
			{
				min_index = i;
				min_choice= boats[i];
				min_end= max( current_end +  boats[i].max_end - boats[i].min_end, boats[i].min_end);
			}
			i++;	
		}
		
	
		current_end=min_end;
		i=min_index+1;
		
		cout<<"Debug"<<endl;
		cout<<i<<endl;
		cout<<min_end<<endl;
		cout<<boats[min_index].min_end<<" "<<boats[min_index].max_end<<endl;
		cout<<"Debug End"<<endl;
		ctr++; //can be wrong
	}
	
	return ctr;
}
