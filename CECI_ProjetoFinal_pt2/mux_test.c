#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "Mux.h"

#include "genpat.h"


char *inttostr(int entier)
{
	char *str;
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "%d",entier);
	return str;
}



int main(void)
{
	DEF_GENPAT("Mux_test");

	DECLAR ("Sel0", ":2", "B", IN, "", "");
	DECLAR ("Sel1", ":2", "B", IN, "", "");

	DECLAR ("A1", ":2", "B", IN, "31 downto 0", "");
	DECLAR ("A2", ":2", "B", IN, "31 downto 0", "");
	DECLAR ("A3", ":2", "B", IN, "31 downto 0", "");
	DECLAR ("A4", ":2", "B", IN, "31 downto 0", "");

	DECLAR ("Out", ":2", "B", OUT, "31 downto 0", "");
	
	DECLAR ("vdd", ":2", "B", IN, "", "");
	DECLAR ("vss", ":2", "B", IN, "", "");

	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");

	int a1 = 10;
	int a2 = 16;
	int a3 = 4;
	int a4 = 33;
	int out;

	AFFECT("0", "A1", inttostr(a1));
	AFFECT("0", "A2", inttostr(a2));
	AFFECT("0", "A3", inttostr(a3));
	AFFECT("0", "A4", inttostr(a4));

	int op1[] = {0,0};
	int op2[] = {0,1};
	int op3[] = {1,0};
	int op4[] = {1,1};

	int *sel[4] = {op1, op2, op3, op4};

	int i;

	LABEL("BEGIN");

	for (i = 0; i < 4; ++i)
	{
		out = Mux_4_1(a1, a2, a3, a4, sel[i]);
		//printf("Mux(%i, %i, %i, %i [%i%i]) = %i\n", a1, a2, a3, a4, sel[i][0], sel[i][1], out);
		AFFECT(inttostr(i), "Sel0", inttostr(sel[i][0]));
		AFFECT(inttostr(i), "Sel1", inttostr(sel[i][1]));
		AFFECT(inttostr(i), "Out", inttostr(out));
	}

	SAV_GENPAT();
	return 0;
}