// BVP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>
#include <share.h>
#define MaxDim 200

void Tridiag(int n, double x[MaxDim], double y[MaxDim], double e[MaxDim],
double f[MaxDim], double g[MaxDim], double r[MaxDim], double h);
void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim],
double b[MaxDim], double x[MaxDim]);
double Exact(double x);

int main(void)
{
	FILE* fp = _fsopen("output", "w", _SH_DENYNO);
	double x[MaxDim], T[MaxDim];
	double e[MaxDim], f[MaxDim], g[MaxDim], r[MaxDim];

	int n = 20; //number of points
	double h = (10. - 0.) / (n + 0.);
	int i;

	for (i = 0; i <= n; i++) x[i] = 0. + i * h;

	Tridiag(n, x, T, e, f, g, r, h);
	ThomasEliminate(n, e, f, g, r, T);

	for (i = 0; i <= n; i++) printf(" %15.7e %15.7e %15.7e \n", x[i], T[i], Exact(x[i]));
	for (i = 0; i <= n; i++) fprintf(fp, " %15.7e %15.7e %15.7e \n", x[i], T[i], Exact(x[i]));
	printf(" dT/dx(x=10) = %15.7e \n", (T[n] - T[n - 1]) / h);

	return 0;
}

void Tridiag(int n, double x[MaxDim], double y[MaxDim], double e[MaxDim],
	double f[MaxDim], double g[MaxDim], double r[MaxDim], double h)
{
	int i;
	e[0] = 0.; f[0] = 1.; g[0] = -1.; r[0] = 0.;
	e[n] = 0.; f[n] = 1.; g[n] = 0.; r[n] = 200.;

	for (i = 1; i <= n - 1; i++) {
		e[i] = -1.; f[i] = 2. + 0.01 * h * h; g[i] = -1.; r[i] = 0.2 * h * h;
	}

}

void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim],
	double b[MaxDim], double x[MaxDim])
{
	int i;

	double E[MaxDim], F[MaxDim], G[MaxDim];
	for (i = 0; i <= n; i++) {
		x[i] = b[i]; E[i] = e[i]; F[i] = f[i]; G[i] = g[i];
	}

	for (i = 1; i <= n; i++) {
		E[i] = E[i] / F[i - 1]; F[i] = F[i] - E[i] * G[i - 1]; x[i] = x[i] - E[i] * x[i - 1];
	}
	x[n] = x[n] / F[n];
	for (i = n - 1; i >= 0; i--) x[i] = (x[i] - G[i] * x[i + 1]) / F[i];
}

double Exact(double x)
{
	return 58.3249275 * exp(0.1 * x) + 58.3249275 * exp(-0.1 * x) + 20.;
}