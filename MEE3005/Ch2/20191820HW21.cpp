// 20191820HW21.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

double function(double x);
double Bisect(double xl, double xu, double es, int imax);


int main()
{
	double xl = 12., xu = 16.;
	double es = 1.e-2, xr;
	int imax = 1000;
	do {
		printf(" xl=? \n"); scanf_s("%lf", &xl); printf(" xu=? \n"); scanf_s("%lf", &xu);
		printf(" fl= %15.7e, fu= %15.7e\n", function(xl), function(xu));
	} while (function(xl) * function(xu) > 0.);
	if (function(xl) * function(xu) <= 0.) {
		printf("  \n");
		xr = Bisect(xl, xu, es, imax);
	}

	return 0;
}

double function(double x)
{
	//double f = 9.8 * 68.1 / x * (1. - exp(-x * 10. / 68.1)) - 40.;
	double f = log(x * x) - 0.7; //log(x*x)-0.7
	return f;
}

double Bisect(double xl, double xu, double es, int imax)
{
	FILE* fp = _fsopen("Bisection.out", "w", _SH_DENYNO);
	printf(" Bisection Method \n");

	double fl, fr, xr = xl, xrold, ea, test;
	int iter = 0;
	fl = function(xl);
	do
	{
		xrold = xr;
		xr = (xl + xu) / 2.;
		fr = function(xr);
		iter++;
		if (xr != 0.) ea = fabs((xr - xrold) / xr) * 100.;
		test = fl * fr;
		if (test < 0.) xu = xr;
		else if (test > 0.) { xl = xr; fl = fr; }
		else ea = 0.;
		fprintf(fp, " %4d  %15.7e  %15.7e %15.7e \n", iter, xr, fr, ea);
		printf(" iter= %4d  xr= %15.7e  fr= %15.7e error= %15.7e \n", iter, xr, fr, ea);
	} while (!(ea < es || iter >= imax));
	fclose(fp);

	return xr;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
