#nclude <iostream>
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
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::FT FT;

enum COLOUR { White = 0 , Black = 1 , Grey = 2};
vector<bool> solve(Triangulation DT, vector<Point> ps, vector<long> Ds,int cnt)
{

vector<bool> solution(ps.size(),false);
for (int j=0;j<ps.size();j++)
{
	Point p = ps[j];
	long D = Ds[j];
	stack<Face_handle> st;
	map<Face_handle,COLOUR> visited;
	
	Point nearest = DT.nearest_vertex(p)->point();
	if (squared_distance(nearest,p) < D) continue;
	
	
//	if (cnt == 7) cout<<"Hey"<<endl;
	long min_dist = 4*D;

	st.push(DT.locate(p));
	//If the max distance from edge is D then the distance from circumcenter is guaranteed to be greater than D by pythogoras theorem
	while(!st.empty())
	{
//		if (fh == NULL) return false;
//		if (cnt == 7) cout<<"Hello"<<endl;
		Face_handle fh = st.top();
//		if (cnt == 7) cout<<"Hello1"<<endl;
		st.pop();
//		if (cnt ==7) cout<<"Hello2"<<endl;
//		if (fh == NULL) cout<<p<<endl;
		if (DT.is_infinite(fh)) { 
			solution[j]=true;
			break;
		}
		
//		if (cnt==7) cout<<"abc"<<endl;
		for (int i=0;i<3;i++)
		{
			Segment edge = DT.segment(fh,i);
//			if (cnt==7) cout<<"Inside"<<endl;
			if (edge.squared_length() >= min_dist)
			{
				Face_handle fh_new = fh->neighbor(i);
				if (visited[fh_new] ==White)
				{
					st.push(fh_new);
					visited[fh_new] = Grey;
				}
			}
		}
		visited[fh] = Black;
	}
}

return solution;
}

int main()
{
	//cout<<fixed<<setprecision(0);
	int cnt=0;
	while(true)
	.	
		//cout<<cnt<<endl;
		
		cnt++;
		int n;
		cin>>n;
		if (n==0) break;
		

		vector<Point> points(n);
		for (int i=0;i<n;i++)
		{
			int x,y;
			cin>>x>>y;	
			points[i] = Point(x,y);
		}

		int m;
		cin>>m;
		vector<Point> query(m);
		vector<long> dist(m);
		//double  min = -1;
		vector<bool> solution;
		for (int i=0;i<m;i++)
		{
			int x,y;
			long D;
			cin>>x>>y>>D;
			Point np(x,y);
			query[i] = np;
			dist[i] = D;
		//	solution += solve(DT, np, D);
		}
	
		Triangulation DT;
		DT.insert(points.begin(),points.end());
		solution= solve(DT, query,dist,cnt);

		for (int i=0;i<m;i++)
		if (solution[i]) cout<<"y"; else cout<<"n";

		//cout<<solution<<endl;		
		cout<<endl;
	}
	return 0;
}

