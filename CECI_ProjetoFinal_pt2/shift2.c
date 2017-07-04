#include <stdio.h>
#include <stdlib.h>
#include "genpat.h"
#include <math.h>
#include "Shift2.h"
#define NUM_BITS 32
#define MAX_32 4294967296
#define MAX_16 65536

unsigned int cur_vect = 0;

char *inttostr(int entier)
{
	char *str;
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "%d",entier);
	return(str);
}

char *inttoHstr(int entier)
{
	char *str;
	str = (char *) mbkalloc (34 * sizeof (char));
	sprintf  (str, "0x%X",entier);
    //printf ("%d %s\n" , entier, str);
	return(str);
}




int main(){
	/*Define o nome do arquivo de saída*/
	DEF_GENPAT("shift2");

	/*Variaveis*/
	unsigned int y = 0;
	unsigned int a ;
	unsigned int i;

	/*Declara todas as interfaces*/
	DECLAR ("IN", ":2", "B", IN, "31 downto 0", "" );
	DECLAR ("OUT", ":2", "B", OUT, "31 downto 0", "" );
	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );
	/*Coloca os valores do terceiro campo na variavel do segundo campo*/
	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");

	for(i= 0; i < MAX_16 ;i++)
	{
		a = i;
		AFFECT(inttostr(cur_vect), "IN", inttostr(a)); //Necessário pois o LABEL é escrito no
		y = shift2(a);
		if(i >= MAX_16)	AFFECT(inttostr(cur_vect), "OUT", inttoHstr(y));
		else		AFFECT(inttostr(cur_vect), "OUT", inttostr(y));
		cur_vect++;
	}
	
	a = 0xFFFFFFFF;
	AFFECT(inttostr(cur_vect), "IN", inttoHstr(a)); 
	y = shift2(a);
	AFFECT(inttostr(cur_vect), "OUT", inttoHstr(y));
	

		
	
	SAV_GENPAT ();
}//end main
