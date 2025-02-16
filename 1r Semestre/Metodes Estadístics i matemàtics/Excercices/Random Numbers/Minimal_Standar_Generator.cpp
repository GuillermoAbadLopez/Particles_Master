#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define IA 16807
#define IQ 127773
#define IM 2147483647
#define IR 2836
#define AM (1.0/IM)


unsigned long next=1;

void sran0(unsigned int seed){
	next=seed;
}

float ran0(void){
	long k;
	float ans;
	
	k=next/IQ;
	next=IA*(next-k*IQ)-IR*k;
	if (next <0 ){
		next += IM;
	}
	if (next>IM){
		next -= IM;
	}
	ans=AM*next;
	return ans;

}



int main(){
	
	sran0(1989743);  //We set the seed here
	int N =1000000;
	double ran[N];
	
	for(int i = 0; i<N; i++){
		ran[i]= ran0();
 	}


	FILE* fichero;
	fichero = fopen("Random_numbers.txt", "w" ); 
	for ( int i = 0; i < N; i++){
		fprintf(fichero, "%f \n", ran[i]);
	}
		
	return 0;
	
}
	