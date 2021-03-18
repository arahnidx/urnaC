#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T 19 /*quantidade de candidatos, e necessario alterar caso adicione algum candidato*/

int input,BRANCO,tvotos,nulo;  /*variaveis globais pois usei elas em mais de uma função*/

void init();
void finalizar();
void votar();
void printAll();
void interface();
void inicio();
void contagem();

struct candidato { /* objeto candidato */
    char nome[100];  
    char partido[20];
    int votos;
    long int numero;
    };

struct candidato lista[T]; /* "arraylist */

main(){
    init();
    inicio();
	return 0;
}

void inicio(){
	//printAll(); /*imprime a lista de candidatos*/
	interface();
	printf("\n\tInsira o numero do seu candidato:\n\t");
	scanf("%d" ,&input);
	
	if(input==96482){
		finalizar();
	}
	else{
		system("cls");
		votar();
	}	
}

void printAll(){ /*Mostra todos os votos e candidatos*/

    int i;

    for(i=0;i<T;i++){
        printf("\t***************\n");
        printf("\tNome: %s",lista[i].nome);    
        printf("\tPartido: %s",lista[i].partido);
        printf("\tVotos: %d\n",lista[i].votos);
        printf("\tNumero: %d\n",lista[i].numero);
        printf("\t***************\n");
    }
    printf("\n\tVotos brancos: %d\n",BRANCO);
	printf("\n\tVotos Nulos: %d\n",nulo);
 	printf("\n\tTotal de votos: %d\n" ,tvotos);	 
}

void init(){  /*Carrega os candidatos contidos no arquivo de texto*/
    FILE *arq;
    int cont, i;
	char linha[100];

    arq = fopen("partido1.txt","r");
    cont = 1;
    i = 0;
    BRANCO=0;
    nulo=0;
    tvotos=0; 
    
    while(!feof(arq)){
        fgets(linha,100,arq);
        if(cont==1){
            strcpy(lista[i].nome,linha);
            lista[i].votos = 0;  /*Deixa inicialmente todos os candidatos com 0 votos*/
        }
		else if(cont==2){
            strcpy(lista[i].partido,linha);
        }
		else if(cont==3){
            lista[i].numero = atoi(linha);
        }
		else if(cont==4){ /*cont 4 para pular uma linha e recomeçar pra ficar mais organizado o bloco de notas */
		cont = 0;
        i++;	
		} 
        cont++;    
    }    
    fclose(arq);
}

void interface(){ 
	printf("\n\t                     _______________________\n");
	printf(" \t                    |                       |\n");
	printf(" \t                    |  | 7 |  | 8 |  | 9 |  |\n");
	printf(" \t                    |  | 4 |  | 5 |  | 6 |  |\n");
	printf(" \t                    |  | 1 |  | 2 |  | 3 |  |\n");
	printf(" \t                    |         | 0 |         |\n");
	printf(" \t                    |_______________________|");
	printf("\n\t|--------------------------------------------|\n");
	printf("\t|  |1- Branco|  |2- Corrige|  |3- Confirma|  |\n");
	printf("\t|--------------------------------------------|\n");
}

void finalizar(){
	int encerrar,bug;

	printf("\tTem certeza de que deseja encerrar a votacao?\n\t 0-Nao / 1-Sim\n\t  ");
	scanf("%d" ,&encerrar);
		
	if(encerrar==0){
		system("cls");
		inicio();
	}
	else if (encerrar==1){
		if(tvotos==0){
			tvotos++;
			bug++; /*para nao mostrar infinito caso abra o finalizar sem antes ter feito algum voto valido*/
		}
		system("cls");	
		printf("\tVotacao encerrada, votos impressos a seguir:\n");
		contagem();						
 		printf("\n\tVotos brancos: %.2f%% (%d) \n" ,(((double)BRANCO)/tvotos)*100,BRANCO);
 		printf("\n\tVotos Nulos: %.2f%% (%d) \n" ,(((double)nulo)/tvotos)*100,nulo);
 	
	 	if(bug==1){ 
 			printf("\n\tTotal de votos: %d\n" ,tvotos-1);	/*nao deixa aparecer o infinito caso tenha 0 votos validos  (x/0 é indeterminação)*/
		}
		else{
			printf("\n\tTotal de votos: %d\n" ,tvotos);		
		}
 			
		system("pause");	
	}
	else{
		printf("\tOpcao invalida, retornando..\n");
		finalizar();
	}
}

void votar(){
	int i=0,opcao,confirmavoto;
	
	for(i=0;i<T;i++){ /*Procura o candidato e só mostra caso o numero digitado seja igual ao de algum candidato*/
		if(lista[i].numero == input){
			printf("\n\tNome: %s" ,lista[i].nome);
			printf("\tPartido: %s" ,lista[i].partido);
			printf("\tNumero do candidato: %d",lista[i].numero);
			break;
		}	
	}
		
	if(i==T){ /*Caso passe de (T-1) significa que o candidato nao esta na lista entao sera um voto nulo*/
		printf("\n\n\n\t***Candidato nao existe, deseja confirmar o voto nulo?***\n\n");
		interface();
		printf("\tEscolha uma opcao:\n\t");
		scanf("%d" ,&opcao);

		if (opcao==1){
			printf("\n\tVoce tem certeza que deseja votar em branco?\n");
			printf("\n\tDigite 1 para confirmar ou 2 para cancelar:\n\t");
			scanf("%d",&confirmavoto);
				
			if(confirmavoto==1){
				BRANCO++;
				tvotos++;
				system("cls");
				inicio();
			}
			else if(confirmavoto==2){
				system("cls");
				inicio();
			}
			else{
				system("cls");
				printf("/n/t Opcao Invalida, retornando...");
				votar();
			}
		}
		else if (opcao==2){
			system("cls");
			inicio();
		}
		else if (opcao==3){
			printf("\n\tVoce tem certeza que deseja votar nulo?\n");
			printf("\n\tDigite 1 para confirmar ou 2 para cancelar:\n\t");
			scanf("%d",&confirmavoto);
			if(confirmavoto==1){
				tvotos++;
				nulo++;
				system("cls");
				inicio();
			}
			else if(confirmavoto==2){
				system("cls");
				inicio();
			}
			else{
				system("cls");
				printf("/n/t Opcao Invalida, retornando...");
				votar();
			}		
		}
		else{
			system("cls");
			printf("/n/t Opcao Invalida, retornando...");
			votar();
		}		
	}
	/*Caso tenha encontrado o candidato ele vai vir pra ca graças ao break;*/
	interface();
	printf("\tEscolha uma opcao:\n\t");
	scanf("%d" ,&opcao);
	

	if (opcao==1){
		printf("\n\tVoce tem certeza que deseja votar em branco?\n");
		printf("\n\tDigite 1 para confirmar ou 2 para cancelar\n\t");
		//printf("\n\tVotos brancos: %d\n" ,BRANCO); /*imprime quantidade de votos em branco*/
		scanf("%d",&confirmavoto);
			
		if(confirmavoto==1){
			BRANCO++;
			tvotos++;
			system("cls");
			printf("\tVoto armazenado\n\n");
			inicio();
		}
		else if(confirmavoto==2){
			system("cls");
			inicio();
		}	
		else{
			system("cls");
			printf("/n/t Opcao Invalida, retornando...");
			votar();
		}
	}
	else if (opcao==2){
		system("cls");
		inicio();			
		}
	else if (opcao==3){
		printf("\n\tVoce tem certeza que deseja votar em %s\t?\n" ,lista[i].nome);
		printf("\n\tDigite 1 para confirmar ou 2 para cancelar\n\t");
		scanf("%d",&confirmavoto);
				
		if(confirmavoto==1){
			tvotos++;
			lista[i].votos++;
			system("cls");
			printf("\tVoto armazenado\n\n");
			inicio();
		}
		else if(confirmavoto==2){
		inicio();
					
		}
		else{
		system("cls");
		printf("/n/t Opcao Invalida, retornando...");
		votar();
		}
	}
	else{
		system("cls");
		printf("/n/t Opcao Invalida, retornando...");
		votar();
	}	
}

void contagem(){	/*Imprime as informacoes que foram armazenadas no formato pedido no trabalho*/
	int i;

    for(i=0;i<T;i++){
        printf("\n\t%s",lista[i].nome);
        printf("\t(%d):" ,lista[i].numero);
        printf("%.2f%%" ,(((double)lista[i].votos)/tvotos)*100);
        printf("(%d)\n",lista[i].votos );
    }
}
