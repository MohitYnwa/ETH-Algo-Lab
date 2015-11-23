#include <iostream>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::All_faces_iterator All_face_iterator;
typedef Triangulation::Finite_vertices_iterator vertex_iterator;
typedef Triangulation::Face_circulator Face_circulator;
typedef Triangulation::Edge_circulator Edge_circulator;
typedef Triangulation::Edge Tr_Edge;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::FT FT;

double ceil_to_long(const FT& x)
{
	double d=std::floor(CGAL::to_double(x));
	//d = d+1;
	while (d>x) d--;
	while (d+1<=x) d++;
	return d == x ? d : d + 1.0L;
}
int main()
{
	while(true)
	{	
		int n;
		cin>>n;
		if (n==0) break;

		vector<Point> points;
		for(int i=0;i<n;i++)
		{
			long x,y;
			cin>>x>>y;
			points.push_back(Point(x,y));
		}

		Triangulation DT;
		DT.insert(points.begin(), points.end());

		double min = DT.segment(DT.finite_edges_begin()).squared_length();

		for(Edge_iterator eit = DT.finite_edges_begin();eit!=DT.finite_edges_end();eit++)
		{
			Segment seg = DT.segment(eit);				
			min = std::min(min, seg.squared_length());
		}
		
		cout<<ceil_to_long(sqrt(min) * 50 )<<endl;
	}
	return 0;
}

