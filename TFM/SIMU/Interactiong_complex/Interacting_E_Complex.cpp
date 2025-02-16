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
	
	int Time = 10000; 
	
	double Lold[Nx][2];
	double Lnew[Nx][2];
	
	double Rold[Nx][2];
	double Rnew[Nx][2];
	
	double e = 1.0; //COUPLING!
	
	double Aolder[Nx];
	double Aold[Nx];
	double Anew[Nx];
	
	double E[Nx];


	int i,t, k=0;
	
	double mx = 0.5 ;
	double sig = 0.03 ;
	
	int tout=Time/100;

	//CONTADOR//
	int IICC=4;
	
	
	for (i=0; i<Nx; i++){
		Lold[i][0]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2.0)/sig ))+exp(-0.5*((i*delx-mx*3.0/2.0)/sig)*( (i*delx-mx*3.0/2.0)/sig )))/(4.0*sig/delx*sqrt(3.14159265));
		Lnew[i][0]= (exp(-0.5*((i*delx-mx/2)/sig)*( (i*delx-mx/2.0)/sig ))+exp(-0.5*((i*delx-mx*3.0/2.0)/sig)*( (i*delx-mx*3.0/2.0)/sig )))/(4.0*sig/delx*sqrt(3.14159265));
		
		Rold[i][0]= (exp(-0.5*((i*delx-mx/3)/(0.5*sig))*( (i*delx-mx/3.0)/(0.5*sig) ))+exp(-0.5*((i*delx-mx*3.5/2.0)/(0.5*sig))*( (i*delx-mx*3.5/2.0)/(0.5*sig) )))/(2.0*sig/delx*sqrt(3.14159265));
		Rnew[i][0]= (exp(-0.5*((i*delx-mx/3)/(0.5*sig))*( (i*delx-mx/3.0)/(0.5*sig) ))+exp(-0.5*((i*delx-mx*3.5/2.0)/(0.5*sig))*( (i*delx-mx*3.5/2.0)/(0.5*sig) )))/(2.0*sig/delx*sqrt(3.14159265));
		
		Aolder[i]=0.001;
		Aold[i]=0.001;
		Anew[i]=0.001;
		
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
				fprintf(sFile, "%d %.8f %.8f %.8f %.8f \n", i , sqrt(Lnew[i][0]*Lnew[i][0] + Lnew[i][1]*Lnew[i][1]), sqrt(Rnew[i][0]*Rnew[i][0] + Rnew[i][1]*Rnew[i][1]), Anew[i], E[i]);
				//printf("%lf \n", Rnew[i][0]);
			}
			
			fclose(sFile);
			
		}
		
		double Ltotal=0.0;
		double Rtotal=0.0;
		double Atotal=0.0;
		
		for(i=0; i<Nx-1; i++){
			Lnew[i][0]=+ r*(Lold[i+1][0]-Lold[i][0])+ Lold[i][0] - e*Aold[i]*(-Lold[i][1]);
			Lnew[i][1]=+ r*(Lold[i+1][1]-Lold[i][1])+ Lold[i][0] - e*Aold[i]*Lold[i][0];
			Ltotal +=  sqrt(Lnew[i][0]*Lnew[i][0] + Lnew[i][1]*Lnew[i][1]);
		
			Rnew[i+1][0]= - r*(Rold[i+1][0]-Rold[i][0])+ Rold[i+1][0] + e*Aold[i+1]*(-Rold[i+1][1]);
			Rnew[i+1][1]= - r*(Rold[i+1][1]-Rold[i][1])+ Rold[i+1][0] + e*Aold[i+1]*Rold[i+1][0];
			Rtotal +=  sqrt(Rnew[i+1][0]*Rnew[i+1][0] + Rnew[i+1][1]*Rnew[i+1][1]);
			
		}
		
		
		for (i=0; i<Nx; i++){
			Anew[i]=2*Aold[i]-Aolder[i]+delt*delt*e*(Rold[i][0]*Rold[i][0]+Rold[i][1]*Rold[i][1]-Lold[i][0]*Lold[i][0]-Lold[i][1]*Lold[i][1]);
			Atotal += fabs(Anew[i]);
			
			E[i]=-(Anew[i]-Aold[i])/delt;
		}
		
		Lnew[Nx-1][0]=+ r*(Lold[0][0]-Lold[Nx-1][0])+ Lold[Nx-1][0] - e*Aold[Nx-1]*(-Lold[Nx-1][1]);
		Lnew[Nx-1][1]=+ r*(Lold[0][1]-Lold[Nx-1][1])+ Lold[Nx-1][0] - e*Aold[Nx-1]*Lold[Nx-1][0];
		Rnew[0][0]= - r*(Rold[0][0]-Rold[Nx-1][0])+ Rold[0][0] + e*Aold[0]*(-Rold[0][1]);
		Rnew[0][1]= - r*(Rold[0][1]-Rold[Nx-1][1])+ Rold[0][0] + e*Aold[0]*Rold[0][0];
		Ltotal +=  sqrt(Lnew[Nx-1][0]*Lnew[Nx-1][0] + Lnew[Nx-1][1]*Lnew[Nx-1][1]);
		Rtotal +=  sqrt(Rnew[0][0]*Rnew[0][0] + Rnew[0][1]*Rnew[0][1]);
		
		for(i=0; i<Nx; i++){
			Aolder[i]=Aold[i];
		}
		
		
		
		for(i=0; i<Nx; i++){
			Lold[i][0]= Lnew[i][0];
			Lold[i][1]= Lnew[i][1];
			Rold[i][0]= Rnew[i][0];
			Rold[i][1]= Rnew[i][1];
			Aold[i]= Anew[i];
			
		}
		
			
	}
	
}