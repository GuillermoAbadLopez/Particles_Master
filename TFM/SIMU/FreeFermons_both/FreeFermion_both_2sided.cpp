#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define nciutats 3
#define Nx 4001


int main(){
	
	
	double Ndx = 4000.0 ;
	
	double r = 0.25 ;
	
	double delx = 1/Ndx ;
	double delt = r*delx ;
	
	int Time = 40000; 
	
	double Lold[Nx];
	double Lnew[Nx];
	
	double Rold[Nx];
	double Rnew[Nx];


	int i,t, k=0;
	
	double mx = 0.5 ;
	double sig = 0.05 ;
	
	int tout=Time/100;

	
	//INITIAL CONDITIONS
	for (i=0; i<Nx; i++){
		Lold[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
		Lnew[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
		
		Rold[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
		Rnew[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
	}
	 
	 
	//Poniendo extremos a 0
	Lold[0]=0.0;
	Lold[Nx-1]=0.0;
	Lnew[0]=0.0;
	Lnew[Nx-1]=0.0;
	
	Rold[0]=0.0;
	Rold[Nx-1]=0.0;
	Rnew[0]=0.0;
	Rnew[Nx-1]=0.0;
	
	
	//CREANDO COSAS PARA PRINT
	char buffer [100];
	FILE * sFile;
	sprintf(buffer,"mkdir T%d_N%d_sig%.6f",  Time,  Nx, sig);
	system(buffer);
	
	
	//MAIN TIME LOOP
	for(t=0 ; t<Time ; t++){
		
		//PRINT
		if((t%tout)==0){
			printf("%d \n",k);
			sprintf(buffer,"T%d_N%d_sig%.6f/Sky%d.txt",  Time,  Nx, sig, k);
			k=k+1;
			sFile = fopen (buffer , "w" );
		
			for(i=0; i<Nx; i++){
				fprintf(sFile, "%d %lf %lf \n", i , Lnew[i], Rnew[i]);
			}
			
			fclose(sFile);
			
		}
		
		double Ltotal=0;
		double Rtotal=0;
		
		
		//MAIN EVOLUTION ALGORITHM
		for(i=1; i<Nx-1; i++){
			Lnew[i]= - r/2*(Lold[i+1]-Lold[i-1]) + Lold[i];
			Ltotal +=  fabs(Lnew[i]);
			
			Rnew[i]= + r/2*(Rold[i+1]-Rold[i-1]) + Rold[i];
			Rtotal +=  fabs(Rnew[i]);
		}
		
		
		//BOUNDARY CONDITIONS
		Lnew[Nx-1]= - r/2*(Lold[0]-Lold[Nx-2]) + Lold[Nx-1];
		Ltotal += fabs(Lnew[Nx-1]);
		Lnew[0]= - r/2*(Lold[1]-Lold[Nx-1]) + Lold[0];
		Ltotal += fabs(Lnew[0]);
		
		Rnew[Nx-1]= + r/2*(Rold[0]-Rold[Nx-2]) + Rold[Nx-1];
		Ltotal += fabs(Rnew[Nx-1]);
		Rnew[0]= + r/2*(Rold[1]-Rold[Nx-1]) + Rold[0];
		Rtotal += fabs(Rnew[0]);
		
		
		//RENORMALIZE
		for(i=0; i<Nx; i++){
			Lold[i]= Lnew[i]*Ndx/Ltotal;
			Rold[i]= Rnew[i]*Ndx/Rtotal;
			
		}
		
			
	}
	
}