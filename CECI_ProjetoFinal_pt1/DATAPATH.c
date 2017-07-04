#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include "FSM.h"
#include "inst_data_mem.h"

#include "genpat.h"


int e = 0x00000000, e1 = 0x00000000, i, j = 1, cod1 = 0, k;
//int Adr,Instr,SrcA,SrcB,aluSrcB[2],AlUOut,r=0;
//long int aluResult,cur_vect = 0,PcN,Pc;

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
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf  (str, "0x%X",entier);
	return(str);
}


/* *********************************************************************** */
/* Registradores */

int Registrador(int clock, int clockA, int reset, int enable, int dado){

	if (clock==1 && clockA == 0){
		if (reset == 1){
			e1 = 0x00000000;
		}
		else if (enable == 1){
			e1 = dado;

		}
	}
	return e1;
}


/* *********************************************************************** */
/* Registrador PC */

int RegistradorPC(int clock, int clockA, int reset, int enable, int dado){

	if (clock==1 && clockA == 0){
		if (reset == 1){
			e = 0x00000000;
		}
		else if (enable == 1){
			e = dado;

		}
	}
	return e;
}


/* *********************************************************************** */
/* Mux de uso geral */

int Mux_2_1(int a_0, int a_1, int s){
	if(s == 0) return a_0;
	else return a_1;
}

int Mux_4_1(int a_0, int a_1, int a_2, int a_3, int *S){
	int y_0, y_1;
	y_0 = Mux_2_1(a_0, a_1, S[0]);
	y_1 = Mux_2_1(a_2, a_3, S[0]);
	return Mux_2_1(y_0, y_1, S[1]);
}


/* *********************************************************************** */
/* ULA */

int AddSub(int op){
	if(op == 6 || op == 7) return 1;
	else return 0;
}

int SomaSub(int a, int b,int addsub, int op){
	long int AluResult;
	switch (op){
		case 0: return a & b;
		case 1: return a | b;
		case 2:
		case 6:
		if (addsub) b = ~b;
		AluResult = (a + b + addsub) & 0xFFFFFFFF;
		return AluResult;
		case 4: return a & ~b;
		case 5: return a | ~b;
		case 7: return a < b;
		default:
		break;
	}
}


int Zero(int resultado){
	return !resultado;
}


int Cout(unsigned int a, unsigned int b, unsigned int addsub, unsigned int resultado){
	if(!addsub)
		if(((a <= 0x7FFFFFFF) && (b <= 0x7FFFFFFF) && (resultado > 0x7FFFFFFF)) ||
				((a > 0x7FFFFFFF) && (b > 0x7FFFFFFF) && (resultado <= 0x7FFFFFFF)))
			return 1;
		else
			return 0;
	
	else if(((a <= 0x7FFFFFFF) && (b > 0x7FFFFFFF) && (resultado > 0x7FFFFFFF)) ||
				((a > 0x7FFFFFFF) && (b <= 0x7FFFFFFF) && (resultado <= 0x7FFFFFFF)))
		return 1;
	else
		return 0;
}


/* *********************************************************************** */
/* Função Principal */

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

	rst = 1;	
	AfctFSM(rst, opcode, funct);

	while(scanf("%s", cod) == 1){
		printf("%d%c instrucao: %s\n", qtd++, 166, cod);
		funct = 0;
		opcode = 0;
		pot = 1;

		for (i=5; i>=0; i--){
			opcode += pot*(cod[i] - 48) ;
			funct += pot*(cod[26+i] - 48) ;
			pot = pot*2;
		}
		printf("Opcode: %d, Funct: %d\n\n", opcode, funct);

		for(k=31;k>=0;k--)
		{
			cod1 += j*(cod[k]-48);
			j=j*2;
		}

		printf("%d\n",cod1);
		MaquinaDeEstados(rst, opcode, funct,cod1);
		j=1;
		cod1=0;
		rst = 0;
	}

	SAV_GENPAT ();
}
