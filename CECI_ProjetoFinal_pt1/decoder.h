int* decodificador(int *s){
    int w,z,x,i;
    int *y;
    y = (int*) malloc(32*sizeof(int));
	w=16*s[0]+8*s[1]+4*s[2]+2*s[3]+s[4];
	for(x=0;x<32;x++)
	{
		y[x]=0;
	}
	y[w]=1;
    return y;
}
