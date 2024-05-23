// 20191820HW71.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

void Euler(double x, double y, double h, double* ynew);
void Derivs(double x, double y, double* ynew);
double Exact(double x);


int main(void)
{
	FILE* fp = _fsopen("output", "w", _SH_DENYNO);

	double x0 = 0., xf = 4., y0 = 1., h = 0.5; // x0 : start, y0 : IC, xf : find, h : step size
	double x = x0, y = y0, ynew;
	int i = 0;


	
	printf("%10d %15.7e %15.7e %15.7e \n", i, x, y, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e \n", i, x, y, Exact(x));
	do {
		Euler(x, y, h, &ynew);
		if (xf < x + h) h = xf - x;
		i++; x = x + h; y = ynew;
		printf("%10d %15.7e %15.7e %15.7e \n", i, x, y, Exact(x)); fprintf(fp, "%10d %15.7e %15.7e %15.7e \n", i, x, y, Exact(x));
	} while (x < xf);


	
	

	fclose(fp);
	printf("학번=20191820, 이름 김형준\n");
	return 0;
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
