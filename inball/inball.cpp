#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_FLOAT.H>
typedef CGAL::MP_FLOAT ET;
#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int main()
{
	while (true)
	{
		int n,d;
		cin>>n;
		if(n==0) break;
		cin>>d;

		Program lp(CGAL::SMALLER,false,0,false,0);
		vector<int> R(d+1);
		for (int i=0;i<d+1;i++)
		{
			R[i]=i;
		}

		for (int i=0;i<n;i++)
		{
			int sum =0;
			for(int j=0;j<d;j++)
			{
				int a;
				cin>>a;
				sum += a * a;
				lp.set_a(R[j],i,a);		
			}
			sum = std::sqrt(sum);
			lp.set_a(R[d],i,sum);
			int b;
			cin>>b;
			lp.set_b(i,b);
		}
		
		lp.set_c(R[d], -1);		
		lp.set_l(R[d],true,0);
		Solution sol = CGAL::solve_linear_program(lp,ET());

		if (sol.is_optimal())
		{	
			double res =floor(-1* CGAL::to_double(sol.objective_value()));
			if (res == -0) res =0;
			cout<<res<<endl;
		}
		else if(sol.is_infeasible())
		{
			cout<<"none"<<endl;
		}
		else if(sol.is_unbounded())
		{
			cout<<"inf"<<endl;
		}
	}
}
