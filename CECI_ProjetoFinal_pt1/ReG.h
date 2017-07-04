int e=0xFFFFFFFF;
int Registrador0(int clock, int clockA, int reset, int enable, int dado){
	int l0;
	if (clock==1 && clockA == 0){
		if (reset == 1){ 
			l0 = 0x00000000; 
		}
		else if (enable == 1){ 
			l0 = dado; 
		
		} 	
	}
    return l0;
}
int Registrador(int clock, int clockA, int reset, int enable, int dado){
	
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
