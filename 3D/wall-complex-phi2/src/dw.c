#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>

#define Nx   100
#define Ny   100
#define Nz   100
#define dt   0.05 
#define alfa 3.0
#define tf   1000.0 
#define V0   0.13   
#define phi0 1.0 

double f(double *Ar, int x, int y, int z, double *phi1, double *phi2, double t){
	int xp1, xm1, yp1, ym1, zp1, zm1;
	double laplaciano1;
	xp1= (x+1)%Nx;
	xm1= (x-1+Nx)%Nx;
	yp1= (y+1)%Ny;
	ym1= (y-1+Ny)%Ny;
	zp1= (z+1)%Nz;
	zm1= (z-1+Nz)%Nz; 
	laplaciano1= (phi1[Ny*(Nx*z+xp1)+y]+phi1[Ny*(Nx*z+xm1)+y]+phi1[Ny*(Nx*z+x)+yp1]+phi1[Ny*(Nx*z+x)+ym1]+phi1[Ny*(Nx*zp1+x)+y]+phi1[Ny*(Nx*zm1+x)+y]-6.0*phi1[Ny*(Nx*z+x)+y]);
	return (laplaciano1-(alfa*2.0*Ar[Ny*(Nx*z+x)+y]/t)-((phi1[Ny*(Nx*z+x)+y]*2.0*V0/(pow(phi0,2)))*(((pow(phi1[Ny*(Nx*z+x)+y],2)+pow(phi2[Ny*(Nx*z+x)+y],2))/(pow(phi0,2)))-1.0)));
}

double g(double *Ai, int x, int y, int z, double *phi1, double *phi2, double t){
	int xp1, xm1, yp1, ym1, zp1, zm1;
	double laplaciano2;
	xp1= (x+1)%Nx;
	xm1= (x-1+Nx)%Nx;
	yp1= (y+1)%Ny;
	ym1= (y-1+Ny)%Ny;
	zp1= (z+1)%Nz;
	zm1= (z-1+Nz)%Nz;
	laplaciano2= (phi2[Ny*(Nx*z+xp1)+y]+phi2[Ny*(Nx*z+xm1)+y]+phi2[Ny*(Nx*z+x)+yp1]+phi2[Ny*(Nx*z+x)+ym1]+phi2[Ny*(Nx*zp1+x)+y]+phi2[Ny*(Nx*zm1+x)+y]-6.0*phi2[Ny*(Nx*z+x)+y]);
	return (laplaciano2-(alfa*2.0*Ai[Ny*(Nx*z+x)+y]/t)-((phi2[Ny*(Nx*z+x)+y]*2.0*V0/(pow(phi0,2)))*(((pow(phi1[Ny*(Nx*z+x)+y],2)+pow(phi2[Ny*(Nx*z+x)+y],2))/(pow(phi0,2)))-1.0)));
}

void ic1(double *phi1){
	int x, y, z;
	FILE *file;
	file= fopen("ic1-0.dat", "w");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%e \n", phi1[Ny*(Nx*z+x)+y]); 
			}
		}
	}
	fclose(file);
}

void ic2(double *phi2){
	int x, y, z;
	FILE *file;
	file= fopen("ic2-0.dat", "w");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%e \n", phi2[Ny*(Nx*z+x)+y]); 
			}
		}
	}
	fclose(file);
}

void th(int n, double *theta1){
	int x, y, z;
	FILE *file;
	char name[100];
	sprintf(name, "theta/theta-%d.dat", n);
	file= fopen(name, "w");
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%e \n", theta1[Ny*(Nx*z+x)+y]); 
			}
		}
	}
	fclose(file);
}

void op(int n, double *phi){
	int x, y, z;
	FILE *file;
	char name[100];
	sprintf(name, "dat/phi-%d.dat", n);
	file= fopen(name, "w");
	fprintf(file, "y, x, z, P\n"); 
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				fprintf(file, "%d, %d, %d, %.4g \n", y, x, z, phi[Ny*(Nx*z+x)+y]); 
			}
		}
	}
	fclose(file);
}

int main(int argc, char **argv){
	int x, y, z;
	int xp1, xm1, yp1, ym1, zm1, zp1;
	double *theta, *theta1, *theta2; 
	double *phi, *phi1_final, *phi2_final, *grad1x, *grad2x, *grad1y, *grad2y, *grad1z, *grad2z, *phi1, *phi2, *phi1_temp, *phi2_temp, *Ar, *Ar_temp, *Ai, *Ai_temp, *V;

	phi=   	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi1_final = (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2_final = (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1x=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2x=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1y=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2y=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad1z=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	grad2z=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi1=   	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi1_temp=   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2= 	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	phi2_temp=   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	Ar= 		   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	Ar_temp=     (double *) calloc(Nx*Ny*Nz, sizeof(double));
	Ai= 		   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	Ai_temp=     (double *) calloc(Nx*Ny*Nz, sizeof(double));
	V=	   	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	theta=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	theta1=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));
	theta2=  	   (double *) calloc(Nx*Ny*Nz, sizeof(double));

	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

//condição inicial - começo
	for (z = 0; z < Nz; z += 1){
		for(x= 0; x< Nx; x++){
			for(y= 0; y< Ny; y++){
				Ar[Ny*(Nx*z+x)+y]= 0.0;
				Ai[Ny*(Nx*z+x)+y]= 0.0;
				theta[Ny*(Nx*z+x)+y]= gsl_rng_uniform(w)*2.0*M_PI;
				phi1[Ny*(Nx*z+x)+y]= cos(theta[Ny*(Nx*z+x)+y]);
				phi2[Ny*(Nx*z+x)+y]= sin(theta[Ny*(Nx*z+x)+y]);
			}
		}
	}	
	ic1(phi1);
	ic2(phi2);

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
//condição inicial - fim

	op(0, phi);

//solução - começo
	double t;
	int n;
	for (t = 1.0; t < tf; t += 0.05){
		for (z = 0; z < Nz; z += 1){
			for(x= 0; x< Nx; x++){
				for(y= 0; y< Ny; y++){
					Ar_temp[Ny*(Nx*z+x)+y]=   Ar[Ny*(Nx*z+x)+y]+0.5*dt*(f(Ar, x, y, z, phi1, phi2, t));
					Ai_temp[Ny*(Nx*z+x)+y]=   Ai[Ny*(Nx*z+x)+y]+0.5*dt*(g(Ai, x, y, z, phi1, phi2, t));
					phi1_temp[Ny*(Nx*z+x)+y]= phi1[Ny*(Nx*z+x)+y]+0.5*dt*Ar[Ny*(Nx*z+x)+y];
					phi2_temp[Ny*(Nx*z+x)+y]= phi2[Ny*(Nx*z+x)+y]+0.5*dt*Ai[Ny*(Nx*z+x)+y];
				}
			}
		}
		for (z = 0; z < Nz; z += 1){
			for(x= 0; x< Nx; x++){
				for(y= 0; y< Ny; y++){
					Ar[Ny*(Nx*z+x)+y]+=   dt*(f(Ar_temp, x, y, z, phi1_temp, phi2_temp, t+0.5*dt));
					Ai[Ny*(Nx*z+x)+y]+=   dt*(g(Ai_temp, x, y, z, phi1_temp, phi2_temp, t+0.5*dt));
					phi1[Ny*(Nx*z+x)+y]+= dt*Ar_temp[Ny*(Nx*z+x)+y];
					phi2[Ny*(Nx*z+x)+y]+= dt*Ai_temp[Ny*(Nx*z+x)+y];
				}
			}
		}
//normalização-começo
		for (z = 0; z < Nz; z += 1){
			for(x= 0; x< Nx; x++){
				for(y= 0; y< Ny; y++){
					phi1_final[Ny*(Nx*z+x)+y]= (phi1[Ny*(Nx*z+x)+y])/(sqrt(phi1[Ny*(Nx*z+x)+y]*phi1[Ny*(Nx*z+x)+y]+phi2[Ny*(Nx*z+x)+y]*phi2[Ny*(Nx*z+x)+y]));
					phi2_final[Ny*(Nx*z+x)+y]= (phi2[Ny*(Nx*z+x)+y])/(sqrt(phi1[Ny*(Nx*z+x)+y]*phi1[Ny*(Nx*z+x)+y]+phi2[Ny*(Nx*z+x)+y]*phi2[Ny*(Nx*z+x)+y]));
					if (phi2_final[Ny*(Nx*z+x)+y] < -1.0 || phi2_final[Ny*(Nx*z+x)+y] > 1.0 ){
						printf("%e \n", phi1_final[Ny*(Nx*z+x)+y]);
					}
				}
			}	
		}
//normalização-fim
//impressão do theta depois dos campos normalizados- começo
		for (z = 0; z < Nz; z += 1){
			for(x= 0; x< Nx; x++){
				for(y= 0; y< Ny; y++){
					theta1[Ny*(Nx*z+x)+y]= acos(phi1_final[Ny*(Nx*z+x)+y]);
					theta2[Ny*(Nx*z+x)+y]= asin(phi2_final[Ny*(Nx*z+x)+y]);
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
//impressão do theta depois dos campos normalizados- fim	
		for (z = 0; z < Nz; z += 1){
			for(x= 0; x< Nx; x++){
				for(y= 0; y< Ny; y++){
					xp1= (x+1)%Nx;
					xm1= (x-1+Nx)%Nx;
					yp1= (y+1)%Ny;
					ym1= (y-1+Ny)%Ny;
					zp1= (z+1)%Nz;
					zm1= (z-1+Nz)%Nz;
					grad1x[Ny*(Nx*z+x)+y]= (phi1_final[Ny*(Nx*z+xp1)+y]+phi1_final[Ny*(Nx*z+xm1)+y])*0.5;
					grad1y[Ny*(Nx*z+x)+y]= (phi1_final[Ny*(Nx*z+x)+yp1]+phi1_final[Ny*(Nx*z+x)+ym1])*0.5;
					grad1z[Ny*(Nx*z+x)+y]= (phi1_final[Ny*(Nx*zp1+x)+y]+phi1_final[Ny*(Nx*zm1+x)+y])*0.5;
					grad2x[Ny*(Nx*z+x)+y]= (phi2_final[Ny*(Nx*z+xp1)+y]+phi2_final[Ny*(Nx*z+xm1)+y])*0.5;
					grad2y[Ny*(Nx*z+x)+y]= (phi2_final[Ny*(Nx*z+x)+yp1]+phi2_final[Ny*(Nx*z+x)+ym1])*0.5;
					grad2z[Ny*(Nx*z+x)+y]= (phi2_final[Ny*(Nx*zp1+x)+y]+phi2_final[Ny*(Nx*zm1+x)+y])*0.5;
					phi[Ny*(Nx*z+x)+y]= grad1x[Ny*(Nx*z+x)+y]*grad1x[Ny*(Nx*z+x)+y]+grad1y[Ny*(Nx*z+x)+y]*grad1y[Ny*(Nx*z+x)+y]+grad1z[Ny*(Nx*z+x)+y]*grad1z[Ny*(Nx*z+x)+y]+grad2x[Ny*(Nx*z+x)+y]*grad2x[Ny*(Nx*z+x)+y]+grad2y[Ny*(Nx*z+x)+y]*grad2y[Ny*(Nx*z+x)+y]+grad2z[Ny*(Nx*z+x)+y]*grad2z[Ny*(Nx*z+x)+y];
					V[Ny*(Nx*z+x)+y]=V0*((pow(phi1[Ny*(Nx*z+x)+y],2)+pow(phi2[Ny*(Nx*z+x)+y],2))-1)*((pow(phi1[Ny*(Nx*z+x)+y],2)+pow(phi2[Ny*(Nx*z+x)+y],2))-1);
				}
			}
		}	
		n= ((t-1)/dt)+1;
		if (n%100 == 0){
			op(n, phi); 
			th(n, theta1);		
		}
/*		if (n%1200 == 0){
			ic1(phi1);
			ic2(phi2);
//			t= tf;
		}*/	
	}
//solução - fim

	gsl_rng_free(w);
	free(phi);
	free(phi1_final);
	free(phi2_final);
	free(grad1x);
	free(grad2x);
	free(grad1y);
	free(grad2y);
	free(grad1z);
	free(grad2z);
	free(phi1);
	free(phi1_temp);
	free(phi2);
	free(phi2_temp);
	free(Ar);
	free(Ar_temp);
	free(Ai);
	free(Ai_temp);
	free(V);
	free(theta);
	free(theta1);
	free(theta2);
	return 0;
}
