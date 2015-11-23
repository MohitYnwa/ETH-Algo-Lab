#include<iostream>
#include <algorithm>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::Triangle_2 Triangle;
typedef K::Segment_2 Segment;
using namespace std;

void swap(Point &p1, Point &p2)
{
  Point temp =p2;
  p2 = p1;
  p1= p2;
}
int main()
{
  int t;
  cin>>t;
  while(t--)
    {

      //      cout<<"Loop Starts"<<endl;
      int m,n;
      cin>>m>>n;

      vector<Point> hike(m);
      for (int i=0;i<m;i++)
	{
	  int x,y;
	  cin>>x>>y;
	  hike[i] = Point(x,y);
	}


      vector< vector<int> > tr_n(n, vector<int>());
      for (int i=0;i<n;i++)
	{
	  int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6;
	  cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4>>x5>>y5>>x6>>y6;

	  vector<Point> p(6);
	  p[0]=Point(x1,y1), p[1] = Point(x2,y2), p[2] = Point(x3,y3);
	  p[3]=Point(x4,y4), p[4] = Point(x5,y5), p[5] = Point(x6,y6);

	  for (int j=0;j<3;j++)
	    {
	      if (CGAL::right_turn(p[2*j],p[2*j+1],p[2*((j+1)%3)]) && CGAL::right_turn(p[2*j],p[2*j+1],p[2*((j+1)%3) + 1]))
		{
		  Point temp = p[2*j];
		  p[2*j] = p[2*j+1];
		  p[2*j+1] = temp;
		}
	    }
	  
	  for (int j=0;j<m-1;j++)
	    {
	      if (!CGAL::right_turn(p[0],p[1],hike[j]) && !CGAL::right_turn(p[2],p[3],hike[j]) && !CGAL::right_turn(p[4],p[5],hike[j]))
		if (!CGAL::right_turn(p[0],p[1],hike[j+1]) && !CGAL::right_turn(p[2],p[3],hike[j+1]) && !CGAL::right_turn(p[4],p[5],hike[j+1]))
		  tr_n[i].push_back(j);
	    }
	}

      ///      cout<<tr_n[0].size()<<endl;
      //      cout<<"Hey"<<endl;
      int count = 0;
      int i=0,j=0;
      int min = n;
      vector<int> sc(m-1,0);
      while(i<n)
	{
	  //	  cs.clear();
	  while (count != m-1 && i<n)
	    {
	      for (int k=0;k<tr_n[i].size();k++)
		{
		  if (sc[tr_n[i][k]] == 0) count++;
		  sc[tr_n[i][k]]++;
		}
	      i++;
	    }
	  while (count == m-1 && j<i )
	    {
	      for (int k=0;k<tr_n[j].size();k++)
		{
		  if (sc[tr_n[j][k]] == 1) count--;
		  sc[tr_n[j][k]]--;
		}
	      j++;
	    }
	  if ( i - j < min  ) // imples minimal set;
	    {
	      min = i - j;
	    }	  
	}

      cout<<min+1<<endl;
    }
  
}
