#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 250
#define Ny 250

int main(int argc, char **argv){
	int x, y, i, a;
	int *comp;
	double *phi, *phi1;
	double **phi2; 
	char nome[100];
	FILE *file;
	
	a= atoi(argv[2]);
	
	phi=  (double *) calloc(a, sizeof(double));
	phi1= (double *) calloc(Nx*Ny, sizeof(double));
	comp=  (int *) calloc(a, sizeof(int));
	
	phi2= (double **) calloc(Nx*Ny, sizeof(double *));
	for (i= 0; i < Nx*Ny; i+= 1){
  		phi2[i] = (double *) calloc(a, sizeof(double ));
	}

	for (i = 0; i < a; i += 1){
		comp[i]= 0;
	}
//condição inicial - começo
	file = fopen(argv[1], "r");	
	for(x= 0; x< Nx; x++){
		for(y= 0; y< Ny; y++){
   		fscanf(file, "%lf ", &phi1[x*Ny+y]);
		}
	}	
	fclose(file);
	
	for (i= 0; i < a; i += 1){
		sprintf(nome, "evolucao1/phi-%d.dat", i+1);	
		file= fopen(nome, "r");
		for (x = 0; x < Nx; x += 1){
			for (y = 0; y < Ny; y += 1){
				fscanf(file, "%lf ", &phi2[x*Ny+y][i]);
			}
		}
		fclose(file);
	}
//condição inicial - fim
	
//comparação - começo
	for (i = 0; i < a; i += 1){
		for (x = 0; x < Nx; x += 1){
			for (y = 0; y < Ny; y += 1){
				if (phi1[x*Ny+y] > 0.0 && phi2[x*Ny+y][i] > 0.0){
					comp[i]++;
				}	
				if (phi1[x*Ny+y] < 0.0 && phi2[x*Ny+y][i] < 0.0){
					comp[i]++;	
				}
			}
		}
	}
	
//comparação - fim
//impressão ????	
	file= fopen("evolucao1/comp/comp.dat", "w");
	for(i= 0; i< a; i++){
		fprintf(file, "%d \n", comp[i]); 
	}
	fclose(file);
	
	for (i = 0; i < Nx*Ny; i += 1){
		free(phi2[i]);
	}

	free(phi);
	free(phi1);
	return 0;
}
