// 20191820HW74.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define Dim 2

void RK4(double x, double y[Dim], double h, double ynew[Dim]);
void Derivs(double x, double y[Dim], double dydx[Dim]);

int main(void)
{
	char fname[100] = "out0"; int flen = strlen(fname) - 1;
	double x0 = 0., xf = 2., h = 0.5; // x0 : start, y0 : IC, xf : find, h : step size
	double y0[Dim] = { 4., 6. };
	//double y0[Dim] = { 0.1, 0. }; // for (a)
	//double y0[Dim] = { 0.785398, 0. }; // pi/4 for (b)
	
	double x = x0, y[Dim], ynew[Dim];
	int j;

	int i = 0;
	for (j = 0; j < Dim; j++) y[j] = y0[j];

	for (int k = 0; k < 1; k++, fname[flen]++)
	{
		FILE* fp = _fsopen(fname, "w", _SH_DENYNO);
		
		printf("%10d %15.7e %15.7e %15.7e \n", i, x, y[0], y[1]); fprintf(fp, "%10d %15.7e %15.7e %15.7e \n", i, x, y[0], y[1]);
		do {
			RK4(x, y, h, ynew);
			if (xf < x + h) h = xf - x;
			i++; x = x + h; for(j=0;j<Dim;j++) y[j] = ynew[j];
			printf("%10d %15.7e %15.7e %15.7e \n", i, x, y[0], y[1]); fprintf(fp, "%10d %15.7e %15.7e %15.7e \n", i, x, y[0], y[1]);
		} while (x < xf);

		fclose(fp);
		printf("\n");
		x = x0; for (j = 0; j < Dim; j++) y[j] = y0[j]; h = h / 2.; i = 0; // reset
	}
	printf("학번=20191820, 이름 김형준\n");
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
	dydx[0] = -0.5 * y[0];
	dydx[1] = 4. - 0.3 * y[1] - 0.1 * y[0];
	//dydx[0] = y[1]; // dy1/dx = y2
	//dydx[1] = -16.1 * y[0]; // dy2/dx = -16.1*y1
	//dydx[1] = -16.1 * sin(y[0]); // dy4/dx = -16.1*sin(y3)
}
