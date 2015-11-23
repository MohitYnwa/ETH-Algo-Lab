#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_FLOAT.h>
typedef CGAL::MP_FLOAT ET;
#endif

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int main()
{
	while (true) 
	{
		int n,m;
		cin>>n>>m;
		if (n==0 && m==0) break;
	
		Program qp(CGAL::LARGER, true, 0, false, 0);	
		int alpha[n];
		for (int i=0;i<n;i++) alpha[i]=i;
		
		for (int i=0;i<n;i++)
		{
			int c,r;
			cin>>c>>r;
			qp.set_a(alpha[i],0,c);
			qp.set_a(alpha[i],1,r);
		}

		for (int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				int var;
				cin>>var;
				qp.set_d(alpha[i],alpha[j],2*var);								
			}
		}
		
		for (int i=0;i<m;i++)
		{
			int C,R,V;
			cin>>C>>R>>V;
			qp.set_b(0,C);
			qp.set_r(0,CGAL::SMALLER);
			qp.set_b(1,R);
			Solution s= CGAL::solve_nonnegative_quadratic_program(qp,ET());
			
			string result;
			//cout<<s.objective_value()<<" "<<V<<endl;
			if (s.is_optimal())
				result = CGAL::to_double(s.objective_value()) <= V ? "Yes." : "No.";
			else result="No.";
			if (s.status() == CGAL::QP_INFEASIBLE)
			{
				result= "No.";
			}
			cout<<result<<endl;
		}		
	}
}
