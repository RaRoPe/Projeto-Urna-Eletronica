#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "interface.c"
#include "votar.c"
#include "validarCPF.c"

void main(){
	
	int8_t opcao = 0;
	int32_t CPF;

	printf("Digite o seu CPF para prosseguir com a votação: ");
	scanf("%d", &CPF);

	valida_CPF(CPF);

	while (opcao != 6){
		opcao = printa_menu(); //Printa o menu para o eleitor
		
		switch(opcao){
			case 1: //Consultar todos os candidatos distritais ou regionais dado um estado
				break;
			case 2: //Fazer busca por um candidato pra saber seu número para votar
				break;
			case 3: //Consultar todos os candidatos de um determinado partido de um estado
				break;
			case 4: //Votar em um candidato federal e regional/distrital
				votar();
				limpa_tela();
				printf( "\n"
					"\t\t***************************\n"
					"\t\tVoto computado com sucesso!\n"
					"\t\t***************************\n\n");
				exit(0);
			case 5: //Multiplicar voto x vezes
				break;
			case 6: //Sair
				exit(0);
				break;
		}
	}
}