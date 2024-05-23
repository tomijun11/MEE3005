// 20191820HW71.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

void Euler(double x, double y, double h, double* ynew);
void Derivs(double x, double y, double* ynew);
double Exact(double x);
void Heun(double x, double y, double h, double* ynew);
void Midpoint(double x, double y, double h, double* ynew);
void Ralston(double x, double y, double h, double* ynew);

int main(void)
{
	char fname[100] = "out0"; int flen = strlen(fname) - 1;
	double x0 = 0., xf = 4., y0 = 1., h = 0.5; // x0 : start, y0 : IC, xf : find, h : step size
	double x = x0, y = y0, y2 = y0, y3 = y0, y4 = y0, ynew, ynew2, ynew3, ynew4; // y : Euler, y2 : Heun, y3 : Midpoint, y4 : Ralston
	int i = 0;

	for (int k = 0; k < 1; k++, fname[flen]++)
	{
		FILE* fp = _fsopen(fname, "w", _SH_DENYNO);

		printf("%10d %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y2, y3, y4, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y2, y3, y4, Exact(x));
		do {
			Euler(x, y, h, &ynew);
			Heun(x, y2, h, &ynew2);
			Midpoint(x, y3, h, &ynew3);
			Ralston(x, y4, h, &ynew4);
			if (xf < x + h) h = xf - x;
			i++; x = x + h; y = ynew, y2 = ynew2; y3 = ynew3; y4 = ynew4;
			printf("%10d %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y2, y3, y4, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y2, y3, y4, Exact(x));
		} while (x < xf);

		fclose(fp);
		printf("\n");
		x = x0; y = y0; y2 = y0; y3 = y0; y4 = y0;  h = h / 2.; i = 0; // reset
	}
	printf("학번=20191820, 이름 김형준\n");
	return 0;
}

void Ralston(double x, double y, double h, double* ynew)
{
	double dydx1, dydx2;
	Derivs(x, y, &dydx1); // f(xi,yi)
	double ymid = y + 3. * h / 4. * dydx1; // yi+3/4
	Derivs(x + 3. * h / 4., ymid, &dydx2); // f(xi+3/4,yi+3/4)
	double slope = (dydx1 + 2. * dydx2) / 3.;
	*ynew = y + h * slope;
}

void Midpoint(double x, double y, double h, double* ynew)
{
	double dydx1, dydx2;
	Derivs(x, y, &dydx1); // f(xi,yi)
	double ymid = y + h/2. * dydx1; // yi+1/2
	Derivs(x + h / 2., ymid, &dydx2); // f(xi+1/2,yi+1/2)
	double slope = dydx2;
	*ynew = y + h * slope;
}

void Heun(double x, double y, double h, double* ynew)
{
	double dydx1, dydx2;
	Derivs(x, y, &dydx1);
	double ymid = y + h * dydx1;
	Derivs(x + h, ymid, &dydx2);
	double slope = (dydx1 + dydx2) / 2.;
	*ynew = y + h * slope;
}

void Euler(double x, double y, double h, double* ynew)
{
	double dydx;
	Derivs(x, y, &dydx);
	*ynew = y + h * dydx;
}

void Derivs(double x, double y, double* dydx)
{
	*dydx = -2. * pow(x, 3) + 12. * pow(x, 2) - 20. * x + 8.5;
}

double Exact(double x)
{
	return -0.5 * pow(x, 4) + 4. * pow(x, 3) - 10. * pow(x, 2) + 8.5 * x + 1;
}
