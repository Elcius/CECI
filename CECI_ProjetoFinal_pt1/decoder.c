#include "stdio.h"
#include "stdlib.h"
#include "decoder.h"
#include "somador.h"


int main(){
	int i;
	int mais_um[32]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	int saida[32]=   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(i=0; i<32; i++){
		saida= Somador(saida, mais_um);
		printf("%i\n", saida[i]);
	}
}