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
	else
		if(((a <= 0x7FFFFFFF) && (b > 0x7FFFFFFF) && (resultado > 0x7FFFFFFF)) || 
			((a > 0x7FFFFFFF) && (b <= 0x7FFFFFFF) && (resultado <= 0x7FFFFFFF)))
			return 1;
	else
			return 0;
}

