#include "votar.h"

bool localizar_candidato(int32_t numero_para_consulta, int8_t estado, int8_t *partido_candidato);

void votar_estadual(int8_t estado, char CPF[12]){

	int32_t codigo;
	int8_t confirmacao, partido;
	bool valido, achou;

	switch (estado){
		case DF:
			limpa_tela();

			valido = true;

			printf("\t\t\tVOTO PARA CANDIDATO DISTRITAL\n\n");
			
			while (valido == true){
				printf("Digite o código do candidato que deseja votar: ");
				scanf("%d", &codigo);
				while (codigo > 99999 || codigo < 0){
					printf("Código inválido. Digite novamente o código do candidato a distrital: ");
					scanf("%d", &codigo);
				}
				achou = localizar_candidato(codigo, DF, &partido);
				if (achou == true){
					printf("Este é o candidato que deseja votar?\n(0) CONFIRMAR\n(1) VOTAR EM OUTRO CANDIDATO\n");
					scanf("%hhd", &confirmacao);
					if (confirmacao == 0)
						valido = false;
				}
			}
			break;
		case GO:
			limpa_tela();

			valido = true;

			printf("\t\t\tVOTO PARA CANDIDATO REGIONAL\n\n");
			
			while (valido == true){
				printf("Digite o código do candidato que deseja votar: ");
				scanf("%d", &codigo);
				while (codigo > 99999 || codigo < 0){
					printf("Código inválido. Digite novamente o código do candidato a distrital: ");
					scanf("%d", &codigo);
				}
				achou = localizar_candidato(codigo, GO, &partido);
				if (achou == true){
					printf("Este é o candidato que deseja votar?\n(0) CONFIRMAR\n(1) VOTAR EM OUTRO CANDIDATO\n");
					scanf("%hhd", &confirmacao);
					if (confirmacao == 0)
						valido = false;
				}
			}
			break;
		case MS:
			limpa_tela();

			valido = true;

			printf("\t\t\tVOTO PARA CANDIDATO REGIONAL\n\n");
			
			while (valido == true){
				printf("Digite o código do candidato que deseja votar: ");
				scanf("%d", &codigo);
				while (codigo > 99999 || codigo < 0){
					printf("Código inválido. Digite novamente o código do candidato a distrital: ");
					scanf("%d", &codigo);
				}
				achou = localizar_candidato(codigo, 3, &partido);
				if (achou == true){
					printf("Este é o candidato que deseja votar?\n(0) CONFIRMAR\n(1) VOTAR EM OUTRO CANDIDATO\n");
					scanf("%hhd", &confirmacao);
					if (confirmacao == 0)
						valido = false;
				}
			}
			break;
	}
	votar_federal(codigo, partido, estado, CPF);
}

void votar_federal(int32_t codigo_candidato_regional, int8_t partido_regional, int8_t estado, char CPF[12]){

	FILE *fp, *fp2;

	char linha[400], c, CPF_alterado[15];
	
	int32_t qtd_votos;
	int8_t estado_votado, ponto_e_virgula = 0;

	printf("APERTE ENTER PARA PROSSEGUIR COM A VOTAÇÃO PARA CANDIDATO FEDERAL\n");
	getchar();

	limpa_tela();

	printf("\t\t\tVOTO PARA CANDIDATO FEDERAL\n\n");

	if (estado == DF)
		estado_votado = 53;
	else if (estado == GO)
		estado_votado = 52;
	else
		estado_votado = 50;
	
	fp = fopen("votos.txt","a+");

	system("tail -1 votos.txt > ultima_linha.txt");
	fp2 = fopen("ultima_linha.txt", "r");
	
	while ((c = getc(fp2)) != EOF){
		if (c == ';'){
			ponto_e_virgula += 1;
			if (ponto_e_virgula == 3){
				fscanf(fp2, "%d", &qtd_votos);
				break;
			}
		}
	}

	printf("CPF = %s\n", CPF);
	CPF_alterado[0] = CPF[0];
	CPF_alterado[1] = CPF[1];
	CPF_alterado[2] = CPF[2];
	CPF_alterado[3] = '.';
	CPF_alterado[4] = CPF[3];
	CPF_alterado[5] = CPF[4];
	CPF_alterado[6] = CPF[5];
	CPF_alterado[7] = '.';
	CPF_alterado[8] = CPF[6];
	CPF_alterado[9] = CPF[7];
	CPF_alterado[10] = CPF[8];
	CPF_alterado[11] = '-';
	CPF_alterado[12] = CPF[9];
	CPF_alterado[13] = CPF[10];

	if (estado == DF){
		fprintf(fp,"2;DF;%s;%d;%d;0000;00;%d;%d\n", CPF_alterado, qtd_votos+1, estado_votado, codigo_candidato_regional, partido_regional);
	}else{
		if (estado == GO){
			fprintf(fp,"2;GO;%s;%d;%d;0000;00;%d;%d\n", CPF_alterado, qtd_votos+1, estado_votado, codigo_candidato_regional, partido_regional);
		}else{
			fprintf(fp,"2;MS;%s;%d;%d;0000;00;%d;%d\n", CPF_alterado, qtd_votos+1, estado_votado, codigo_candidato_regional, partido_regional);
		}
	}

	fclose(fp);

}

void votar(char CPF[12]){
	
	int8_t estado;
	
	estado = saberEstado();

	votar_estadual(estado, CPF);
}
