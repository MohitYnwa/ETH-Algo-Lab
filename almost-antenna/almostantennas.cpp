#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>
#include <vector>
#include<algorithm>


typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Min_circle_2_traits_2<EK> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef EK::Point_2 Point;


using namespace std;

long ceil_to_long(const EK::FT& x)
{
  long d = std::floor(CGAL::to_double(x));
  while (d>x) d--;
  while (d+1<=x) d++;
  return d==x ? d : d + 1.0L;
}
int main()
{
  cout<<setiosflags(ios::fixed)<<setprecision(0);
  int n;
  cin>>n;

  while(n!=0)
    {
      vector<EK::FT> mrv;
      Point P[n];
      for (int i=0;i<n;i++)
	{
	  long a,b;
	  cin>>a>>b;
	  P[i] = Point(a,b);
	}

      Min_circle mc(P,P+n,true);
      EK::FT radius;
      int cnt = mc.number_of_support_points();

      vector<int> support_points;
      for(CGAL::Min_circle_2<Traits>::Support_point_iterator it = mc.support_points_begin();it!=mc.support_points_end();it++)
	{
	  for (int i=0;i<n;i++)
	    {
	      if (P[i]==*it)
		{
		  support_points.push_back(i);
		}
	    }
	}

      for (int i=0;i<support_points.size();i++)
	{
	  vector<Point> temp(P, P + support_points[i]);
	  temp.insert(temp.end(),P+support_points[i]+1, P + n);
	  Min_circle mc_t(temp.begin(),temp.end(),true);
	  mrv.push_back(mc_t.circle().squared_radius());
	}
      
       radius = *min_element(mrv.begin(),mrv.end());
      EK::FT f = sqrt(radius);
      long r = ceil_to_long(f);
      //      cout<<dist.size()<<" points"<<endl;
      cout<<r<<endl;
      cin>>n;
    }
}
