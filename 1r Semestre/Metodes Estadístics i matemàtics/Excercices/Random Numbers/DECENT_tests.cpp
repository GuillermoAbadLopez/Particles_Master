#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


unsigned long next=1;
	
int ran0(void){
		next = next*1103515245 + 12345;
		return (unsigned int)(next/65536) % 32768;
}
	
void sran0(unsigned int seed){
	next=seed;
}


int main(){
	
	sran0(84289743);  //We set the seed here
	int N =100000;
	double ran[N];
	
	for(int i = 0; i<N; i++){
		ran[i]= static_cast <float> (ran0()) / static_cast <float> (RAND_MAX);
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
