	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	
	
	int main(){
		
		srand(14434354743);  //We set the seed here
		int N =100000;
		double ran[N];
		
		for(int i = 0; i<N; i++){
			ran[i]= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	 	}
	 	
	 	int counter=0;
		for (int i=0; i<N ;i++){
			for (int j=0; j<N; j++){
				if (i=j+1){
	    			if (ran[i]<ran[j]){
	    				counter+=1;
					}
	    		}
			}	
        }
        printf("%d",counter);
		return 0;
	}