
/*
 *   Execício 1 - Lab_ED2 
 *   Autores:
 *   Gustavo Molina
 *   Gabriel Vinícius
 *   Luis Marcello 
 *   Pedrenrique Gonçalves
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

//variáveis de controle
int quantum = 10;
int quantPronto=0;
int fazer = 1;

//struct do processo

typedef struct PROCESSO {
    struct PROCESSO *prox;
    int id;
    int tempoCPU;
    char estado[20];
    int stack, heap, data;
} Processo;

//struct para controlar as FILAS

typedef struct lista {
    Processo *inicio;
    Processo *fim;
} LISTA;

//função para liberar as LISTAS da memória
void limpa(LISTA *l) {
    Processo *aux = l->inicio;
    while (l->inicio != NULL) {
        aux = l->inicio;
        l->inicio = l->inicio->prox;
        free(aux);
    }
}

Processo *removeProcesso(Processo *l);

//inicializa as LISTAs de forma genérica 
LISTA *criaLista() {
    LISTA *l = (LISTA *) malloc(sizeof (LISTA));
    l->fim = NULL;
    l->inicio = NULL;
    return l;
}

//função para exibir uma fila
//recebe o INICIO de uma fila como parâmetro

void exibirJobs(LISTA *jobs) {

    if (jobs->inicio == NULL) {
        printf("\nLista de JOBS vazia.\n");
    } else {
        Processo *aux = jobs->inicio;

        printf("\n---FILA JOBS---\n");
        while (aux != NULL) {
            printf("|ID:%d ", aux->id);
       	 	printf("\n");
       	 	printf("|DATA:%d ", aux->data);
       	 	printf("\n"); 
       	 	printf("|HEAP:%d ", aux->heap);
       	 	printf("\n"); 
			printf("|Stack:%d ", aux->stack);
       	 	printf("\n");
            printf("|Tempo de CPU:%d ", aux->tempoCPU);
        	printf("\n");
            printf("|Estado:%s ", aux->estado);
            printf("\n");
			printf("\n");
			aux = aux->prox;
    	}
        
    }

}

//recebe o INICIO de uma fila como parâmetro

void exibirPronto(LISTA *pronto) {

    if (pronto->inicio == NULL) {
        printf("\nLista de PRONTO vazia.\n");
    } else {
        Processo *aux = pronto->inicio;

        printf("\n---FILA PRONTO---\n");
        printf("\n---PROCESSO NA CPU---\n");
        while (aux != NULL) {
            printf("|ID:%d \t\t", aux->id);
            aux = aux->prox;
        }
        printf("\n");
        aux = pronto->inicio;
        while (aux != NULL) {
            printf("|Tempo CPU:%d \t\t", aux->tempoCPU);
            aux = aux->prox;
        }
        printf("\n");
        aux = pronto->inicio;
        while (aux != NULL) {
            printf("|Estado:%s \t", aux->estado);
            aux = aux->prox;
        }
        printf("\n");
    }
}


void exibirDispositivo(LISTA *Dispositivo) {

    if (Dispositivo->inicio == NULL) {
        printf("\nLista de Dispositivo vazia.\n");
    } else {
        Processo *aux = Dispositivo->inicio;

        printf("\n---FILA Dispositivos---\n");
        while (aux != NULL) {
            while (aux != NULL) {
                printf("|ID:%d \t\t", aux->id);
                aux = aux->prox;
            }
            printf("\n");
            aux = Dispositivo->inicio;
            while (aux != NULL) {
                printf("|Tempo de CPU:%d \t\t", aux->tempoCPU);
                aux = aux->prox;
            }
            printf("\n");
            aux = Dispositivo->inicio;
            while (aux != NULL) {
                printf("|Estado:%s \t", aux->estado);
                aux = aux->prox;
            }
            printf("\n");
        }
    }
}

// Recebe a FILA PRONTO de parâmetro e conta quantos termos ela tem
int contaPronto(LISTA *pronto) {
    int n=0;
    if (pronto->inicio == NULL) {
        n = 0;
    } else {
        Processo *aux = pronto->inicio;
        while (aux != NULL) {
            n++;
            aux = aux->prox;
        }
    }
    return n;
}

// Recebe a FILA DISPOSITIVO de parâmetro e conta quantos termos ela tem
int contaDispositivo(LISTA *dispositivo) {
    int n=0;
    if (dispositivo->inicio == NULL) {
        n = 0;
    } else {
        Processo *aux = dispositivo->inicio;
        while (aux != NULL) {
            n++;
            aux = aux->prox;
        }
    }
    return n;
}

//função para criar um processo, deve inserir na fila JOBS de forma aleatória
LISTA* criaProcesso(LISTA *l) {//Funciona!
    int ale, i;
    //gerar variação no ID
    for (i = 0; i < 2; i++) {
        ale = (rand() % 10000) + 1;
    }
    int aux_id = ale;
    int aux_stack = (rand() % 10) + 4;
    int aux_heap = (rand() % 10) + 6;
    int aux_data = (rand() % 10) + 8;
    int aux_tempo = (rand() % 5) + 3;
    char aux_estado[20];
    fflush(stdin); //limpa o buffer
    strcpy(aux_estado, "Na fila JOBS");

    Processo *novo = (Processo *) malloc(sizeof (Processo));
    novo->prox = NULL;

    if (novo == NULL) {
        printf("\nMemoria insuficiente\n");
        exit(1);
    }

    novo->data = aux_data;
    novo->heap = aux_heap;
    novo->id = aux_id;
    novo->stack = aux_stack;
    novo->tempoCPU = aux_tempo;
    strcpy(novo->estado, aux_estado);

    //lógica de FILA SIMPLES
    if (l->inicio == NULL) {
        l->fim = novo;
        l->inicio = novo;
    } else {//se tiver elemento, insere no fim
        l->fim->prox = novo;
        l->fim = novo;
    }
    return l;
}

/*  move TODOS os processos para a fila de PRONTOS
 *   aqui, os processos começaram a ser atendidos segundo o RR
 */

LISTA *movePronto(LISTA *jobs, LISTA *pronto) {
    
	Processo *aux = jobs->inicio;
	
	quantPronto = contaPronto(pronto);
	int x = quantPronto;  
	
	while ( x < 5 && jobs->inicio != NULL) {
    	
        /*  Este x vai até 5, garante que haja no máximo 5 processos na fila de pronto
         *  e deve existir elemento na FILA de Jobs
         */
        fflush(stdin);
		strcpy(aux->estado, "Na Fila PRONTO");
        jobs->inicio = aux->prox;
        if(pronto->inicio == NULL){ //Se a fila JOBS estiver vazia
            pronto->inicio = aux;
            pronto->fim = aux;
            aux->prox = NULL;
        } else {//Se tiver elementos
            pronto->fim->prox = aux;
            pronto->fim = aux;
            aux->prox = NULL;
        }
        aux = jobs->inicio;
    	x++;
    }     
    return jobs;
}

//Função para decrementar o valor do tempo, 
//arruma a lista de forma a deixa-lá circular
LISTA *resolveProcesso(LISTA *pronto) {

    Processo *aux = pronto->inicio;

	aux->tempoCPU = aux->tempoCPU - quantum; //"resolve" o processo
    if ( (aux->tempoCPU) <= 0) {//se resolveu o processo
    	pronto->inicio = pronto->inicio->prox;    
		free(aux);
    }else {//se não resolveu
    	pronto->inicio = pronto->inicio->prox;
		pronto->fim->prox = aux;
        pronto->fim = aux;
        aux->prox = NULL;
	}
	
    return pronto;
}

/*  move UM ÚNICO processo da lista de PRONTO para esta, onde 
 *   o processo aguardará o usuário autorizá-lo a voltar para a FILA PRONTO
 *   deve ser "removido da CPU" ou seja, move o primeiro elemento do PRONTO
 *   e o retorna em último na FILA PRONTO
 */
LISTA* moveProntoParaDispositivo(LISTA *pronto, LISTA *dispositivo){
	
	if(pronto->inicio==NULL){
		printf("\nNão há como bloquear processo.\n");
		
	}else{
		Processo *aux1 = pronto->inicio;
		pronto->inicio = aux1->prox;	
		fflush(stdin);
		strcpy(aux1->estado, "Na Fila DISPOSITIVO");
		if(dispositivo->inicio==NULL){//se a dispositivo estiver vazia
			dispositivo->inicio = aux1;
			dispositivo->fim = aux1;
		}else{//se já tiver elemento
			dispositivo->fim->prox = aux1;
			dispositivo->fim = aux1;
		}
		dispositivo->fim->prox = NULL;
	}
	
	return pronto;
}

/* Move um único nó da FILA dispositivo para pronto. 
* Inserese no fim, independente do tamanho da pronto.
* Menor chance de ocorrer
*/ 
LISTA* moveDispositivoParaPronto(LISTA *pronto, LISTA *dispositivo){
	

	
	if(dispositivo->inicio==NULL){
		printf("\nNao ha como desbloquear processo.\n");
	}else{
		
		Processo *aux1 = dispositivo->inicio;
		Processo *aux2 = pronto->fim;
		
		fflush(stdin);
		strcpy(dispositivo->inicio->estado, "Na Fila PRONTO");
		if(pronto->inicio == NULL){
			pronto->inicio = aux1;
			pronto->fim = aux1;
			dispositivo->inicio = aux1->prox;
			aux1->prox = NULL;
		} else {
			dispositivo->inicio = dispositivo->inicio->prox;
			aux2->prox = aux1;
			aux1->prox = NULL;
		}
	}
	
	return dispositivo;
}

int main() {
    setlocale(LC_ALL, "portuguese");
    int opc = 0, sei = 0;
    int i, decide=0;
    srand(time(NULL));

    //declaração e inicialização das 3 FILAS solicitadas
    LISTA *jobs, *pronto, *dispositivo;

    jobs = criaLista();
    pronto = criaLista();
    dispositivo = criaLista();

    while (quantum > 5 || quantum < 1) {
        printf("\n\nSimulador de Processos de S.O. : \n\n");
        printf("\nInforme o valor do QUANTUM (MAX 5):\n");
        scanf("%d", &quantum);
        if (quantum > 5 || quantum < 1) {
            printf("\nQuantum inválido.\n");
            system("pause");
            system("cls");
        }
    }
	system("pause");
	while (1) {
    
		while(fazer==1){//Responsável por fazer as operações de forma automática e aleatória
        	system("cls");
        	//quando entrar neste laço, já cria um novo processo aleatório

        	sei = rand() % 10 + 1;
        	for (i = 0; i < sei ; i++)
        	    jobs = criaProcesso(jobs);
        	           	
       		if(decide==1){//na primeira iteração, ele NÃO joga na FILA PRONTO
			   
        		jobs = movePronto(jobs, pronto);
        		
        		pronto = resolveProcesso(pronto);
			}
			
        	if ( sei >= 8  &&  quantPronto >= 1) {//move para a dispositivo; garante que haja pelo menos um processo na fila PRONTO
            	printf("\nHouve interrupção!\n");
            	system("pause");
            	pronto = moveProntoParaDispositivo(pronto, dispositivo);
            	sleep(1);
        	}
        
			int quantDispositivo = contaDispositivo(dispositivo);
        
			if ( sei == 10  &&  quantDispositivo >= 1) {//move para a pronto; garante que haja pelo menos um processo na fila DISPOSITIVO
        	    printf("\nHouve desbloqueio de processos!\n");
        	    system("pause");
        	    dispositivo = moveDispositivoParaPronto(pronto, dispositivo);
        	    sleep(1);
        	}
			
        	fazer=0;
        	decide=1;
        	sleep(1);
		}
		system("cls");
		printf("\n QUANTUM:%d \n", quantum);
        printf("\n Menu: \n");
        printf("\n1 para continuar:\n");
        printf("\n2 para exibir JOBS:\n");
        printf("\n3 para exibir PRONTO:\n");
        printf("\n4 para exibir DISPOSITIVO:\n");
		printf("\n-1 para sair:\n");
        scanf("%d", &opc);
        if (opc < -1 || opc > 5) {
            printf("\nComando inválido!\n");
        } else {

            switch (opc) {

                case 1:
                    printf("\nRodando!\n");
                    fazer=1;
                    sleep(2);
                    break;
                case 2:
                    exibirJobs(jobs);
                    system("pause");
                    fazer = 0;
                    break;
   				case 3:
   					exibirPronto(pronto);
                    system("pause");
					fazer = 0;
					break;
   				case 4:
                    exibirDispositivo(dispositivo);
                    system("pause");
					fazer = 0;
					break;
                case -1:
                	fazer = 0;
                    printf("\nLimpando Listas...\n\n");
                    printf("---------------------\n");
                    limpa(jobs);
                    printf("-JOBS APAGADA-\n");
                    limpa(pronto);
                    printf("-PRONTO APAGADA-\n");
                    limpa(dispositivo);
                    printf("-DISPOSITIVO APAGADA-\n");
                    exit(1);
                    break;
                default :
                	printf("\nEntrada Inválida.\n");
                	break;
            }
        }

    }
    return 0;
}
