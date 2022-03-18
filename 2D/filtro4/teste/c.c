#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	int i, j;
	double *phi;
	int Nx, Ny;
	Nx= Ny= 250;
	FILE *arquivo;

	phi= (double *) calloc(Nx*Ny, sizeof(double));	

	arquivo= fopen("g.dat", "w");	
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			if (sqrt((i-Nx/2)*(i-Nx/2)+(j-Ny/2)*(j-Ny/2)) < 4){
				phi[i*Nx+j]= 1.0;
			}else{
				phi[i*Nx+j]= 0.0;
			}
			fprintf(arquivo, "%e ", phi[i*Nx+j]);
		}
		fprintf(arquivo, "\n");
	}
 
	free(phi);

	return 0;
}
