#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 250
#define Ny 250

int main(int argc, char **argv){
	int j, i, a, maior, maior_j;
	double **theta2; 
	char nome[100];
	FILE *file;

	a= atoi(argv[1]);
	
	theta2= (double **) calloc(99, sizeof(double *));
	
	for (i= 0; i < 99; i+= 1){
  		theta2[i] = (double *) calloc(a, sizeof(double ));
	}

//condição inicial - começo	
	for (i= 0; i < a; i += 1){
		sprintf(nome, "evolucao1/comp/comp-%d.dat", i+1);	
		file= fopen(nome, "r");
		for (j = 0; j < 99; j += 1){
			fscanf(file, "%lf ", &theta2[j][i]);
		}
		fclose(file);
	}
//condição inicial - fim

//impressão da media da menor diferença de thetas	
	for (i = 0; i < a; i += 1){ 
		maior= 1;
		for (j = 0; j < 99; j += 1){
			if (theta2[j][i] > maior){
				maior= theta2[j][i];
				maior_j= j;
			}	
		}
		file= fopen("maior1.dat", "a");
		fprintf(file, "%e %d\n", 1.0*maior/(250.0*250.0), maior_j+1); 
		fclose(file);
	}

	
	for (i = 0; i < 99; i += 1){
		free(theta2[i]);
	}
	return 0;
}
