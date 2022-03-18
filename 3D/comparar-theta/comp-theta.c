#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 100
#define Ny 100
#define Nz 100

int main(int argc, char **argv){
	int x, y, z, i, a;
	double *theta, *theta1, *theta_teste;
	double **theta2; 
	char nome[100];
	FILE *file;

	a= atoi(argv[2]);
	
	theta=  	   (double *) calloc(a, sizeof(double));
	theta1= 	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	theta_teste= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	
	theta2= (double **) calloc(Nx*Ny*Nz, sizeof(double *));
	for (i= 0; i < Nx*Ny*Nz; i+= 1){
  		theta2[i] = (double *) calloc(a, sizeof(double ));
	}

//condição inicial - começo
	file = fopen(argv[1], "r");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
   			fscanf(file, "%lf ", &theta1[Ny*(Nx*z+x)+y]);
			}
		}
	}	
	fclose(file);
	
	for (i= 0; i < a; i += 1){
		sprintf(nome, "evolucao1/theta-%d.dat", i+1);	
		file= fopen(nome, "r");
		for (z = 0; z < Nz; z += 1){
			for (x = 0; x < Nx; x += 1){
				for (y = 0; y < Ny; y += 1){
					fscanf(file, "%lf ", &theta2[Ny*(Nx*z+x)+y][i]);
				}
			}
		}
		fclose(file);
	}
//condição inicial - fim

	
//comparação - começo
	for (i = 0; i < a; i += 1){
		for (z = 0; z < Nz; z += 1){
			for (x = 0; x < Nx; x += 1){
				for (y = 0; y < Ny; y += 1){
					if (theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i] > M_PI){
						theta[i]+= (theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i]-2.0*M_PI)*(theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i]-2.0*M_PI);
					}else{
						if (theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i] < -M_PI){
							theta[i]+= (theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i]+2.0*M_PI)*(theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i]+2.0*M_PI);
						}else{
							theta[i]+= (theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i])*(theta1[Ny*(Nx*z+x)+y]-theta2[Ny*(Nx*z+x)+y][i]);
						}
					}	
				}
			}
		}
	}
	for (i = 0; i < a; i += 1){
		theta[i]/= Nx*Ny*Nz; 
	}	
//comparação - fim

//impressão da media da menor diferença de thetas	
	file= fopen("evolucao1/diff-theta/diff-theta.dat", "w");
	for(i= 0; i< a; i++){
		fprintf(file, "%e \n", theta[i]); 
	}
	fclose(file);
	
	for (i = 0; i < Nx*Ny*Nz; i += 1){
		free(theta2[i]);
	}

	free(theta);
	free(theta1);
	free(theta_teste);
	return 0;
}
