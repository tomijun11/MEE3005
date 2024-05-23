// 20191820HW25.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include <iostream>
#include <math.h>

double ufunc(double x, double y);
double vfunc(double x, double y);
double dux(double x, double y);
double duy(double x, double y);
double dvx(double x, double y);
double dvy(double x, double y);
void Newton2(double x0, double y0, double es, int imax);

int main()
{
	double x0 = 1.2, y0 = 1.2;
	double es = 1.e-2;
	int imax = 1000;
	Newton2(x0, y0, es, imax);
	return 0;
}

double ufunc(double x , double y)
{
	double f = -x * x + x + 0.75 - y; // -x^2+x+0.75-y=0
	return f;
}

double vfunc(double x, double y)
{
	double f = y + 5 * x * y - x * x; // y+5xy-x^2=0
	return f;
}

double dux(double x, double y)
{
	double f = -2 * x + 1; // -2x+1
	return f;
}

double duy(double x, double y)
{
	double f = -1; // -1
	return f;
}

double dvx(double x, double y)
{
	double f = 5 * y - 2 * x; // 5y-2x
	return f;
}

double dvy(double x, double y)
{
	double f = 1 + 5 * x; // 1+5x
	return f;
}


void Newton2(double x0, double y0, double es, int imax)
{
	FILE* fp = _fsopen("Newton2.out", "w", _SH_DENYNO);
	printf(" Newton-Raphson Method \n");

	double ur, vr, yr = y0, xr = x0, xrold, yrold, eax, eay, temp;
	int iter = 0;
	ur = ufunc(xr, yr); vr = vfunc(xr, yr);
	do
	{
		xrold = xr;
		yrold = yr;
		temp = (dux(xrold, yrold) * dvy(xrold, yrold) - duy(xrold, yrold) * dvx(xrold, yrold));
		xr = xrold - (ur * dvy(xrold, yrold) - vr * duy(xrold, yrold)) / temp;
		yr = yrold - (vr * dux(xrold, yrold) - ur * dvx(xrold, yrold)) / temp;

		ur = ufunc(xr, yr); vr = vfunc(xr, yr);
		iter++;
		if (xr != 0.) eax = fabs((xr - xrold) / xr) * 100.;
		if (yr != 0.) eay = fabs((yr - yrold) / yr) * 100.;
		fprintf(fp, " %4d  %15.7e  %15.7e %15.7e %15.7e %15.7e %15.7e \n", iter, xr, yr, ur, vr, eax, eay);
		printf(" iter= %4d  xr= %15.7e  yr= %15.7e ur= %15.7e vr= %15.7e errorx= %15.7e errory= %15.7e \n", iter, xr, yr, ur, vr, eax, eay);
	} while (!(eax < es && eay < es || iter >= imax)); 
	fclose(fp);
}
