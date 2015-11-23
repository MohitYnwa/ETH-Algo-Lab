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

int main()
{
	cout<<fixed<<setprecision(0);
	while(true)
	{	
		int n;
		cin>>n;
		if (n==0) break;
		
		vector<Point> points;
		for (int i=0;i<n;i++)
		{
			long x,y;
			cin>>x>>y;	
			points.push_back(Point(x,y));
		}

		Triangulation DT;
		DT.insert(points.begin(),points.end());

		int m;
		cin>>m;
		vector<Point> newp;
		//double  min = -1;
		for (int i=0;i<m;i++)
		{
			long x,y;
			cin>>x>>y;
			Point np(x,y);
			newp.push_back(np);
		}

		vector<double> sol;
		for (int i=0;i<m;i++)
		{
			Point np = newp[i];
			Point p = DT.nearest_vertex(np)->point();

			double dist = CGAL::to_double(squared_distance(np,p));
			sol.push_back(dist);
			
		}

		for (int i=0;i<m;i++) cout<<sol[i]<<endl;

				
		
	}
	return 0;
}

