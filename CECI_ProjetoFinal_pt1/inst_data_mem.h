char* inttostr(int entier) 
{
	char* str;
	str = (char*) mbkalloc(32 * sizeof(char));
	sprintf(str, "%d", entier);

	return(str);
}

char *inttoHstr(int entier)
{
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf  (str, "0x%X",entier);
	return(str);
}


int Pow(int base, int pot)
{
	int i;
	int ret = 1;

	for(i = 0; i < pot; ++i)
		ret *= base;

	return ret;
}

void instr_data_Memory(int clock, int clockA, int A, int MemWrite, int WD) {
	FILE *instrucoes;

	if (MemWrite == 0) {
		instrucoes= fopen("./memoria.txt", "r");
		if(instrucoes){
			int linha = 0, j=1,cod1=0,k;
			int i, funct, opcode, pot, rst= 1;
			char cod[32];
			printf("ARQUIVO ABERTO \n");
			
			while(!feof(instrucoes)){
				fscanf(instrucoes, "%s", cod);
				if (linha == A) {
					printf("%d%c instrucao: %s\n", linha, '@', cod);
					funct = 0;
					opcode = 0;
					pot = 1;

					for (i=5; i>=0; i--) {
						opcode += pot*(cod[i] - 48) ;
						funct += pot*(cod[26+i] - 48) ;
						pot = pot*2;
					}					

					for(k=31;k>=0;k--) {
						cod1 += j*(cod[k]-48);
						j=j*2;
					}

					printf("Opcode: %d, Funct: %d, Cod1: %d\n\n", opcode, funct, cod1);
					//MaquinaDeEstados(rst, opcode, funct,cod1);

					AFFECT(inttostr(linha), "clk",  inttostr(clock));
					AFFECT(inttostr(linha), "A",  inttostr(A));
					AFFECT(inttostr(linha), "MemWrite",  inttostr(MemWrite));
					AFFECT(inttostr(linha), "WD",  inttostr(WD));
					AFFECT(inttostr(linha), "Cod",  inttoHstr(cod1));
					AFFECT(inttostr(linha), "Funct",  inttostr(funct));
					AFFECT(inttostr(linha), "Opcode",  inttostr(opcode));
					LABEL("Leitura");
					j=1;
					cod1=0;
					rst = 0;
					
					break;
				}
				linha++;
				
			}
			fclose(instrucoes);

		}
		else{
			printf("ERRO AO ABRIR ARQUIVO \n");	
		}
	}	
	else {
		if(clock == 1 && clockA == 0){
			LABEL("Escrita");

			FILE *temp;

			instrucoes = fopen("./memoria.txt", "r+");
			temp = fopen("./~memoria.txt", "w");
			
			if(instrucoes && temp){
				
				char aux[255];
				int cont = 0;

				while(fgets(aux, sizeof(aux), instrucoes)){
					if(cont == A - 1) {
						int ik;
						int aux[32];

						for(ik = 0; ik < 32; ++ik){
							aux[ik] = Pow((WD & 0b01), ik);
							WD >>= 1;
						}

						for(ik = 31; ik >= 0; --ik)
							fprintf(temp, "%i", aux[ik]);
						
						fprintf(temp, "\n");

					} else
						fprintf(temp, "%s", aux);

					cont++;
				}
				fclose(temp);
				fclose(instrucoes);

				char ch;

				temp = fopen("./~memoria.txt", "r");
				instrucoes = fopen("./memoria.txt", "w");

				while(1){
					ch = fgetc(temp);

					if (ch == EOF)
						break;
					else
						putc(ch, instrucoes);
				}

				fclose(instrucoes);
				fclose(temp);				
			}

			else
				printf("ERRO AO ABRIR ARQUIVO \n");
		}
	}
}
