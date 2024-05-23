// Trapezoidal.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>

#define MaxDim 100
double function(double x);
double Trapeq(int n, double a, double b);
double Simp13m(int n, double a, double b);

int main()
{
	double a = 0., b = 0.8;
	int n; // n=interval

	FILE* fp = _fsopen("out", "w", _SH_DENYNO);

	for (n = 2; n <= 10; n=n+2) // 점의 갯수가 홀수여야만 가능함 (n is even) 2 4 6 8 10 (Interval)
	{
		double h = (b - a) / n;

		double I1 = Trapeq(n, a, b);
		double I2 = Simp13m(n, a, b);
		double tr = 1.640533;

		double err1 = (tr - I1) / tr * 100;
		double err2 = (tr - I2) / tr * 100;

		printf("n=%5d h=%15.7e I1=%15.7e I2=%15.7e err1=%15.7e err2=%15.7e \n", n, h, I1 ,I2, err1, err2);
		fprintf(fp, "%5d %15.7e %15.7e %15.7e %15.7e %15.7e \n", n, h, I1, I2, err1, err2);
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

double Simp13m(int n, double a, double b)
{
	double h = (b - a) / n; //printf(" h= %17.5e \n", h);
	double x[MaxDim]; x[0] = a;
	for (int i = 0; i < n; i++) x[i + 1] = x[i] + h;
	double sum = 0.;
	for (int i = 0; i < n - 1; i = i + 2) {
		sum += h / 3. * (function(x[i]) + 4. * function(x[i + 1]) + function(x[i + 2])); // 2h / 6 * (f0 + 4f1 + f2)
	}
	return sum;
}

double function(double x)
{
	double f = 0.2 + 25. * x - 200. * pow(x, 2) + 675. * pow(x, 3) - 900. * pow(x, 4) + 400. * pow(x, 5);
	return f;
}
