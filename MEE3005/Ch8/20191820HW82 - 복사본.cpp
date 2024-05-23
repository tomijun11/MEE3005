// ST-GS1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <share.h>

#define ID 101
#define JD 101

void Gauss_Seidel(int ibeg, int iend, int jbeg, int jend, int maxiter, double maxerr, double lambda,double dy, double T[ID][JD]);
void Plot_Contour(FILE* fp, double T0, int ibeg, int iend, int jbeg, int jend, double x[ID], double y[JD], double T[ID][JD]);
void printAll(double T[ID][JD], int n);

int main(void)
{
	double x[ID], y[JD];
	double T[ID][JD];

	int m, n, i, j;
	int maxiter = 10000;
	//double maxerr=1.e-2, lambda=1.5;
	double maxerr = 1.e-5, lambda = 1.0;
	//	
	//	(x,y)-nodes: (0,1...m,m+1), (0,1...n,n+1)
	m = 9; n = 9;
	//
	// initialize
	double dx = 1. / float(m + 1);
	double dy = 1. / float(n + 1);
	for (i = 0; i <= m + 1; i++) x[i] = i * dx;
	for (j = 0; j <= n + 1; j++) y[j] = j * dy;

	for (j = 0; j <= n + 1; j++) {
		for (i = 0; i <= m + 1; i++) T[i][j] = 0.;
	}
	//
	// boundary conditions
	for (i = 0; i <= m + 1; i++) { T[i][0] = 0.;  T[i][n + 1] = 100.; } // y=0, y=n	
	for (j = 0; j <= n + 1; j++) { T[0][j] = 75.;  T[m + 1][j] = 50.; } // x=0, x=n
	//
	// solver
	Gauss_Seidel(1, m, 0, n, maxiter, maxerr, lambda, dy, T);
	//
	for (j = n; j > 0; j--) {
		printf("  %9.5f, %9.5f %9.5f \n", T[1][j], T[2][j], T[3][j]);
	}
	//printAll(T, 9);


	FILE* fp = _fsopen("data", "w", _SH_DENYNO);
	for (i = 0; i <= m + 1; i++) {
		for (j = 0; j <= n + 1; j++) {
			fprintf(fp, "  %9.5f %9.5f %9.5f \n", x[i], y[j], T[i][j]);
		}
		fprintf(fp, "  \n");
	}
	fclose(fp);

	FILE* fp1 = _fsopen("cont", "w", _SH_DENYNO);
	Plot_Contour(fp1, 60.0, 0, m + 1, 0, n + 1, x, y, T);
	Plot_Contour(fp1, 70.0, 0, m + 1, 0, n + 1, x, y, T);
	Plot_Contour(fp1, 80.0, 0, m + 1, 0, n + 1, x, y, T);
	Plot_Contour(fp1, 90.0, 0, m + 1, 0, n + 1, x, y, T);
	fclose(fp1);

	return 0;
}

void printAll(double T[ID][JD], int n)
{
	for (int j = n; j > 0; j--) {
		for (int i = 1; i <= n; i++)
			if (i == n)
				printf("%9.5f\n", T[i][j]);
			else
				printf("%9.5f  ", T[i][j]);
	}
	printf("\n");

}
void Gauss_Seidel(int ibeg, int iend, int jbeg, int jend, int maxiter, double maxerr, double lambda, double dy, double T[ID][JD])
{
	int iter = 0; double error;
	int i, j;
	do {
		iter++; error = 0.;
		for (j = jbeg; j <= jend; j++) {
			for (i = ibeg; i <= iend; i++) {
				double Told = T[i][j];
				double Tnew;
				if (j == jbeg) // j = 0 
				{
					double Ts = T[i][j + 1] - 2. * dy;
					Tnew = (T[i - 1][j] + T[i + 1][j] + Ts + T[i][j + 1]) / 4.; // dT/dy[i][0] = 1 
				}
				else {
					Tnew = (T[i - 1][j] + T[i + 1][j] + T[i][j - 1] + T[i][j + 1]) / 4.;
				}
				Tnew = T[i][j] = lambda * Tnew + (1. - lambda) * Told;
				error = __max(error, fabs((T[i][j] - Told) / T[i][j]));
			}
		}
		printf(" iter=%4d T[1][1]=%9.5f T[2][2]=%9.5f maxerr=%9.3e \n", iter, T[1][1], T[2][2], error);

	} while ((iter < maxiter) && (error > maxerr));
}

void Plot_Contour(FILE* fp, double T0, int ibeg, int iend, int jbeg, int jend, double x[ID], double y[JD], double T[ID][JD])
{
	int i0, j0, i1, j1, n;
	double x1[4], y1[4], DT00, DT10, DT11, DT01;
	for (j0 = jbeg; j0 < jend; j0++) {
		for (i0 = ibeg; i0 < iend; i0++) {
			j1 = j0 + 1; i1 = i0 + 1; n = -1;
			DT00 = T0 - T[i0][j0]; DT10 = T0 - T[i1][j0];
			DT11 = T0 - T[i1][j1]; DT01 = T0 - T[i0][j1];

			if ((DT00 * DT10 <= 0.) && (DT00 != DT10)) {
				n++; x1[n] = x[i0] + DT00 / (DT00 - DT10) * (x[i1] - x[i0]); y1[n] = y[j0];
			}

			if ((DT10 * DT11 <= 0.) && (DT10 != DT11)) {
				n++; x1[n] = x[i1]; y1[n] = y[j0] + DT10 / (DT10 - DT11) * (y[j1] - y[j0]);
			}

			if ((DT11 * DT01 <= 0.) && (DT11 != DT01)) {
				n++; x1[n] = x[i0] + DT01 / (DT01 - DT11) * (x[i1] - x[i0]); y1[n] = y[j1];
			}

			if ((DT01 * DT00 <= 0.) && (DT01 != DT00)) {
				n++; x1[n] = x[i0]; y1[n] = y[j0] + DT00 / (DT00 - DT01) * (y[j1] - y[j0]);
			}

			if (n >= 1) {
				for (int nn = 0; nn < n; nn++) {
					fprintf(fp, "  %9.5f %9.5f \n", x1[nn], y1[nn]);
					fprintf(fp, "  %9.5f %9.5f \n \n", x1[nn + 1], y1[nn + 1]);
				}
				if (n != 1) {
					fprintf(fp, "  %9.5f %9.5f \n", x1[n], y1[n]);
					fprintf(fp, "  %9.5f %9.5f \n \n", x1[0], y1[0]);
				}
			}
		}
	}
}
