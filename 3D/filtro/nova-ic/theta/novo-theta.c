#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Nx   100
#define Ny   100
#define Nz   100 

void theta(int n, double *theta){
	int x, y, z;
	FILE *file;
	char name[100];
	sprintf(name, "theta-%d.dat", n);
	file= fopen(name, "w");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%e \n", theta[Ny*(Nx*z+x)+y]); 
			}
		}
	}
	fclose(file);
}

int main(int argc, char **argv){
	int x, y, z;
	double *theta1, *theta2, *phi1, *phi2;
	FILE *file;

	theta1= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	theta2= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi1=   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2=   (double *) calloc(Nx*Ny*Nz, sizeof(double));

//condição inicial - começo
	file = fopen(argv[1], "r");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fscanf(file, "%lf ", &phi1[Ny*(Nx*z+x)+y]); 
			}
		}
	}	
	fclose(file);
	
	file = fopen(argv[2], "r");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fscanf(file, "%lf ", &phi2[Ny*(Nx*z+x)+y]); 
			}
		}
	}	
	fclose(file);
//condição inicial - fim
	for (z = 0; z< Nz; z++){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				theta1[Ny*(Nx*z+x)+y]= acos(phi1[Ny*(Nx*z+x)+y]);
				theta2[Ny*(Nx*z+x)+y]= asin(phi2[Ny*(Nx*z+x)+y]);
			}
		}
	}
	for (z = 0; z < Nz; z += 1){
		for (x = 0; x < Nx; x += 1){
			for (y = 0; y < Ny; y += 1){
				if (theta1[Ny*(Nx*z+x)+y] != theta2[Ny*(Nx*z+x)+y] && theta2[Ny*(Nx*z+x)+y] < 0.0){
					theta1[Ny*(Nx*z+x)+y]= 2*M_PI-theta1[Ny*(Nx*z+x)+y];	
				}
			}
		}
	}
	
	theta(0, theta1); 	

	free(theta1);
	free(theta2);
	free(phi1);
	free(phi2);
	return 0;
}
