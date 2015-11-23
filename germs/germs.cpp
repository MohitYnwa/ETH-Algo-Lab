#include <iostream>
#include <map>
#include <set>
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
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Point TP;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::FT FT;

double min_segment(Segment rect[], Point p)
{
	double min_s = squared_distance(p,rect[0]);
	for (int i=0;i<4;i++)
	{
		min_s = std::min(min_s, squared_distance(p, rect[i]));
	}	
	return min_s;
}

double ceil_to_long(double x)
{
	double d = std::floor(x);
	while(d>x) d--;
	while(d+1<=x) d++;
	return d==x ? d : d+1.0L;
}
int time (double dist)
{
	double t = sqrt(sqrt(dist) - 0.5);
	return ceil_to_long(t);	
}

void solve(Triangulation DT, Segment rect[],vector<Point> points)
{
	map<TP,double> vertex_dist;
	for (vertex_iterator vit = DT.finite_vertices_begin();vit!=DT.finite_vertices_end();vit++)
	{
		TP vertex_p = vit->point();
		double min_dist = min_segment(rect, vertex_p);
		vertex_dist[vertex_p] = min_dist;
	}	
	
	for(Edge_iterator eit=	DT.finite_edges_begin(); eit!=DT.finite_edges_end();eit++)
	{
		double min_dist = CGAL::to_double(DT.segment(eit).squared_length()/4);
		TP vertex_p1 = eit->first->vertex(DT.cw(eit->second))->point();
		TP vertex_p2 = eit->first->vertex(DT.ccw(eit->second))->point();

		vertex_dist[vertex_p1] = std::min(vertex_dist[vertex_p1], min_dist);
		vertex_dist[vertex_p2] = std::min(vertex_dist[vertex_p2], min_dist);
	}

	vector<double> dist;
	for (std::map<TP,double>::iterator it = vertex_dist.begin();it!= vertex_dist.end(); it++)
	{
		dist.push_back(it->second);
	}

	sort(dist.begin(),dist.end());

	int f,m,l;
	f = time(dist[0]);
	m = time(dist[points.size()/2]);
	l = time(dist[points.size() - 1]);

	cout<<f<<" "<<m<<" "<<l<<endl;	
}

int main()
{
	//cout<<fixed<<setprecision(0);
	int cnt=0;
	while(true)
	{
		int n;
		cin>>n;
		if (n==0) break;
		
		int l,b,r,t;
		cin>>l>>b>>r>>t;

		Segment rect[4];
		rect[0] = Segment(Point(l,b),Point(r,b));
		rect[1] = Segment(Point(l,b),Point(l,t));
		rect[2] = Segment(Point(l,t),Point(r,t));
		rect[3] = Segment(Point(r,t),Point(r,b));
		
		vector<Point> points;
		for (int i=0;i<n;i++)
		{
			int x,y;
			cin>>x>>y;
			points.push_back(Point(x,y));	
		}
		Triangulation DT;
		DT.insert(points.begin(),points.end());
		

		solve(DT,rect,points);

	}
	return 0;
}

