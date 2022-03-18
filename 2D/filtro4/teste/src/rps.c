#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <fftw3.h>

void op(int t, double *phi){
	int i, j;
	char nome[100];
	int Nx, Ny;
	Nx= Ny= 500;
	FILE *arq;
	
	sprintf(nome, "dat/dw-%d.dat", t);
	arq= fopen(nome, "w");
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			fprintf(arq, "%e ", phi[i*Ny+j]);
		}
		fprintf(arq, "\n");
	}
	fclose(arq);
}

int main(int argc, char **argv){
	int i, j, l, k, x, y;
	int lpx, lmx, lpy, lmy;
	double laplaciano, t, max, min;
	double *phi, *in, *in2, *inv;
	fftw_plan p;
	fftw_plan q; 
	fftw_plan pinv;   
	FILE *file;
	int Nx, Ny;
	Nx= Ny= 500;
	
  /* Alocação de memória */
	in  = (double 	  *) calloc(Nx*Ny, sizeof(double));		
	fftw_complex* out = fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
	in2 = (double 	  *) calloc(Nx*Ny, sizeof(double));		
	fftw_complex* out2 = fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
	inv = (double 	  *) calloc(Nx*Ny, sizeof(double));
	phi = (double 	  *) calloc(Nx*Ny, sizeof(double));	

  /* Cria o plano para execução da FFT */
	p = fftw_plan_dft_r2c_2d(Ny, Nx, in, out, FFTW_ESTIMATE);
	q = fftw_plan_dft_r2c_2d(Ny, Nx, in2, out2, FFTW_ESTIMATE); 
 
   /* condição inicial para a passagem do filtro */
	file = fopen(argv[1], "r");
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
   		fscanf(file, "%lf", &in[i*Ny+j]);
		}
	}	
	fclose(file);
  /* condição inicial1 - fim */	

  /* condição inicial2/top-hat - começo */
	file = fopen(argv[2], "r");
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
   		fscanf(file, "%lf", &in2[i*Ny+j]);
		}
	}	
	fclose(file);
  /* condição inicial2/top-hat - fim */	

  /* Calcula a FFT */
	fftw_execute(p);
	fftw_execute(q);

  /* Multiplica as transformadas */
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			out[i*Ny+j]= out[i*Ny+j]*out2[i*Ny+j];
		}
	}

  /* Cria o plano para execução da inversa*/
  	pinv= fftw_plan_dft_c2r_2d(Ny, Nx, out, inv, FFTW_ESTIMATE);

  /* Calcula a inversa */
	fftw_execute(pinv);

/* Normalização */
	min= max= inv[0];
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			if (inv[i*Ny+j] < min){
				min= inv[i*Ny+j];
			}
			if (inv[i*Ny+j] > max){
				max= inv[i*Ny+j];
			}
		}
	}
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			inv[i*Ny+j]= (inv[i*Ny+j]-min)/(max-min);
		}
	}


  /* inverter as diagonais */
	for(y= 0; y< (Ny/2); y++){
		for(x= 0; x< (Nx/2); x++){
			phi[(y+Ny/2)*Nx+x+Nx/2]= inv[y*Nx+x];
			phi[y*Nx+x]= inv[(y+Ny/2)*Nx+x+Nx/2];
			phi[(y+Ny/2)*Nx+x]= inv[y*Nx+x+Nx/2];
			phi[y*Nx+x+Nx/2]= inv[(y+Ny/2)*Nx+x];
		}
	}
  /* printa os valores */
	op(1, phi);
	

  /* Libera memória */
	free(phi);
	free(in);
	free(in2);
	free(inv);
	fftw_destroy_plan(p); 
	fftw_free(out);
	fftw_destroy_plan(q); 
	fftw_free(out2);
	fftw_destroy_plan(pinv);
	return 0;
}
