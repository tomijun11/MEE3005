// 20191820HW32.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 20191820HW31.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// GE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100

void Decompose(int n, double a[MaxDim][MaxDim]);
void Substitute(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim]);

int main()
{
	double a[MaxDim][MaxDim], b[MaxDim], x[MaxDim];

	int n = 4;
	a[1][1] = 3.0;	a[1][2] = -0.1;	a[1][3] = -0.2; a[1][4] = 0.2; b[1] = 8.25;
	a[2][1] = 0.1;	a[2][2] = 7.0;	a[2][3] = -0.3;	a[2][4] = 0.5; b[2] = -18.3;
	a[3][1] = 0.3;	a[3][2] = -0.2;	a[3][3] = 10.;  a[3][4] = 20.; b[3] = 111.4;
	a[4][1] = 1.0;	a[4][2] = 1.0;	a[4][3] = 1.0;  a[4][4] = 1.0; b[4] = 9.5;
	//a[4][1] = 0.2;	a[4][2] = 0.2;	a[4][3] = 0.2;  a[4][4] = 1.0; b[4] = 9.5;

	double as[MaxDim][MaxDim], bs[MaxDim];
	int i, j;
	for (i = 1; i <= n; i++) {
		bs[i] = b[i];
		for (j = 1; j <= n; j++) as[i][j] = a[i][j];
	}

	printf(" LU Decompose \n");
	printf(" A & b \n");
	for (i = 1; i <= n; i++) {
		printf(" %15.7e %15.7e %15.7e %15.7e %15.7e \n", a[i][1], a[i][2], a[i][3], a[i][4], b[i]);
	}

	Decompose(n, a);
	printf(" A & b after LU Decomposition \n");
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

void Decompose(int n, double a[MaxDim][MaxDim]) // A -> LU
{
	int i, j, k; double factor;

	for (k = 1; k <= n - 1; k++) {
		for (i = k + 1; i <= n; i++) {
			factor = a[i][k] / a[k][k];
			a[i][k] = factor;
			for (j = k+1; j <= n; j++) a[i][j] -= factor * a[k][j]; // j = k 일때 elimination이 적용된 부분에 0을 채움
		}
	}
}

void Substitute(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim]) 
{
	int i, j; double sum;

	for (i = 2; i <= n; i++)
	{
		sum = b[i];
		for (j = 1; j <= i - 1; j++) sum -= a[i][j] * b[j];
		b[i] = sum;
	}

	x[n] = b[n] / a[n][n];
	for (i = n - 1; i >= 1; i--) {
		sum = 0.;
		for (j = i + 1; j <= n; j++) sum += a[i][j] * x[j];
		x[i] = (b[i] - sum) / a[i][i];
	}
}


