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
	
	int Time = 100000; 
	
	double Lold[Nx][2];
	double Lnew[Nx][2];
	
	double Rold[Nx][2];
	double Rnew[Nx][2];
	
	double e = 0.01; //COUPLING!
	
	double Aolder[Nx];
	double Aold[Nx];
	double Anew[Nx];
	
	double E[Nx];


	int i,t, k=0;
	
	double mx = 0.5 ;
	double sig = 0.03 ;
	
	int tout=Time/100;

	//CONTADOR//
	int IICC=55;
	
	
	for (i=0; i<Nx; i++){
		Lold[i][0]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2)/sig ))+exp(-0.5*((i*delx-mx*3/2)/sig)*( (i*delx-mx*3/2)/sig )))/(2*sig*sqrt(2*3.14159265));
		Lnew[i][0]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2)/sig ))+exp(-0.5*((i*delx-mx*3/2)/sig)*( (i*delx-mx*3/2)/sig )))/(2*sig*sqrt(2*3.14159265));
		
		Rold[i][0]= (exp(-0.5*((i*delx-mx/3)/(0.5*sig))*( (i*delx-mx/3)/(0.5*sig) ))+exp(-0.5*((i*delx-mx*3.5/2)/(0.5*sig))*( (i*delx-mx*3.5/2)/(0.5*sig) )))/(sig*sqrt(2*3.14159265));
		Rold[i][0]= (exp(-0.5*((i*delx-mx/3)/(0.5*sig))*( (i*delx-mx/3)/(0.5*sig) ))+exp(-0.5*((i*delx-mx*3.5/2)/(0.5*sig))*( (i*delx-mx*3.5/2)/(0.5*sig) )))/(sig*sqrt(2*3.14159265));
		
		Anew[i]=0.0;
		
	}
	
	
	char buffer [100];
	FILE * sFile;
	sprintf(buffer,"mkdir T%d_N%d_sig%.3f_%d",  Time,  Nx, sig, IICC);
	system(buffer);
	
	for(t=0 ; t<Time ; t++){
		
		if((t%tout)==0){
			printf("%d \n",k);
			sprintf(buffer,"T%d_N%d_sig%.3f_%d/Sky%d.txt",  Time,  Nx, sig, IICC,k);
			k=k+1;
			sFile = fopen (buffer , "w" );
		
			for(i=0; i<Nx; i++){
				fprintf(sFile, "%d %lf %lf %lf %lf \n", i , Lnew[i], Rnew[i], Anew[i]*10, E[i]*100);
			}
			
			fclose(sFile);
			
		}
		
		double Ltotal=0;
		double Rtotal=0;
		double Atotal=0;
		
		for(i=0; i<Nx-1; i++){
			Lnew[i][0]=+ r*(Lold[i+1][0]-Lold[i][0])+ Lold[i][0] - e*Aold[i]*(-Lold[i][1]);
			Lnew[i][1]=+ r*(Lold[i+1][1]-Lold[i][1])+ Lold[i][0] - e*Aold[i]*Lold[i][0];
			Ltotal +=  sqrt(Lnew[i][0]*Lnew[i][0] + Lnew[i][1]*Lnew[i][1]);
		
		///////////////////////////////////////////////////////// HASTA AQUI CAMBIADO SOLO!!!! ////////////////////////////////////////////////////
		
			Rnew[i+1][0]= - r*(Rold[i+1][0]-Rold[i][0])+ Rold[i+1][0] +e*Aold[i]*(-Rold[i+1][1]);
			Rnew[i+1][1]= - r*(Rold[i+1][1]-Rold[i][1])+ Rold[i+1] + e*Aold[i]*Rold[i+1][0];
			Rtotal +=  sqrt(Rnew[i+1][0]*Rnew[i+1][0] + Rnew[i+1][1]*Rnew[i+1][1]);
		}
		
		
		for (i=0; i<Nx; i++){
			Anew[i]=2*Aold[i]-Aolder[i]+delt*delt*e*(Rold[i]*Rold[i]-Lold[i]*Lold[i]);
			Atotal += fabs(Anew[i]);
			
			E[i]=-(Anew[i]-Aold[i])/delt;
		}
		
		Lnew[Nx-1]= + r*(Lold[0]-Lold[Nx-1])+ (1-e*Aold[Nx-1])*Lold[Nx-1];
		Ltotal += fabs(Lnew[Nx-1]);
		
		Rnew[0]= - r*(Rold[0]-Rold[Nx-1])+ (1+e*Aold[0])*Rold[0];
		Rtotal += fabs(Rnew[0]);
		
		for(i=0; i<Nx; i++){
			Aolder[i]=Aold[i];
		}
		
		for(i=0; i<Nx; i++){
			Lold[i]= Lnew[i]*Ndx/(Ltotal+Rtotal);
			Rold[i]= Rnew[i]*Ndx/(Ltotal+Rtotal);
			Aold[i]= Anew[i];
			
		}
		
			
	}
	
}