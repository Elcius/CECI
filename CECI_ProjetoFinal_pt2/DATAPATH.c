#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "FSM.h"
#include "inst_data_mem.h"
#include "decoder.h"
#include "Mux.h"
#include "ULA.h"
#include "ReG.h"


//#include "genpat.h"


int  e1 = 0x00000000, i, j = 1, cod1 = 0, k;
int REGISTRADORES[32];

void datapathFetch(int clock, int clockA, int IorD, int IRWrite, int PCSrc, int ALUControl, int AluSrcA, int AluSrcB, int PCen, int Reset, int CODIGO)
{	
	Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);
	Adr = Mux_2_1(Pc,0,IorD);
	Instr = Registrador(clock,clockA,Reset,IRWrite,CODIGO);
	SrcA = Mux_2_1(Pc,0,AluSrcA);
	aluSrcB[0]=AluSrcB>>0&1;
	aluSrcB[1]=AluSrcB>>1&1;
	SrcB = Mux_4_1(0,4,2,3,aluSrcB);
	aluResult = SomaSub(SrcA,SrcB,0,ALUControl);
	AlUOut = Mux_2_1(aluResult,0,PCSrc);
	PcN = RegistradorPC(clock,clockA,Reset,PCen,AlUOut);
	//Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);


	AFFECT(inttostr(cur_vect), "pc",         inttostr(Pc));
	AFFECT(inttostr(cur_vect), "clk",         inttostr(clock));
	AFFECT(inttostr(cur_vect), "rst",         inttostr(Reset));
	AFFECT(inttostr(cur_vect), "pcN",         inttoHstr(PcN));
	AFFECT(inttostr(cur_vect), "SrcA",         inttoHstr(SrcA));
	AFFECT(inttostr(cur_vect), "SrcB",         inttoHstr(SrcB));
	AFFECT(inttostr(cur_vect), "Adr",         inttoHstr(Adr));
	AFFECT(inttostr(cur_vect), "Instr",         inttoHstr(Instr));
	AFFECT(inttostr(cur_vect), "ALUResult",         inttoHstr(aluResult));
	LABEL("Fetch");

	clka = clk;
	clk = !clka;    
	cur_vect++;
}

int RegistradorSelecionado(int *reg){
	int i;
	for(i = 0; i < 32; i++){
		if(reg[i]==1)
			break;
	}
	return i;
}

void Execute(int clock, int clockA,int MemToReg, int funct, int ALUControl, int AluSrcA, int AluSrcB, int *rs, int *rt, int *rd)
{
	char label[20];
	int num_registradorRs = RegistradorSelecionado(decodificador(rs));
	int num_registradorRt = RegistradorSelecionado(decodificador(rt));
	int num_registradorRd = RegistradorSelecionado(decodificador(rd));
	
	int RegA = Registrador(clock, clockA, 0, 1, REGISTRADORES[num_registradorRs]);
	int RegB = Registrador(clock, clockA, 0, 1, REGISTRADORES[num_registradorRt]);
		
	switch(funct){
		case 0b100000:		
			strcpy(label, "Execute_Add");		

			SrcA = Mux_2_1(0,RegA,AluSrcA); 
			aluSrcB[0]=AluSrcB>>0&1;
			aluSrcB[1]=AluSrcB>>0&1;
			SrcB = Mux_4_1(RegB,4,2,3,aluSrcB); 
			printf("%i %i %i %i\n",SrcA, SrcB, 1, ALUControl );
			aluResult = SomaSub(SrcA,SrcB,0,ALUControl); // 0 para soma, 1 para subtraçã		

			break;

		case 0b100010:
			strcpy(label, "Execute_Sub");

			SrcA = Mux_2_1(0,RegA,AluSrcA); 
			aluSrcB[0]=AluSrcB>>0&1;
			aluSrcB[1]=AluSrcB>>0&1;
			SrcB = Mux_4_1(RegB,4,2,3,aluSrcB); 
			aluResult = SomaSub(SrcA,SrcB,1,ALUControl); // 0 para soma, 1 para subtraçã

			break;

		case 0b100100:
			strcpy(label, "Execute_And");

			SrcA = Mux_2_1(0,RegA,AluSrcA); 
			aluSrcB[0]=AluSrcB>>0&1;
			aluSrcB[1]=AluSrcB>>0&1;
			SrcB = Mux_4_1(RegB,4,2,3,aluSrcB); 
			aluResult = SomaSub(SrcA,SrcB,1,ALUControl); 

			break;

		case 0b100101:
			strcpy(label, "Execute_Or");

			SrcA = Mux_2_1(0,RegA,AluSrcA); 
			aluSrcB[0]=AluSrcB>>0&1;
			aluSrcB[1]=AluSrcB>>0&1;
			SrcB = Mux_4_1(RegB,4,2,3,aluSrcB); 
			aluResult = SomaSub(SrcA,SrcB,1,ALUControl); 

			break;

		case 0b101010:
			strcpy(label, "Execute_Slt");

			SrcA = Mux_2_1(0,RegA,AluSrcA); 
			aluSrcB[0]=AluSrcB>>0&1;
			aluSrcB[1]=AluSrcB>>0&1;
			SrcB = Mux_4_1(RegB,4,2,3,aluSrcB); 
			aluResult = SomaSub(SrcA,SrcB,1,ALUControl); 

			break;

		default:
			printf("Operação inexistente!");
			break;
	}
	AlUOut = Registrador(clock, clockA, 0, 1, aluResult);	
	REGISTRADORES[num_registradorRd]= Registrador(clock, clockA, 0, 1, Mux_2_1(AlUOut, 0, MemToReg));

	clka = clk;
	clk = !clka;
}


void datapath(int clock, int clockA, int IorD, int IRWrite, int PCSrc, int ALUControl, int AluSrcA, int AluSrcB, int PCen, int Reset, int CODIGO)
{	
	Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);
	Adr = Mux_2_1(Pc,0,IorD);
	Instr = Registrador(clock,clockA,Reset,IRWrite,CODIGO);
	SrcA = Mux_2_1(Pc,0,AluSrcA);
	aluSrcB[0] = AluSrcB >> 0&1;
	aluSrcB[1] = AluSrcB >> 1&1;
	SrcB = Mux_4_1(0,4,2,3,aluSrcB);
	aluResult = SomaSub(SrcA, SrcB, 0, ALUControl);
	AlUOut = Mux_2_1(aluResult, 0, PCSrc);
	PcN = RegistradorPC(clock, clockA, Reset, PCen, AlUOut);
	//Pc = RegistradorPC(clock,clockA,Reset,PCen,PcN);

	AFFECT(inttostr(cur_vect), "pc",         inttostr(Pc));
	AFFECT(inttostr(cur_vect), "clk",         inttostr(clock));
	AFFECT(inttostr(cur_vect), "rst",         inttostr(Reset));
	AFFECT(inttostr(cur_vect), "pcN",         inttoHstr(PcN));
	AFFECT(inttostr(cur_vect), "SrcA",         inttoHstr(SrcA));
	AFFECT(inttostr(cur_vect), "SrcB",         inttoHstr(SrcB));
	AFFECT(inttostr(cur_vect), "Adr",         inttoHstr(Adr));
	AFFECT(inttostr(cur_vect), "Instr",         inttoHstr(Instr));
	AFFECT(inttostr(cur_vect), "ALUResult",         inttoHstr(aluResult));
	LABEL("Reset");

	clka = clk;
	clk = !clka;    
	cur_vect++;
}


int main(void)
{
	DEF_GENPAT("FSM_Fetch");
	DECLAR ("clk",        ":2", "B", IN, "", "" );
	DECLAR ("rst",        ":2", "B", IN, "", "" );
	DECLAR ("pc",        ":2", "B", IN, "31 downto 0", "" );
	DECLAR ("SrcA",        ":2", "B", IN, "31 downto 0", "" );
	DECLAR ("SrcB",        ":2", "B", IN, "31 downto 0", "" );

	DECLAR ("Adr",        ":2", "B", OUT, "31 downto 0", "" );
	DECLAR ("Instr",        ":2", "B", OUT, "31 downto 0", "" );
	DECLAR ("ALUResult",        ":2", "B", OUT, "31 downto 0", "" );
	
	DECLAR ("pcN",        ":2", "B", IN, "31 downto 0", "" );

	DECLAR ("vdd", ":2", "B", IN, "", "" );
	DECLAR ("vss", ":2", "B", IN, "", "" );

	AFFECT ("0", "vdd", "0b1");
	AFFECT ("0", "vss", "0b0");

	int k;
	for(k=0; k<32; k++){
		REGISTRADORES[k]= k;
	}

	rst = 1;	
	AfctFSM(rst, opcode, funct);

	int a;
	int clock = 0;
	int clockA = 0;
	int FSMMemWrite = 0;
	int wd = 0;
	for(a=0; a< 5; a++)
		instr_data_Memory(clock, clockA, a, FSMMemWrite, wd);

	SAV_GENPAT ();
}
