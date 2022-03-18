#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 100
#define Ny 100
#define Nz 100

int main(int argc, char **argv){
	int j, i, a, menor_j;
	double menor;
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
		sprintf(nome, "evolucao1/diff-theta/diff-theta-%d.dat", i+1);	
		file= fopen(nome, "r");
		for (j = 0; j < 99; j += 1){
			fscanf(file, "%lf ", &theta2[j][i]);
		}
		fclose(file);
	}
	

//condição inicial - fim

//impressão da media da menor diferença de thetas	
	for (i = 0; i < a; i += 1){ 
		menor= 100.0;
		for (j = 0; j < 99; j += 1){
			if (theta2[j][i] < menor){
				menor= theta2[j][i];
				menor_j= j;
			}	
		}
		file= fopen("menor1.dat", "a");
		fprintf(file, "%e %d\n", menor, menor_j+1); 
		fclose(file);
	}

	
	for (i = 0; i < 99; i += 1){
		free(theta2[i]);
	}
	return 0;
}
