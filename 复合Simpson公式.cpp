#include<iostream.h>
#include<math.h>

class simpson
{
	private:
		int n, k;
		double a, b, f, half_interval, integral, interval, sum_even_terms;
		double sum_odd_terms, x;
	public:
		double func(double t)
		{
			f=2e3*log(1e5/(1e5-2e3*t))-10*t;
			return f;
		}
		void intergration();
};

int  main()
{
	simpson simp;
	simp.intergration();
}

void simpson::intergration()
{
	cout<<"\nInput a&b(lower and upper limits):";
	cin>>b>>a;
	cout<<"\nInput N(Times you want to use simpson law):";
	cin>>n;
	interval=(b-a)/n;
	half_interval=interval/2.0;
	sum_even_terms=0.0;
	sum_odd_terms=0.0;
	for(k=1; k<n; k++)
	{
		x=a+k*interval;
		sum_even_terms+=func(x);
		sum_odd_terms+=func(x+half_interval);
	}
	integral=(2.0*sum_even_terms+4.0*sum_odd_terms-func(a)+func(b))*half_interval/3.0;
	cout<<endl<<"The integral = "<<integral<<endl;
}
