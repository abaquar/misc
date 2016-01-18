#include <stdio.h>
#include <math.h>

double f(double x){return exp(-1*x) - cos(x);}

double flinha(double x){return -1*exp(-1*x) + sin(x);}

double xkmaisum(double xk){return xk - ( f(xk) / flinha(xk) );}

double Er(double x, double xast){return x - xast;}

double Ea(double in){return (in < 0) ? in*-1 : in;}

double Ep(double in, double x){return (x < 0) ? in/(x*-1) : in/x;}

main(){
	double xk = -2;
	double er,ea;
	int i;

	printf("K	Xk		f(Xk)		f'(xk)		Xk+1		Er		Ea		Ep\n");
	for(i=0;i<7;i++){
		printf("%d	",i+1);
		printf("%f	",xk);
		printf("%f	",f(xk));
		printf("%f	",flinha(xk));
		printf("%f	",xkmaisum(xk));
		er = Er(xkmaisum(xk),xk);
		ea = Ea(er);
		printf("%f	",er);
		printf("%f	",ea);
		printf("%f	",Ep(ea,xkmaisum(xk)));
		printf("\n");
		xk = xkmaisum(xk);
	}
}
