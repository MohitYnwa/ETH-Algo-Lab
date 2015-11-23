
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
using namespace std;
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
      string intersects = "no";
      for (int i=0;i<n;i++)
	{
	  cin>>xr0>>yr0>>xr1>>yr1;
	  if (intersects == "yes") continue;
	  IK::Point_2 s0(xr0,yr0),s1(xr1,yr1);
	  
	  IK::Segment_2 segment(s0,s1);
	  if (do_intersect(ray,segment)) intersects = "yes";
	}

      cout<<intersects<<endl;
      cin>>n;
    }
}

