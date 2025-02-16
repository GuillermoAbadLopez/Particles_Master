	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	
	
	int main(){
		
		srand(6554743);  //We set the seed here
		int N =1000000;
		double ran[N];
		
		for(int i = 0; i<N; i++){
			ran[i]= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	 	}
	 	
	 	FILE* fichero;
		fichero = fopen("Random_numbers2.txt", "w" ); 
		for ( int i = 0; i < N; i++){
			fprintf(fichero, "%f \n", ran[i]);
		}
		
		return 0;
	}