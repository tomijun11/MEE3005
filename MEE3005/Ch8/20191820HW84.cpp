// PDE.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <share.h>

#define ID 100
void Tridiag(int n, double lambda, double Told[ID], double T[ID], double e[ID], double f[ID], double g[ID], double r[ID]);
void ThomasEliminate(int n, double e[ID], double f[ID], double g[ID], double b[ID], double x[ID]);

int main()
{
	double x[ID], T[ID], Told[ID];
	//	double k=0.835, Tinit=0., timef=12; //timef=12.; 
	double k = 0.835, Tinit = 0., timef = 400.; //timef=12.; 

												//	double dx=2., dt=0.1, lambda=k*dt/dx/dx;
	int n = 20; // n=# of segments
	double dx = 10. / (n + 0.), dt = 10., lambda = k * dt / dx / dx;
	int i, itime = 0, jump = 1; //jump=30;
	for (i = 0; i <= n; i++) { x[i] = i * dx; T[i] = Tinit; }
	T[0] = 0.; T[n] = 50.; // T[0] = Tinit

	double time = 0.;
	FILE* fp = _fsopen("output", "w", _SH_DENYNO);
	for (i = 0; i <= n; i++) fprintf(fp, "%10.5f %10.5f %10.5f \n", time, x[i], T[i]); fprintf(fp, " \n");
	for (i = 0; i <= n; i++) printf("%10.5f %10.5f %10.5f \n", time, x[i], T[i]); printf(" \n");

	double e[ID], f[ID], g[ID], r[ID];

	do {
		time = time + dt; itime++;
		for (i = 0; i <= n; i++) Told[i] = T[i];
		T[n] = 50.; // BC T�� ������� �׻� ����

		Tridiag(n, lambda, Told, T, e, f, g, r);
		ThomasEliminate(n, e, f, g, r, T);

		if (itime == itime / jump * jump) {
			for (i = 0; i <= n; i++) fprintf(fp, "%10.5f %10.5f %10.5f \n", time, x[i], T[i]); fprintf(fp, " \n");
			for (i = 0; i <= n; i++) printf("%10.5f %10.5f %10.5f \n", time, x[i], T[i]); printf(" \n");
		}
	} while (time < timef - 0.1 * dt);

	return 0;
}

void Tridiag(int n, double lambda, double Told[ID], double T[ID], double e[ID], double f[ID], double g[ID], double r[ID])
{
	int i;
	e[0] = 0.; f[0] = (1. + 2. * lambda); g[0] = -2. * lambda; r[0] = Told[0]; // T[1]-T[-1]/2dx = DT/DX[0], T[-1] = T[1]
	e[n] = 0.; f[n] = 1.; g[n] = 0.; r[n] = T[n];

	for (i = 1; i <= n - 1; i++) {
		e[i] = -lambda;
		f[i] = (1. + 2. * lambda);
		g[i] = -lambda;
		r[i] = Told[i];
	}
}

void ThomasEliminate(int n, double e[ID], double f[ID], double g[ID], double b[ID], double x[ID])
{
	int i;

	double E[ID], F[ID], G[ID];
	for (i = 0; i <= n; i++) {
		x[i] = b[i]; E[i] = e[i]; F[i] = f[i]; G[i] = g[i];
	}

	for (i = 1; i <= n; i++) {
		E[i] = E[i] / F[i - 1]; F[i] = F[i] - E[i] * G[i - 1]; x[i] = x[i] - E[i] * x[i - 1];
	}
	x[n] = x[n] / F[n];
	for (i = n - 1; i >= 0; i--) x[i] = (x[i] - G[i] * x[i + 1]) / F[i];
}
