#include <stdio.h>
#include <stdlib.h>
#include "genpat.h"
#include "inst_data_mem.h"

int main(){
	DEF_GENPAT("inst_data_mem");
	

	DECLAR ("clk",        ":2", "B", IN, "", "" );
	DECLAR ("A",        ":2", "B", IN, "3 downto 0", "" );
	DECLAR ("MemWrite",        ":2", "B", IN, "", "" );
	DECLAR ("WD",        ":2", "B", IN, "", "" );
	DECLAR ("Cod",        ":2", "B", OUT, "31 downto 0", "" );
	DECLAR ("Funct",        ":2", "B", OUT, "5 downto 0", "" );	
	DECLAR ("Opcode",        ":2", "B", OUT, "5 downto 0", "" );

	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );

	AFFECT ("0", "clk", "0b0");
	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");

	int a;
	int clock = 0;
	int clockA = 0;
	int FSMMemWrite = 0;
	int wd = 0;
	
	for(a = 0; a < 8; a++) {
		instr_data_Memory(clock, clockA, a, FSMMemWrite, wd);
	}

	clock = 1;
	clockA = 0;
	FSMMemWrite = 1;
	wd = 0b00010001000100010001000100010001;
	
	for(a = 10; a < 20; a++)
		instr_data_Memory(clock, clockA, a, FSMMemWrite, wd);

	SAV_GENPAT();
}


