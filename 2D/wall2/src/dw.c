#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>

#define Nx   250
#define Ny   250
#define dt   0.01 
#define alfa 3.0
#define tf   1000.0   

double f(double *A, int x, int y, double *phi, double t){
	int xp1, xm1, yp1, ym1;
	xp1= (x+1)%Nx;
	xm1= (x-1+Nx)%Nx;
	yp1= (y+1)%Ny;
	ym1= (y-1+Ny)%Ny;
	return ((phi[xp1*Ny+y]+phi[xm1*Ny+y]+phi[x*Ny+yp1]+phi[x*Ny+ym1]-4.0*phi[x*Ny+y])-(alfa*2.0*A[x*Ny+y]/t)-(0.79*(pow(phi[x*Ny+y],3)-phi[x*Ny+y])));
}

void op(int n, double *phi){
	int x, y, a;
	FILE *file;
	char name[100];
	sprintf(name, "dat/phi-%d.dat", n);
	file= fopen(name, "w");
	for(x= 0; x< Nx; x++){
		for(y= 0; y< Ny; y++){
			fprintf(file, "%.0g ", phi[x*Ny+y]); 
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

int main(int argc, char **argv){
	int x, y, b, n;
	double *phi, *phi_temp, *A, *A_temp;

	phi= 		 (double *) calloc(Nx*Ny, sizeof(double));
	phi_temp= (double *) calloc(Nx*Ny, sizeof(double));
	A= 		 (double *) calloc(Nx*Ny, sizeof(double));
	A_temp= 	 (double *) calloc(Nx*Ny, sizeof(double));

	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

//condição inicial - começo
	for(x= 0; x< Nx; x++){
		for(y= 0; y< Ny; y++){
			A[x*Ny+y]= 0.0;
			b= gsl_rng_uniform(w)*2;
			switch(b){
					case 0:
						phi[x*Ny+y]= -1.0;
					break;
					default:
						phi[x*Ny+y]= 1.0;
			}
		}
	}	
//condição inicial - fim

	op(0, phi);

//solução - começo
	double t;
	for (t = 1.0; t < tf; t += 0.01){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				A_temp[x*Ny+y]= A[x*Ny+y]+0.5*dt*(f(A, x, y, phi, t));
				phi_temp[x*Ny+y]= phi[x*Ny+y]+0.5*dt*A[x*Ny+y];		
			}
		}
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				A[x*Ny+y]+= dt*(f(A_temp, x, y, phi_temp, t+0.5*dt));
				phi[x*Ny+y]+= dt*A_temp[x*Ny+y];			
			}
		}
		n= ((t-1)/dt)+1;
		if ((n%100) == 0){
			op(n, phi);	
		}
//printf("%e\n", t);
	}
//solução - fim

	gsl_rng_free(w);
	free(phi);
	free(phi_temp);
	free(A);
	free(A_temp);
	return 0;
}
