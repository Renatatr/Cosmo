#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void op1(int t, double *phi1){
	int i, j, k;
	char nome[100];
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;
	FILE *arq;
	sprintf(nome, "ic1-%d.dat", t);
	arq= fopen(nome, "w");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				fprintf(arq, "%e \n", phi1[Ny*(Nx*k+i)+j]);
			}
		}
	}
	fclose(arq);
}

void op2(int t, double *phi2){
	int i, j, k;
	char nome[100];
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;
	FILE *arq;
	
	sprintf(nome, "ic2-%d.dat", t);
	arq= fopen(nome, "w");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				fprintf(arq, "%e \n", phi2[Ny*(Nx*k+i)+j]);
			}
		}
	}
	fclose(arq);
}

int main(int argc, char **argv){
	int i, j, k;
	double *phi1, *phi2, *phi1_final, *phi2_final ;
	FILE *file;
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;

  /* Alocação de memória */
	phi1= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2= (double *) calloc(Nx*Ny*Nz, sizeof(double));	
	phi1_final= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2_final= (double *) calloc(Nx*Ny*Nz, sizeof(double));
  /* condição inicial1 - começo */
	file = fopen(argv[1], "r");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
   			fscanf(file, "%lf", &phi1[Ny*(Nx*k+i)+j]);
			}
		}
	}	
	fclose(file);
	file = fopen(argv[2], "r");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
   			fscanf(file, "%lf", &phi2[Ny*(Nx*k+i)+j]);
			}
		}
	}	
	fclose(file);
  /* imprimir a condição inicial */
//	op1(0, phi1);
//	op2(0, phi2);
  /* condição inicial1 - fim */	

  /* Normalização */
  	for (k = 0; k < Nz; k += 1){			
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				phi1_final[Ny*(Nx*k+i)+j]= (phi1[Ny*(Nx*k+i)+j])/(sqrt(phi1[Ny*(Nx*k+i)+j]*phi1[Ny*(Nx*k+i)+j]+phi2[Ny*(Nx*k+i)+j]*phi2[Ny*(Nx*k+i)+j]));
				phi2_final[Ny*(Nx*k+i)+j]= (phi2[Ny*(Nx*k+i)+j])/(sqrt(phi1[Ny*(Nx*k+i)+j]*phi1[Ny*(Nx*k+i)+j]+phi2[Ny*(Nx*k+i)+j]*phi2[Ny*(Nx*k+i)+j]));
			}
		}
	}

  /* printa os valores */
	op1(0, phi1_final);
	op2(0, phi2_final);

  /* Libera memória */
	free(phi1);
	free(phi2);

	return 0;
}
