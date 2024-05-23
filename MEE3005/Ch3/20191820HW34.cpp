// 20191820HW34.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 20191820HW33.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// GE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

#define MaxDim 100

void Gseid(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim], int imax, double es);

int main()
{
	int imax = 1000; double es = 1.e-5;
	double a[MaxDim][MaxDim], b[MaxDim], x[MaxDim];

	int n = 4;
	a[1][1] = 3.0;	a[1][2] = -0.1;	a[1][3] = -0.2; a[1][4] = 0.2; b[1] = 8.25;
	a[2][1] = 0.1;	a[2][2] = 7.0;	a[2][3] = -0.3;	a[2][4] = 0.5; b[2] = -18.3;
	a[3][1] = 0.3;	a[3][2] = -0.2;	a[3][3] = 10.;  a[3][4] = 20.; b[3] = 111.4;
	a[4][1] = 0.2;	a[4][2] = 0.2;	a[4][3] = 0.2;  a[4][4] = 1.0; b[4] = 9.5;
	for (int i = 1; i <= n; i++) x[i] = 0;


	double as[MaxDim][MaxDim], bs[MaxDim];
	int i, j;
	for (i = 1; i <= n; i++) {
		bs[i] = b[i];
		for (j = 1; j <= n; j++) as[i][j] = a[i][j];
	}

	printf(" Gauss-Seidel \n");
	printf(" A & b \n");
	for (i = 1; i <= n; i++) {
		printf(" %15.7e %15.7e %15.7e %15.7e %15.7e \n", a[i][1], a[i][2], a[i][3], a[i][4], b[i]);
	}

	Gseid(n, a, b, x, imax, es);
	printf(" x after Gauss-Seidel \n");
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

void Gseid(int n, double a[MaxDim][MaxDim], double b[MaxDim], double x[MaxDim], int imax, double es)
{
	int i, j; double sum; double lambda = 1.;

	for (i = 1; i <= n; i++)
	{
		double  dummy = a[i][i];
		for (j = 1; j <= n; j++)
		{
			a[i][j] = a[i][j] / dummy;
		}
		b[i] = b[i] / dummy;
	}
	
	for (i = 1; i <= n; i++)
	{
		sum = b[i];
		for (j = 1; j <= n; j++)
			if (i != j) sum = sum - a[i][j] * x[j];
		x[i] = sum;
	}
	
	int iter = 1;
	do {
		int check = 1;
		for (i = 1; i <= n; i++)
		{
			double old = x[i];
			sum = b[i];
			for (j = 1; j <= n; j++)
				if (i != j) sum = sum - a[i][j] * x[j];
			x[i] = lambda * sum + (1. - lambda) * old;
			if (check == 1 && x[i] != 0.) 
			{
				double ea = fabs((x[i] - old) / x[i]) * 100.;
				if (ea > es) check = 0;
			}
		}
		printf("%6d %15.7e %15.7e %15.7e %15.7e \n",iter, x[1], x[2], x[3], x[4]);
		iter++;
		if (check == 1 || iter >= imax) break;
	} while (1);


}

