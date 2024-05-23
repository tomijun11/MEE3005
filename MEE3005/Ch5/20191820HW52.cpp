// 20191820HW33.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// GE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100
void Tridiag(int n, double x[MaxDim], double y[MaxDim], double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim]);
double SplineInterp(int n, double x[MaxDim], double y[MaxDim], double d2x[MaxDim], double xu);
void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim], double x[MaxDim]);

int main()
{
	double e[MaxDim], f[MaxDim], g[MaxDim], r[MaxDim], x[MaxDim], y[MaxDim], d2x[MaxDim];
	
	int i, n = 10; // x = -1~1, n = interval
	for (i = 0; i <= n; i++)
	{
		x[i] = -1. + (2. * i) / (n + 0.);
		y[i] = 1. / (1. + 25. * x[i] * x[i]);
	}
	
	double xx[MaxDim];
	for (i = 0; i <= 50; i++) // 찍을 점의 갯수
	{
		xx[i] = -1. + (2. * i) / (50 + 0.);
	}

	FILE* fp = _fsopen("out", "w", _SH_DENYNO);
	double x0, y0;

	Tridiag(n, x, y, e, f, g, r);
	ThomasEliminate(n, e, f, g, r, d2x);

	for (i = 0; i <= 50; i++)
	{
		x0 = xx[i]; y0 = SplineInterp(n, x, y, d2x, xx[i]);
		printf("x=%15.7e y=%15.7e \n", x0, y0);
		fprintf(fp, " %15.7e %15.7e \n", x0, y0);
	}

	fclose(fp);
	
	//printf(" f(xu)= %15.7e \n", SplineInterp(n, x, y, d2x, xu));

	return 0;
}

double SplineInterp(int n, double x[MaxDim], double y[MaxDim], double d2x[MaxDim], double xu)
{
	int i = 1;
	do {
		if (xu >= x[i - 1] && xu <= x[i])
		{
			return d2x[i - 1] / 6. / (x[i] - x[i - 1]) * pow(x[i] - xu, 3)
				+ d2x[i] / 6. / (x[i] - x[i - 1]) * pow(xu - x[i - 1], 3)
				+ (y[i - 1] / (x[i] - x[i - 1]) - d2x[i - 1] * (x[i] - x[i - 1]) / 6.) * (x[i] - xu)
				+ (y[i] / (x[i] - x[i - 1]) - d2x[i] * (x[i] - x[i - 1]) / 6.) * (xu - x[i - 1]);
		}
		else i++;
	} while (i != n + 1);
	printf("outside range \n");
}

void Tridiag(int n, double x[MaxDim], double y[MaxDim], double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim])
{
	int i;
	e[0] = 0.; f[0] = 1.; g[0] = 0.; r[0] = 0.;
	e[n] = 0.; f[n] = 1.; g[n] = 0.; r[n] = 0.;

	for (int i = 1; i < n; i++)
	{
		e[i] = (x[i] - x[i - 1]);
		f[i] = 2. * (x[i + 1] - x[i - 1]);
		g[i] = (x[i + 1] - x[i]);
		r[i] = 6. / (x[i + 1] - x[i]) * (y[i + 1] - y[i])
			- 6. / (x[i] - x[i - 1]) * (y[i] - y[i - 1]);
	}
}

void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim], double x[MaxDim])
{
	int i;

	double E[MaxDim], F[MaxDim], G[MaxDim];
	for (i = 0; i <= n; i++) { // i = 0부터 시작
		E[i] = e[i]; F[i] = f[i]; G[i] = g[i]; x[i] = r[i];
	}

	for (i = 2; i <= n; i++) {
		E[i] = E[i] / F[i - 1];
		F[i] = F[i] - E[i] * G[i - 1];
		x[i] = x[i] - E[i] * x[i - 1];
	}
	x[n] = x[n] / F[n];
	for (i = n - 1; i >= 1; i--) x[i] = (x[i] - G[i] * x[i + 1]) / F[i];
}

