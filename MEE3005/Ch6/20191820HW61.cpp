// Trapezoidal.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>

#define MaxDim 100
double function(double x);
double Trapeq(int n, double a, double b);

int main()
{
	double a = 0., b = 0.8;
	int n; // n=interval
	
	FILE* fp = _fsopen("out", "w", _SH_DENYNO);

	for (n = 1; n <= 10; n++)
	{
		double h = (b - a) / n;
		double I = Trapeq(n, a, b);
		double err = (1.640533 - I)/ 1.640533*100;
		//printf("n=%5d I=%15.7e err=%15.7e \n", n, I, err);
		printf("n=%5d h=%15.7e I=%15.7e err=%15.7e \n", n, h, I, err);
		fprintf(fp, "%5d %15.7e %15.7e %15.7e \n", n, h, I, err);
	}

	fclose(fp);

	return 0;
}

double Trapeq(int n, double a, double b)
{
	double h = (b - a) / n; //printf(" h= %17.5e \n", h);
	double x[MaxDim]; x[0] = a;
	for (int i = 0; i < n; i++) x[i + 1] = x[i] + h;
	double sum = 0.;
	for (int i = 0; i < n; i++) {
		sum += h / 2. * (function(x[i]) + function(x[i + 1]));
	}
	return sum;
}

double function(double x)
{
	double f = 0.2 + 25. * x - 200. * pow(x, 2) + 675. * pow(x, 3) - 900. * pow(x, 4) + 400. * pow(x, 5);
	return f;
}
