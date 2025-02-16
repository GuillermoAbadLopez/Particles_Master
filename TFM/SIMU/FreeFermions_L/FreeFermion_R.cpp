#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define nciutats 3
#define Nx 4001


int main(){
	
	
	double Ndx = 4000 ;
	
	double r = 0.25 ;
	
	double delx = 1/Ndx ;
	double delt = r*delx ;
	
	int Time = 40000; 
	
	double Told[Nx];
	double Tnew[Nx];

	int i,t, k=0;
	
	double mx = 0.5 ;
	double sig = 0.03 ;
	
	int tout=Time/100;

	
	for (i=0; i<Nx; i++){
		Told[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
		Tnew[i]= (exp(-0.5*((i*delx-mx)/sig)*( (i*delx-mx)/sig )))/(sig*sqrt(2*3.14159265));
	}
	 
	Told[0]=0;
	Told[Nx-1]=0;
	Tnew[0]=0;
	Tnew[Nx-1]=0;
	
	char buffer [100];
	FILE * sFile;
	sprintf(buffer,"mkdir T%d_N%d_sig%.6f",  Time,  Nx, sig);
	system(buffer);
	
	for(t=0 ; t<Time ; t++){
		
		if((t%tout)==0){
			printf("%d \n",k);
			sprintf(buffer,"T%d_N%d_sig%.6f/Sky%d.txt",  Time,  Nx, sig, k);
			k=k+1;
			sFile = fopen (buffer , "w" );
		
			for(i=0; i<Nx; i++){
				fprintf(sFile, "%d %lf \n", i , Tnew[i]);
			}
			
			fclose(sFile);
			
		}
		
		double Ttotal=0;
		for(i=0; i<Nx-1; i++){
			Tnew[i]= - r*Told[i+1] + (1+r)*Told[i];
			Ttotal +=  fabs(Tnew[i]);
		}
		
		Tnew[Nx-1]=- r*Told[0] + (1+r)*Told[Nx-1];
		Ttotal += fabs(Tnew[Nx-1]);
		
		for(i=0; i<Nx; i++){
			Told[i]= Tnew[i]*4000/Ttotal;
		}
		
			
	}
	
}