// 20191820HW31.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// GE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100

void Eliminate(int n, double a[MaxDim][MaxDim], double b[MaxDim]);
void Substitute(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim]);

int main()
{
	double a[MaxDim][MaxDim], b[MaxDim], x[MaxDim];

	int n = 4;
	a[1][1] = 3.0;	a[1][2] = -0.1;	a[1][3] = -0.2; a[1][4] = 0.2; b[1] = 8.25;
	a[2][1] = 0.1;	a[2][2] = 7.0;	a[2][3] = -0.3;	a[2][4] = 0.5; b[2] = -18.3;
	a[3][1] = 0.3;	a[3][2] = -0.2;	a[3][3] = 10.;  a[3][4] = 20.; b[3] = 111.4;
	a[4][1] = 0.2;	a[4][2] = 0.2;	a[4][3] = 0.2;  a[4][4] = 1.0; b[4] = 9.5;

	double as[MaxDim][MaxDim], bs[MaxDim];
	int i, j;
	for (i = 1; i <= n; i++) {
		bs[i] = b[i];
		for (j = 1; j <= n; j++) as[i][j] = a[i][j];
	}

	printf(" Gauss Elimination \n");
	printf(" A & b \n");
	for (i = 1; i <= n; i++) {
		printf(" %15.7e %15.7e %15.7e %15.7e %15.7e \n", a[i][1], a[i][2], a[i][3], a[i][4], b[i]);
	}

	Eliminate(n, a, b);
	printf(" A & b after Forward Elimination \n");
	for (i = 1; i <= n; i++) {
		printf(" %15.7e %15.7e %15.7e %15.7e %15.7e \n", a[i][1], a[i][2], a[i][3], a[i][4], b[i]);
	}

	Substitute(n, a, b, x);
	printf(" x after Back Substitution \n");
	printf(" %15.7e %15.7e %15.7e %15.7e \n", x[1], x[2], x[3], x[4]);

	printf(" check original equations \n");
	for (i = 1; i <= n; i++) {
		double sum = 0.;
		for (int j = 1; j <= n; j++)  sum += as[i][j] * x[j];
		sum -= bs[i];
		printf(" Eq. %2d: %15.7e \n", i, sum);
	}


	return 0;
}

void Eliminate(int n, double a[MaxDim][MaxDim], double b[MaxDim])
{
	int i, j, k; double factor;

	for (k = 1; k <= n - 1; k++) {
		for (i = k + 1; i <= n; i++) {
			factor = a[i][k] / a[k][k];
			for (j = k; j <= n; j++) a[i][j] -= factor * a[k][j]; // j = k 일때 elimination이 적용된 부분에 0을 채움
			b[i] -= factor * b[k];
		}
	}
}

void Substitute(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim])
{
	int i, j; double sum;

	x[n] = b[n] / a[n][n];
	for (i = n - 1; i >= 1; i--) {
		sum = 0.;
		for (j = i + 1; j <= n; j++) sum += a[i][j] * x[j];
		x[i] = (b[i] - sum) / a[i][i];
	}
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
