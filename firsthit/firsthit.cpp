
#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <boost/bind.hpp>
typedef CGAL::Exact_predicates_exact_constructions_kernel IK;
using namespace std;

void  minimum(IK::Ray_2 r, boost::optional<IK::Point_2>& closest, IK::Point_2 intersect)
{
  if (closest)
    {
      IK::Point_2 rs = r.source();
      if ( CGAL::squared_distance(rs,intersect) < CGAL::squared_distance(rs,*closest))
	closest = intersect;
    }
  else
    closest = intersect;
}

double floor_to_long(const IK::FT& x)
{
  double d = std::floor(CGAL::to_double(x));
  while (d>x) d--;
  while (d+1<=x) d++;
  return d;
}
int main()
{
  int n;
  cin>>n;

  //  cout<<"Mohit"<<endl;

  while ( n!=0 )
    {
      long xr0,yr0,xr1,yr1;
   
      cin>>xr0>>yr0>>xr1>>yr1;
      IK::Point_2 r0(xr0,yr0), r1(xr1,yr1);
      IK::Ray_2 ray (r0,r1) ;

      boost::optional<IK::Point_2> closest;
      for (int i=0;i<n;i++)
	{
	  cin>>xr0>>yr0>>xr1>>yr1;
	  IK::Point_2 s0(xr0,yr0),s1(xr1,yr1);
	  
	  IK::Segment_2 segment(s0,s1);
	  if (do_intersect(ray,segment))
	    {
	      CGAL::cpp11::result_of<IK::Intersect_2(IK::Ray_2,IK::Segment_2)>::type o = CGAL::intersection(ray,segment);
	      const IK::Point_2* op = boost::get<IK::Point_2>(&*o);
	      if (const IK::Point_2* op = boost::get<IK::Point_2>(&*o))
		minimum(ray,closest,*op);
	      if (const IK::Segment_2* seg = boost::get<IK::Segment_2>(&*o))
		{
		  minimum(ray,closest,(*seg).source());
		  minimum(ray,closest,(*seg).target());
		}
	    }
	}

      if (closest)
	{
	  const IK::Point_2 min = closest.get();
	  long x = floor_to_long(min.x());
	  long y = floor_to_long(min.y());
	  cout<<x<<" "<<y<<endl;
	}
	
     else cout<<"no"<<endl;
      
      cin>>n;
    }
}

