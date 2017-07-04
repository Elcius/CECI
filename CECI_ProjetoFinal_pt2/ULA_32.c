#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genpat.h"
#include "ULA.h"

int clkv = 0, clk = 0, rst = 0, sub = 0, op = 0, y = 0;
unsigned int cur_vect = 0;

char *inttostr(entier)
	int entier;
{
	char *str;
	str = (char*)mbkalloc(32*sizeof(char));
	sprintf(str, "%d",entier);
	return(str);
}

char *inttoHstr(entier)
	int entier;
{
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf  (str, "0x%X",entier);
	return(str);
}


void TestarUla(unsigned int a, unsigned int b, int op){
		//for (i = 0; i < 100; i++){
			printf ("Entrada: SrcA = %u, SrcB = %u, op = %d \n", a, b, op);
			//AFFECT (inttostr(cur_vect), "clk", inttostr(rst) );
			//AFFECT (inttostr(cur_vect), "cin", inttostr(rst) );
			AFFECT (inttostr(cur_vect), "SrcA", inttoHstr(a) );
			AFFECT (inttostr(cur_vect), "SrcB", inttoHstr(b) );
			AFFECT (inttostr(cur_vect), "AluResult", inttoHstr(SomaSub(a,b,AddSub(op),op)) );
			AFFECT (inttostr(cur_vect), "OVFL", inttostr(Cout(a,b,AddSub(op),SomaSub(a,b,AddSub(op),op))) );
			AFFECT (inttostr(cur_vect), "Zero", inttostr(Zero(SomaSub(a,b,AddSub(op),op)))  );
			//clkv = clk;
			cur_vect++;
			//clk = !clk;
		//}
}

/*
	int Y(int a,int s){
		if((clk == 1) && (clkv == 0))
			if(rst == 1){
			y = 0;
			return y;
		}else{
			y = SomaSub(a,y,s);
			return y;
		}
		else
			return y;
	}
*/
int main(){

	DEF_GENPAT("ULA_32");

	/* interface */
	//DECLAR ("clk", ":2", "B", IN, "", "" );
	//DECLAR ("set", ":2", "B", IN, "", "" );
	//DECLAR ("cin", ":2", "B", IN, "", "" );
	//DECLAR ("addsub", ":2", "B", IN, "", "" );
	DECLAR ("op", ":2", "B", IN, "2 downto 0", "" );
	DECLAR ("SrcA", ":2", "X", IN, "31 downto 0", "" );
	DECLAR ("SrcB", ":2", "X", IN, "31 downto 0", "" );
	DECLAR ("AluResult", ":2", "X", OUT,"31 downto 0", "" );
	DECLAR ("OVFL", ":2", "B",OUT,"", "" );
	DECLAR ("Zero", ":2", "B",OUT,"", "" );
	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );

	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");
	//AFFECT ("0", "clk", "0b0");

	LABEL ("ADD");
	op=2;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	TestarUla(0, 0, op);
	TestarUla(0, 0x7fffffff, op);
	TestarUla(0x7fffffff, 0, op);
	TestarUla(0x7ffffffe, 0x1, op);
	TestarUla(0x7fffffff, 0x7fffffff, op);
	TestarUla(0x8fffffff, 0x1, op);
	TestarUla(0x8fffffff, 0x8fffffff, op);
	TestarUla(0xffffffff, 0x7fffffff, op);

	
	op=6;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("SUB");
	TestarUla(0, 0, op);
	TestarUla(0, 0x7fffffff, op);
	TestarUla(0x7fffffff, 0, op);
	TestarUla(0x7ffffffe, 0x1, op);
	TestarUla(0x7fffffff, 0x7fffffff, op);
	TestarUla(0x8fffffff, 0x1, op);
	TestarUla(0x8fffffff, 0x8fffffff, op);
	TestarUla(0xffffffff, 0x7fffffff, op);

	
	op=7;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("SLT");
	TestarUla(0, 0, op);
	TestarUla(0, 0x7fffffff, op);
	TestarUla(0x7fffffff, 0, op);
	TestarUla(0x7ffffffe, 0x1, op);
	TestarUla(0x7fffffff, 0x7fffffff, op);
	TestarUla(0x8fffffff, 0x1, op);
	TestarUla(0x8fffffff, 0x8fffffff, op);
	TestarUla(0xffffffff, 0x7fffffff, op);
		
	
	op=0;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("AND");
	TestarUla(0, 0, op);
	TestarUla(0, 0xffffffff, op);
	TestarUla(0xffffffff, 0, op);
	TestarUla(0xffffffff, 0xffffffff, op);

	
	op=1;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("OR");
	TestarUla(0, 0, op);
	TestarUla(0, 0xffffffff, op);
	TestarUla(0xffffffff, 0, op);
	TestarUla(0xffffffff, 0xffffffff, op);

	
	op=4;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("SrcANandSrcB");
	TestarUla(0, 0, op);
	TestarUla(0, 0xffffffff, op);
	TestarUla(0xffffffff, 0, op);
	TestarUla(0xffffffff, 0xffffffff, op);

	
	op=5;
	AFFECT (inttostr(cur_vect), "op", inttostr(op));
	LABEL ("SrcANorSrcB");
	TestarUla(0, 0, op);
	TestarUla(0, 0xffffffff, op);
	TestarUla(0xffffffff, 0, op);
	TestarUla(0xffffffff, 0xffffffff, op);

	printf ("\n CHEGOU\n");

	SAV_GENPAT ();
}

