#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	int i, j, k;
	double *phi;
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;
	FILE *arquivo;

	phi= (double *) calloc(Nx*Ny*Nz, sizeof(double));	

	arquivo= fopen("g.dat", "w");	
//	fprintf(arquivo, "x,y,z,P\n");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				if (sqrt((i-Nx/2)*(i-Nx/2)+(j-Ny/2)*(j-Ny/2)+(k-Nz/2)*(k-Nz/2)) < 10){
					phi[Ny*(Nx*k+i)+j]= 1.0;
				}else{
					phi[Ny*(Nx*k+i)+j]= 0.0;
				}
//				fprintf(arquivo, "%d,%d,%d,%e\n", j, i, k, phi[Ny*(Nx*k+i)+j]);
				fprintf(arquivo, "%e\n", phi[Ny*(Nx*k+i)+j]);
			}
		}
	}
	free(phi);

	return 0;
}
