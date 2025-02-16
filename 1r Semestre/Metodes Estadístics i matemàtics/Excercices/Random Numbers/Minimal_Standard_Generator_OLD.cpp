#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define IA 16807
#define IQ 127773
#define IM 2147483647
#define IR 2836
#define AM (1.0/IM)



float ran0(long seed, float arr[]){
	long k;
	float ans;
	
	k=seed/IQ;
	seed=IA*(seed-k*IQ)-IR*k;
	if (seed <0 ){
		seed += IM;
	}
	ans=AM*seed;
	
	arr[0]=ans;
	arr[1]=seed;
	
	return 0.0;
}



int main(){
	
	int N=100000;
	float ran[N]; 
	float arr[2];
	long seed=2131231231; //We set the seed here
	arr[1]=seed;

	for (int i=0; i<N; i++){
		ran0(arr[1],arr);
		ran[i]=arr[0];	
	}


	FILE* fichero;
	fichero = fopen("Random_numbers.txt", "w" ); 
	for ( int i = 0; i < N; i++){
		fprintf(fichero, "%f \n", ran[i]);
	}
		
	return 0;
	
	
}
	