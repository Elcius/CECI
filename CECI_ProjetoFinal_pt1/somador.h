int Saida(int a, int b, int cin){
	return (a+b+cin)&1;
}

int Cout(int a, int b, int cin){
	return (a+b+cin)>1?1:0;
}

int* Somador(int *a, int *b){
	int cin=0, COUT=0;
	for(int i=3; i>=0; i--){
		a[i]= Saida(a[i], b[i], cin);
		COUT= Cout(a[i],b[i], cin);	
		cin= COUT;
	}
	return a;
}
