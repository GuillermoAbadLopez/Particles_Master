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
	double sig = 0.03 ;
	
	int tout=Time/100;

	int IICC=3;
	for (i=0; i<Nx; i++){
		Lold[i]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2)/sig ))+exp(-0.5*((i*delx-mx*3/2)/sig)*( (i*delx-mx*3/2)/sig )))/(2*sig*sqrt(2*3.14159265));
		Lnew[i]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2)/sig ))+exp(-0.5*((i*delx-mx*3/2)/sig)*( (i*delx-mx*3/2)/sig )))/(2*sig*sqrt(2*3.14159265));
		
		Rold[i]= 5*sin(i/110.0);
		Rnew[i]= 5*sin(i/110.0);
	}
	 
	Lold[0]=0;
	Lold[Nx-1]=0;
	Lnew[0]=0;
	Lnew[Nx-1]=0;
	
	Rold[0]=0;
	Rold[Nx-1]=0;
	Rnew[0]=0;
	Rnew[Nx-1]=0;
	
	char buffer [100];
	FILE * sFile;
	sprintf(buffer,"mkdir T%d_N%d_sig%.6f_%d",  Time,  Nx, sig, IICC);
	system(buffer);
	
	for(t=0 ; t<Time ; t++){
		
		if((t%tout)==0){
			printf("%d \n",k);
			sprintf(buffer,"T%d_N%d_sig%.6f_%d/Sky%d.txt",  Time,  Nx, sig, IICC,k);
			k=k+1;
			sFile = fopen (buffer , "w" );
		
			for(i=0; i<Nx; i++){
				fprintf(sFile, "%d %lf %lf \n", i , Lnew[i], Rnew[i]);
			}
			
			fclose(sFile);
			
		}
		
		double Ltotal=0;
		double Rtotal=0;
		
		for(i=0; i<Nx-1; i++){
			Lnew[i]=+ r*(Lold[i+1]-Lold[i])+ Lold[i];
			Ltotal +=  fabs(Lnew[i]);
			
			Rnew[i+1]= - r*(Rold[i+1]-Rold[i])+ Rold[i+1];;
			Rtotal +=  fabs(Rnew[i+1]);
		}
		
		Lnew[Nx-1]= + r*(Lold[0]-Lold[Nx-1])+ Lold[Nx-1];
		Ltotal += fabs(Lnew[Nx-1]);
		
		Rnew[0]= - r*(Rold[0]-Rold[Nx-1])+ Rold[0];
		Rtotal += fabs(Rnew[0]);
		
		for(i=0; i<Nx; i++){
			Lold[i]= Lnew[i]*Ndx/Ltotal;
			Rold[i]= Rnew[i]*Ndx/Rtotal;
			
		}
		
			
	}
	
}