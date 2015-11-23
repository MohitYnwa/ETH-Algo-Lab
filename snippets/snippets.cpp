#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <boost/graph/adjacency_list.hpp>
using namespace std;

struct words
{
  int pos;
  int word;
  words(int p,int n)
  {
    pos = p;
    word = n;
  }
  words() {};
};

bool compare(words w1,words w2)
{
  return w1.pos < w2.pos;
}

int main()
{
  int n;
  cin>>n;

  for (int i=0;i<n;i++)
    {
      int w;
      cin>>w;
      vector<int> word_c(w);

      for (int j=0;j<w;j++)
	{
	  cin>>word_c[j];
	}

      vector<words> word_pos;
      vector<int> current_pos(w,-1);
      int min=-1,max=-1; //can be error  prone
      for (int j=0;j<w;j++)
	{
	  for (int k=0;k<word_c[j];k++)
	    {
	      int p;
	      cin>>p;
	      min = min == -1 ? p : std::min(p,min);
	      max = k==0 ? std::max(p,max) : max;
	      word_pos.push_back(words(p,j));
	    }
	}

      //      cout<<min<<" "<<max<<endl;

      sort(word_pos.begin(),word_pos.end(),compare);
      //      cout<<word_pos.size()<<endl;

      deque<words> q;
      int min_dist = max - min + 1;
      int no = 0;
      for (int j=0;j<word_pos.size();j++)
	{
	  words current = word_pos[j];

	  if (current_pos[current.word] == -1 )
	    {
	      no++;
    
	    }
	  
	  
	      q.push_back(current);
	      current_pos[current.word] = current.pos;
	      while ( !(q.front().pos == current_pos[q.front().word] ))
		{
		  q.pop_front();
		}
		
	  

	  if (no == w)
	    {
	      int dist = q.back().pos - q.front().pos + 1;
	      min_dist = std::min(dist,min_dist);
	    }
	}

      cout<<min_dist<<endl;
      //      cout<<q.back().pos<<" "<<q.front().pos<<endl;
      //      cout<<q.back().pos-q.front().pos +1<<endl;
      
    }
}
