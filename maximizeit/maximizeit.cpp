#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_FLOAT.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve_1(int a,int b)
{
	Program lp(CGAL::SMALLER, true,0,false,0); //x>=0 
	const int X=0;
	const int Y=1;

	lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0,4); //X + Y<=4
	lp.set_a(X,1,4); lp.set_a(Y,1,2); lp.set_b(1, a*b); // 4X + 2Y <= ab
	lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b(2,1); //-X+ Y <=1

	lp.set_d(X,X, 2*a); //double D
	lp.set_c(Y, -b);

	Solution s = CGAL::solve_quadratic_program(lp,ET());
	assert(s.solves_quadratic_program(lp));

	if (s.is_optimal())
	{
		long sol = std::floor(-1 * CGAL::to_double(s.objective_value()));
		cout<<sol<<endl;
		//cout<<s.objective_value()<<endl;
	}
	else if (s.is_unbounded())
	{
		cout<<"unbounded"<<endl;
	}
	else 
	{
		cout<<"no"<<endl;
	}
}

void solve_2(int a, int b)
{
	Program lp(CGAL::LARGER, false,0, false, 0);
	const int X = 0;
	const int Y = 1;
	const int Z2 = 2;

	lp.set_u(X,true,0);
	lp.set_u(Y,true,0);
	lp.set_l(Z2,true,0);//Z^2 has lowerbound = 0
	
	lp.set_a(X,0,1);lp.set_a(Y,0,1);lp.set_b(0,-4);//X + Y >= -4
	lp.set_a(X,1,4);lp.set_a(Y,1,2);lp.set_a(Z2,1,1);lp.set_b(1,-1*a*b);//4x + 2y+z^2 ?=-ab
	lp.set_a(X,2,-1);lp.set_a(Y,2,1);lp.set_b(2,-1);//-x + y >= -1

	lp.set_d(X,X,2*a);
	lp.set_d(Z2,Z2,2*1);
	lp.set_c(Y,b);
	
	Solution s=CGAL::solve_quadratic_program(lp,ET());
	assert(s.solves_quadratic_program(lp));

	if (s.is_optimal())
	{	
		long sol = std::ceil(CGAL::to_double(s.objective_value()));
		cout<<sol<<endl;	
	}
	else if (s.is_unbounded())
	{
		cout<<"unbounded"<<endl;
	}
	else
	{
		cout<<"no"<<endl;
	}
	
}

int main() {
	while(true)
	{
		//cout<<t<<endl;
		int p,a,b;
		cin>>p;

		if (p==0) break;

		cin>>a>>b;

		if (p==1) solve_1(a,b);
		if (p==2) solve_2(a,b);
	}

}

