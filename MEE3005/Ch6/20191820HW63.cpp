// Trapezoidal.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>

#define MaxDim 100
double function1(double x);
double function2(double x);
double Simp13m(int n, double a, double b);
double Mideq(int n, double a, double b);

int main()
{
	int n = 10;
	double I1 = Simp13m(n, 0., 2.);
	double I2 = Mideq(n, 0., 0.5);
	double Iex = sqrt(acos(-1.) / 8.);
	double err = (Iex - I1 - I2) / Iex * 100.;
	printf("n=%5d I1=%15.7e I2=%15.7e I=%15.7e err=%15.7e \n", n, I1, I2, I1 + I2, err);

	n = 20;
	I1 = Simp13m(n, 0., 2.);
	I2 = Mideq(n, 0., 0.5);
	err = (Iex - I1 - I2) / Iex * 100.;
	printf("n=%5d I1=%15.7e I2=%15.7e I=%15.7e err=%15.7e\n", n, I1, I2, I1 + I2, err);
	
	return 0;
}

double Mideq(int n, double a, double b)
{
	double h = (b - a) / n;
	double x[MaxDim]; x[0] = a;
	for (int i = 0; i < n; i++) x[i + 1] = x[i] + h;
	double sum = 0.;
	for (int i = 0; i < n; i++) {
		sum += h * function2(0.5 * (x[i] + x[i + 1]));
	}
	return sum;
}

double Simp13m(int n, double a, double b)
{
	double h = (b - a) / n; //printf(" h= %17.5e \n", h);
	double x[MaxDim]; x[0] = a;
	for (int i = 0; i < n; i++) x[i + 1] = x[i] + h;
	double sum = 0.;
	for (int i = 0; i < n ; i = i + 2) {
		sum += h / 3. * (function1(x[i]) + 4. * function1(x[i + 1]) + function1(x[i + 2])); // 2h / 6 * (f0 + 4f1 + f2)
	}
	return sum;
}

double function1(double x)
{
	double f = exp(-2. * x * x);
	return f;
}

double function2(double x)
{
	double f = exp(-2. / x / x) / x / x;
	return f;
}