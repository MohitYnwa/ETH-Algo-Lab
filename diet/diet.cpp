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
	while(true)
	{
		
		int n,m;
		cin>>n>>m;
		if (n==0 && m==0) break;
		int F[m];

		Program qp(CGAL::SMALLER, true, 0, false, 0);//Lower Bound of F
		for (int i=0;i<m;i++) F[i] = i;

		for (int i=0;i<n;i++)
		{
			int min,max;
			cin>>min>>max;
			
			qp.set_b(i, max);
			qp.set_b(i+n,-1 * min);
		}

		for (int i=0;i<m;i++)
		{
			int cst;
			cin>>cst;
			for (int j=0;j<n;j++)
			{
				int amt;
				cin>>amt;
				//max condition
				qp.set_a(F[i], j, amt);
				//min condition
				qp.set_a(F[i], j + n, -1* amt);
			}
			qp.set_c(F[i], cst);
		}
		
		Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
		if (s.status()== CGAL::QP_INFEASIBLE)  {
			cout<<"No such diet."<<endl;
		}
		else
		{
			long sol = std::floor(CGAL::to_double(s.objective_value()));
			cout<<sol<<endl;
		}
	}
}
