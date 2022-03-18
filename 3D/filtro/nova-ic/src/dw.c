#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Nx   100
#define Ny   100
#define Nz   100
#define V0   0.013   
#define phi0 1.0 

void op(int n, double *phi){
	int x, y, z;
	FILE *file;
	char name[100];
	sprintf(name, "dat/phi1-%d.dat", n);
	file= fopen(name, "w");
	fprintf(file, "x,y,z,P\n"); 
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%d,%d,%d,%e \n", x, y, z, phi[Ny*(Nx*z+x)+y]);
			}
		}
	}
	fclose(file);
}

int main(int argc, char **argv){
	int x, y, z;
	int xp1, xm1, yp1, ym1, zm1, zp1;
	double *phi, *grad1x, *grad2x, *grad1y, *grad2y, *grad1z, *grad2z, *phi1, *phi2;
	FILE *file;

	phi=    (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1x= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2x= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1y= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2y= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1z= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2z= (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi1=   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2=   (double *) calloc(Nx*Ny*Nz, sizeof(double));

//condição inicial - começo
	file = fopen(argv[1], "r");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
	   		fscanf(file, "%lf", &phi1[Ny*(Nx*z+x)+y]);
			}
		}
	}	
	fclose(file);
	
	file = fopen(argv[2], "r");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
   			fscanf(file, "%lf", &phi2[Ny*(Nx*z+x)+y]);
			}
		}
	}	
	fclose(file);
//condição inicial - fim

/*	for(x= 0; x< Nx; x++){
		for(y= 0; y< Ny; y++){
			phi[x*Ny+y]= (phi1[x*Ny+y]+phi2[x*Ny+y])/(sqrt(phi1[x*Ny+y]*phi1[x*Ny+y]+phi2[x*Ny+y]*phi2[x*Ny+y]));
		}
	}	
*/
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				xp1= (x+1)%Nx;
				xm1= (x-1+Nx)%Nx;
				yp1= (y+1)%Ny;
				ym1= (y-1+Ny)%Ny;
				zp1= (z+1)%Nz;
				zm1= (z-1+Nz)%Nz;
				grad1x[Ny*(Nx*z+x)+y]= (phi1[Ny*(Nx*z+xp1)+y]+phi1[Ny*(Nx*z+xm1)+y])*0.5;
				grad1y[Ny*(Nx*z+x)+y]= (phi1[Ny*(Nx*z+x)+yp1]+phi1[Ny*(Nx*z+x)+ym1])*0.5;
				grad1z[Ny*(Nx*z+x)+y]= (phi1[Ny*(Nx*zp1+x)+y]+phi1[Ny*(Nx*zm1+x)+y])*0.5;
				grad2x[Ny*(Nx*z+x)+y]= (phi2[Ny*(Nx*z+xp1)+y]+phi2[Ny*(Nx*z+xm1)+y])*0.5;
				grad2y[Ny*(Nx*z+x)+y]= (phi2[Ny*(Nx*z+x)+yp1]+phi2[Ny*(Nx*z+x)+ym1])*0.5;
				grad2z[Ny*(Nx*z+x)+y]= (phi2[Ny*(Nx*zp1+x)+y]+phi2[Ny*(Nx*zm1+x)+y])*0.5;
				phi[Ny*(Nx*z+x)+y]= grad1x[Ny*(Nx*z+x)+y]*grad1x[Ny*(Nx*z+x)+y]+grad1y[Ny*(Nx*z+x)+y]*grad1y[Ny*(Nx*z+x)+y]+grad1z[Ny*(Nx*z+x)+y]*grad1z[Ny*(Nx*z+x)+y]+grad2x[Ny*(Nx*z+x)+y]*grad2x[Ny*(Nx*z+x)+y]+grad2y[Ny*(Nx*z+x)+y]*grad2y[Ny*(Nx*z+x)+y]+grad2z[Ny*(Nx*z+x)+y]*grad2z[Ny*(Nx*z+x)+y];
			}
		}
	}

	op(1, phi); 	

	free(phi);
	free(grad1x);
	free(grad2x);
	free(grad1y);
	free(grad2y);
	free(grad1z);
	free(grad2z);
	free(phi1);
	free(phi2);
	return 0;
}

