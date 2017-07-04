#include <stdio.h>
#include <stdlib.h>
#include "genpat.h"
#include "Extend.h"

unsigned int cur_vect = 0;
int R;

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
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "0x%X",entier);
	return(str);
}


int main()
{
	DEF_GENPAT("Sign_Extend");
	int i;
	int size_16 = 65535;

	DECLAR("in",":2","B",IN,"15 downton 0","");
	DECLAR("Signlmm",":2","B",OUT,"31 downton 0","");
	DECLAR("vdd",":2","B",IN,"","");
	DECLAR("vss",":2","B",IN,"","");

	AFFECT("0","vdd","0b1");
	AFFECT("0","vss","0b0");

	for(i=0; i <= size_16; i++){
		
		AFFECT(inttostr(cur_vect),"in",inttostr(i));
		LABEL("sinal");
		R = sign_extension(i);
		AFFECT(inttostr(cur_vect),"Signlmm",inttoHstr(R));
		cur_vect++;
		
	}
	
	printf("\nFIM\n");
	SAV_GENPAT();
}
