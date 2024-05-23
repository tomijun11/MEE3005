// 20191820HW41.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100
double interpolation(int n, double x[MaxDim], double y[MaxDim], double x0);

int main()
{
	double x[MaxDim], y[MaxDim];
	int n = 10; // n=order
	int i; // x = -1~1

	for (i = 0; i <= n; i++)
	{
		x[i] = -1. + (2. * i) / (n + 0.);
		//y[i] = exp(x[i] * x[i]);
		y[i] = 1. / (1. + 25. * x[i] * x[i]);
	}

	double xx[MaxDim];
	for (i = 0; i <= 50; i++)
	{
		xx[i] = -1. + (2. * i) / (50 + 0.);
	}

	FILE* fp = _fsopen("out", "w", _SH_DENYNO);
	double x0, y0;

	for (i = 0; i <= 50; i++)
	{	
		x0 = xx[i]; y0 = interpolation(n, x, y, xx[i]);
		printf("x=%15.7e y=%15.7e \n", x0, y0);
		fprintf(fp," %15.7e %15.7e \n", x0, y0);
	}

	fclose(fp);
	return 0;
}

double interpolation(int n, double x[MaxDim], double y[MaxDim], double x0)
{
	

	double sum = 0.;
	int i, j;
	for (i = 0; i < n + 1; i++)
	{
		double product = y[i];
		for (j = 0; j < n + 1; j++)
		{
			if (i != j) product *= (x0 - x[j]) / (x[i] - x[j]);
		}
		sum += product;
	}

	return sum;
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
