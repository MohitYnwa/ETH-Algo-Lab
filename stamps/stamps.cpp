#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_FLOAT.H>
typedef CGAL::MP_FLOAT ET;
#endif

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

using namespace std;
struct Lamp {
	Point p;
	Lamp(long x1, long y1) { p=Point(x1,y1);
	}
};

struct Stamp {
	long M;
	Point p;
	Stamp(long x1,long y1,long M1) { p=Point(x1,y1); M=M1; }
};

struct Wall {
	Segment s;
	Wall(long x11, long y11,long x22,long y22) { 
		Point p1 = Point(x11,y11); Point p2 =Point(x22,y22);
		s = Segment(p1,p2);
	}
};

bool compare_lamp(struct Lamp &l1, struct Lamp &l2)
{
	//if (l1.x == l2.x) return l1.y<l2.y;
//	return l1.x<l2.x;		
	return true;
}

bool compare_walls(struct Wall &w1, struct Wall &w2)
{
	return true;
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int l,s,w;
		cin>>l>>s>>w;
		
		vector<Lamp> lamps;
		for (int i=0;i<l;i++)
		{
			long x,y;
			cin>>x>>y;
			lamps.push_back(Lamp(x,y));
		}
	
		vector<Stamp> stamps;
		for (int i=0;i<s;i++)
		{
			long x,y,M;
			cin>>x>>y>>M;
			stamps.push_back(Stamp(x,y,M));
		}
		
		vector<Wall> walls;
		for (int i=0;i<w;i++)
		{
			long x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			walls.push_back(Wall(x1,y1,x2,y2));
		}	
	
		
		int P[l];
		for (int i=0;i<l;i++) P[i]=i;

		Program lp(CGAL::SMALLER,true,1,true,std::pow(2,12));
		for (int i=0;i<l;i++)		
		{
			lp.set_c(P[i], 1);
		}
		for (int i=0;i<s;i++)
		{
		    for(int j=0;j<l;j++){
			bool blocked=false;
			for (int k=0;k<w;k++)
			{
				if (do_intersect(Segment(lamps[j].p,stamps[i].p), walls[k].s)) {
					blocked = true; break;
				}
			}
			double dist = 0;
			if (!blocked) {	K::FT d = 1/CGAL::squared_distance( lamps[j].p , stamps[i].p);
					dist= CGAL::to_double(d);
			}
			lp.set_a(P[j],i,dist);
			lp.set_a(P[j],i+s,-1*dist);
		     }
		     lp.set_b(i,stamps[i].M);
		     lp.set_b(i+s, -1);
			
		}	
		
//		cout<<"True"<<endl;
		Solution sol=CGAL::solve_linear_program(lp,ET());

		if(sol.is_optimal())
		{
			cout<<"yes"<<endl;
		}
		else cout<<"no"<<endl;
	}
}
