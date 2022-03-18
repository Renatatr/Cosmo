#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <fftw3.h>

void op(int t, double *phi){
	int i, j, k;
	char nome[100];
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;
	FILE *arq;
	sprintf(nome, "dat/dw-%d.dat", t);
	arq= fopen(nome, "w");
	fprintf(arq, "x,y,z,P\n");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				fprintf(arq, "%d,%d,%d,%e\n", i, j, k, phi[Ny*(Nx*k+i)+j]);
//				fprintf(file, "%e \n", phi[Ny*(Nx*k+i)+j]); 
			}
		}
	}
	fclose(arq);
}

int main(int argc, char **argv){
	int i, j, l, k, x, y, z;
	double laplaciano, t, max, min;
	double *phi, *in, *in2, *inv;
	fftw_plan p;
	fftw_plan q; 
	fftw_plan pinv;   
	FILE *file;
	int Nx, Ny, Nz;
	Nx= Ny= Nz= 100;

  /* Alocação de memória */
	in  = (double 	  *) calloc(Nx*Ny*Nz, sizeof(double));		
	fftw_complex* out = fftw_malloc(sizeof(fftw_complex)*Nx*Ny*Nz);
	in2 = (double 	  *) calloc(Nx*Ny*Nz, sizeof(double));		
	fftw_complex* out2 = fftw_malloc(sizeof(fftw_complex)*Nx*Ny*Nz);
	inv = (double 	  *) calloc(Nx*Ny*Nz, sizeof(double));
	phi = (double 	  *) calloc(Nx*Ny*Nz, sizeof(double));	

  /* Cria o plano para execução da FFT */
	p = fftw_plan_dft_r2c_3d(Ny, Nx, Nz, in, out, FFTW_ESTIMATE);
	q = fftw_plan_dft_r2c_3d(Ny, Nx, Nz, in2, out2, FFTW_ESTIMATE); 
	
   /* condição inicial */
	file = fopen(argv[2], "r");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
   			fscanf(file, "%lf", &in[Ny*(Nx*k+i)+j]);
			}
		}
	}	
	fclose(file);
	/* imprimir a condição inicial */
	op(0, in);
  /* condição inicial - fim */	

  /* filtro - começo */
	file = fopen(argv[1], "r");
	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
   			fscanf(file, "%lf", &in2[Ny*(Nx*k+i)+j]);
			}
		}
	}	
	fclose(file);
  /* condição inicial2/top-hat - fim */	

  /* Calcula a FFT */
	fftw_execute(p);
	fftw_execute(q);

  /* Multiplica as transformadas */
  	for (k = 0; k < Nz; k += 1){
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				out[Ny*(Nx*k+i)+j]= out[Ny*(Nx*k+i)+j]*out2[Ny*(Nx*k+i)+j];
			}
		}
	}

  /* Cria o plano para execução da inversa*/
	pinv= fftw_plan_dft_c2r_3d(Ny, Nx, Nz, out, inv, FFTW_ESTIMATE);

  /* Calcula a inversa */
	fftw_execute(pinv);

  /* inverter as diagonais */
	for(z= 0; z< (Nz/2); z++){
		for(y= 0; y< (Ny/2); y++){
			for(x= 0; x< (Nx/2); x++){
				phi[((z+Nz/2)*Ny+(y+Ny/2))*Nx+(x+Nx/2)]= inv[(z*Ny+y)*Nx+x];
				phi[(z*Ny+y)*Nx+x]= inv[((z+Nz/2)*Ny+(y+Ny/2))*Nx+(x+Nx/2)];
				
				phi[((z+Nz/2)*Ny+(y+Ny/2))*Nx+x]= inv[(z*Ny+y)*Nx+(x+Nx/2)];
				phi[(z*Ny+y)*Nx+(x+Nx/2)]= inv[((z+Nz/2)*Ny+(y+Ny/2))*Nx+x];
	
				phi[((z+Nz/2)*Ny+y)*Nx+x]= inv[(z*Ny+(y+Ny/2))*Nx+(x+Nx/2)];
				phi[(z*Ny+(y+Ny/2))*Nx+(x+Nx/2)]= inv[((z+Nz/2)*Ny+y)*Nx+x];
				
				phi[((z+Nz/2)*Ny+y)*Nx+(x+Nx/2)]= inv[(z*Ny+(y+Ny/2))*Nx+x];
				phi[(z*Ny+(y+Ny/2))*Nx+x]= inv[((z+Nz/2)*Ny+y)*Nx+(x+Nx/2)];
			}
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
