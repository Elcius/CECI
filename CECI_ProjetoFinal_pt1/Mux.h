int Mux_2_1(int a_0, int a_1, int s)
{
	if(s == 0)
    return a_0;
	else return a_1;
}

int Mux_4_1(int a_0, int a_1, int a_2, int a_3, int *S)
{
	int y_0, y_1;
	y_0 = Mux_2_1(a_0, a_1, S[0]);
	y_1 = Mux_2_1(a_2, a_3, S[0]);
	return Mux_2_1(y_0, y_1, S[1]);
}

int Mux_8_1(int a_0, int a_1, int a_2, int a_3,int a_4, int a_5, int a_6, int a_7,int *S)
{

    int y_0, y_1;
    y_0 = Mux_4_1(a_0, a_1,a_2,a_3, S);
    y_1 = Mux_4_1(a_4, a_5,a_6,a_7, S);
    return Mux_2_1(y_0, y_1, S[2]);

}

int Mux_32_1(int a_0, int a_1, int a_2, int a_3,int a_4, int a_5, int a_6, int a_7,int a_8, int a_9, int a_10, int a_11,int a_12, int a_13, int a_14, int a_15, int a_16,
             int a_17, int a_18, int a_19,int a_20, int a_21, int a_22, int a_23,int a_24, int a_25, int a_26, int a_27,int a_28, int a_29, int a_30, int a_31,int *S){

      int y_0, y_1, y_2, y_3, *s1;
      s1 = &S[3];
      y_0 = Mux_8_1(a_0, a_1, a_2, a_3, a_4, a_5, a_6, a_7, S);
	  y_1 = Mux_8_1(a_8, a_9, a_10, a_11, a_12, a_13, a_14, a_15, S);
      y_2 = Mux_8_1(a_16, a_17, a_18, a_19, a_20, a_21, a_22, a_23, S);
      y_3 = Mux_8_1(a_24, a_25, a_26, a_27, a_28, a_29, a_30, a_31, S);
	  return Mux_4_1(y_0, y_1, y_2, y_3, s1);

}


