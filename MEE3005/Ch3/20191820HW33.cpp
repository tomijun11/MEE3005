// 20191820HW33.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// GE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100

void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim], double x[MaxDim]);

int main()
{
	int i, n;
	double e[MaxDim], f[MaxDim], g[MaxDim], r[MaxDim], x[MaxDim], y[MaxDim];

	n = 21;
	for (i = 1; i <= n; i++)
		x[i] = (i - 1.) / (n - 1.);

	for (i = 2; i <= n - 1; i++)
	{
		e[i] = 1.;
		f[i] = 16. / ((n - 1.) * (n - 1.)) - 2.;
		g[i] = 1.;
		r[i] = 0.;
	}
				f[1] = 1.; g[1] = 0.; r[1] = 0.;
	e[n] = 0.;  f[n] = 1.; r[n] = 1.;

	ThomasEliminate(n, e, f, g, r, y);

	FILE* fp = _fsopen("out", "w", _SH_DENYNO);

	for (i = 1; i <= n; i++) {
		printf(" y (%1d) = %15.7e %15.7e \n", i, x[i], y[i]);
		fprintf(fp, " %4d %15.7e %15.7e \n", i, x[i], y[i]);
	}

	fclose(fp);

	double err;
	for (i = 1; i <= n; i++) {
		err = f[i] * y[i] - r[i];
		if (i != n) err += g[i] * y[i + 1];
		if (i != 1) err += e[i] * y[i - 1];
		printf(" err (%1d) = %15.7e \n", i, err);
	}

	return 0;
}

void ThomasEliminate(int n, double e[MaxDim], double f[MaxDim], double g[MaxDim], double r[MaxDim], double x[MaxDim])
{
	int i;

	double E[MaxDim], F[MaxDim], G[MaxDim];
	for (i = 1; i <= n; i++) {
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

