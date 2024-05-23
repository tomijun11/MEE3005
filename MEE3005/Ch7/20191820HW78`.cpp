// 20191820HW74.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define Dim 3

void RK4(double x, double y[Dim], double h, double ynew[Dim]);
void Derivs(double x, double y[Dim], double dydx[Dim]);

int main(void)
{
	double x0 = 0., xf = 10., y0[Dim];
	double h0 = 0.01;
	double x, y[Dim], ynew[Dim];
	int j;
	y0[0] = 0.; y0[1] = 0.; // y[0] : y, y[1] : y', y[2] : y''

	double yl = 0, yr = 10., ym = (yl + yr) / 2.;
	do
	{
		y0[2] = ym;
		//printf("\n type y0[2] %lf\n", y0[2]);
		printf("\n type y0[2] \n"); scanf_s("%lf", &y0[2]);
		x = x0;

		FILE* fp = _fsopen("out", "w", _SH_DENYNO);
		for (j = 0; j < Dim; j++) y[j] = y0[j];
		int i = 0;
		printf("%10d %15.7e %15.7e %15.7e %15.7e \n", i, x, y[0], y[1], y[2]);
		fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e \n", i, x, y[0], y[1], y[2]);
		double h = h0;
		do
		{
			RK4(x, y, h, ynew);
			if (xf < x + h) h = xf - x;
			i++; x = x + h; for (j = 0; j < Dim; j++) y[j] = ynew[j];
			printf("%10d %15.7e %15.7e %15.7e %15.7e \n", i, x, y[0], y[1], y[2]);
			fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e \n", i, x, y[0], y[1], y[2]);
		} while (x < xf);
		printf("*** y0[2] = %15.7e \n",y0[2]);
		fclose(fp);

		if (y[1] > 1.) // f'(+inf) = 1
			yr = ym;
		else
			yl = ym;
		ym = (yl + yr) / 2.;

	} while (fabs(y[1] - 1.) > 1.e-3);

	return 0;
}

void RK4(double x, double y[Dim], double h, double ynew[Dim])
{
	double k1[Dim], k2[Dim], k3[Dim], k4[Dim], ymid[Dim], slope[Dim];
	int j;
	Derivs(x, y, k1);
	for (j = 0; j < Dim; j++) ymid[j] = y[j] + 0.5 * h * k1[j];
	Derivs(x + 0.5 * h, ymid, k2);
	for (j = 0; j < Dim; j++) ymid[j] = y[j] + 0.5 * h * k2[j];
	Derivs(x + 0.5 * h, ymid, k3);
	for (j = 0; j < Dim; j++) ymid[j] = y[j] + h * k3[j];
	Derivs(x + h, ymid, k4);
	for (j = 0; j < Dim; j++) slope[j] = (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6.;
	for (j = 0; j < Dim; j++) ynew[j] = y[j] + h * slope[j];
}

void Derivs(double x, double y[Dim], double dydx[Dim])
{
	dydx[0] = y[1]; // 1st derivs : dydx[0] = df/dx
	dydx[1] = y[2]; // 2nd derivs : dydx[1] = du/dx
	dydx[2] = -0.5 * y[0] * y[2]; // 3rd derivs : dydx[2] = dv/dx
}
