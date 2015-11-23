#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>


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
  int n;
  cin>>n;

  while(n!=0)
    {
      Point P[n];
      for (int i=0;i<n;i++)
	{
	  long x,y;
	  cin>>x>>y;
	  P[i] = Point(x,y);
	}

      Min_circle mc(P,P+n,true);
      Traits::Circle c = mc.circle();
      EK::FT f = sqrt(c.squared_radius());
      long r = ceil_to_long(f);
      cout<<r<<endl;
      cin>>n;
    }
}
