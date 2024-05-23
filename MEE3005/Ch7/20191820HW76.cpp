// 20191820HW71.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

void Euler(double x, double y, double h, double* ynew);
void Euler_imp(double x, double y, double h, double* ynew);
void RK4(double x, double y, double h, double* ynew);
void Derivs(double x, double y, double* ynew);
double Exact(double x);


int main(void)
{
	char fname[100] = "out0"; int flen = strlen(fname) - 1; // xf = 0.1(1e-2)
	double x0 = 0., xf = 0.1, y0 = 0., h, h0[4] = { 5.e-4,1.5e-3,2.1e-3,1.e-2 }; // x0 : start, y0 : IC, xf : find, h : step size
	double x = x0, y = y0, y2 = y0, y3 = y0, ynew, ynew2, ynew3;
	int i = 0;
 
	for (int k = 3; k < 4; k++, fname[flen]++)
	{
		h = h0[k];
		FILE* fp = _fsopen(fname, "w", _SH_DENYNO);

		printf("%10d %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y3, y2, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y3, y2, Exact(x));
		do {
			Euler(x, y, h, &ynew);
			Euler_imp(x, y2, h, &ynew2);
			RK4(x, y3, h, &ynew3);
			if (xf < x + h) h = xf - x;
			i++; x = x + h; y = ynew; y2 = ynew2; y3 = ynew3;
			printf("%10d %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y3, y2, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e %15.7e %15.7e \n", i, x, y, y3, y2, Exact(x));
		} while (x < xf);

		fclose(fp);
		printf("\n");
		x = x0; y = y0; y2 = y0; y3 = y0; i = 0; // reset
	}
	printf("학번=20191820, 이름 김형준\n");
	return 0;
}

void Euler(double x, double y, double h, double* ynew)
{
	double dydx;
	Derivs(x, y, &dydx);
	*ynew = y + h * dydx;
}

void Euler_imp(double x, double y, double h, double* ynew)
{
	*ynew = (y + 3000 * h - 2000 * h * exp(-x - h)) / (1 + 1000 * h);
}

void RK4(double x, double y, double h, double* ynew)
{
	double k1, k2, k3, k4;
	Derivs(x, y, &k1);
	double ymid = y + 0.5 * h * k1;
	Derivs(x + 0.5 * h, ymid, &k2);
	ymid = y + 0.5 * h * k2;
	Derivs(x + 0.5 * h, ymid, &k3);
	ymid = y + h * k3;
	Derivs(x + h, ymid, &k4);
	double slope = (k1 + 2 * k2 + 2 * k3 + k4) / 6.;
	*ynew = y + h * slope;
}

void Derivs(double x, double y, double* dydx)
{
	*dydx = -1000 * y + 3000 - 2000 * exp(-x);
}

double Exact(double x)
{
	return 3. - 0.998 * exp(-1000. * x) - 2.002 * exp(-x);
}