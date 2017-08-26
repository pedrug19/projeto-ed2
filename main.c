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
#include "tad.h"

int quantum = 10;
int quantPronto = 0;

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
            printf("|ID:%d \t\t", aux->id);
            aux = aux->prox;
        }
        printf("\n");
        aux = jobs->inicio;
        while (aux != NULL) {
            printf("|Tempo de CPU:%d \t", aux->tempoCPU);
            aux = aux->prox;
        }
        printf("\n");
        aux = jobs->inicio;
        while (aux != NULL) {
            printf("|Estado:%s \t", aux->estado);
            aux = aux->prox;
        }
        printf("\n");
    }

}

//recebe o INICIO de uma fila como parâmetro

void exibirPronto(LISTA *pronto) {

    if (pronto->inicio == NULL) {
        printf("\nLista de PRONTOS vazia.\n");
    } else {
        Processo *aux = pronto->inicio;

        printf("\n---FILA PRONTO---\n");


        if (aux == pronto->inicio) {

            printf("\nProcesso na CPU:\n");
            printf("\n________________\n");
            printf("|ID:%d \t\t", aux->id);
            printf("|Tempo de CPU:%d \t", aux->tempoCPU);
            printf("|Estado:%s \t", aux->estado);
            printf("\n________________\n");
            aux = aux->prox;

        } else {
            while (aux != NULL) {
                printf("|ID:%d \t\t", aux->id);
                aux = aux->prox;
            }
            printf("\n");
            aux = pronto->inicio->prox;
            while (aux != NULL) {
                printf("|Tempo de CPU:%d \t", aux->tempoCPU);
                aux = aux->prox;
            }
            printf("\n");
            aux = pronto->inicio->prox;
            while (aux != NULL) {
                printf("|Estado:%s \t", aux->estado);
                aux = aux->prox;
            }
            printf("\n");
        }
    }
}

//recebe o INICIO de uma fila como parâmetro
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
                printf("|Tempo de CPU:%d \t", aux->tempoCPU);
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

int contaPronto(LISTA *pronto) {
    int n;
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

int contaDispositivo(LISTA *dispositivo) {
    int n;
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

//função para criar um processo, deve inserir na fila JOBS
//e deve ser contínuo e aleatória

LISTA* criaProcesso(LISTA *l) {//Funciona!
    int ale, i;
    //gerar variação no ID
    for (i = 0; i < 2; i++) {
        ale = (rand() % 10000) + 1;
        //printf("\nFUNÇAO:%d", ale);
    }
    int aux_id = ale;
    int aux_stack = (rand() % 10) + 4;
    int aux_heap = (rand() % 10) + 6;
    int aux_data = (rand() % 10) + 8;
    float aux_tempo = (rand() % 5) + 5;
    char aux_estado[20];
    fflush(stdin); //limpa o buffer
    strcpy(aux_estado, "Na fila JOBS");

    /*
            printf("\nCriação de processo.\n");
            printf("\n%d\n",aux_id);
            printf("\n%d\n",aux_stack);
            printf("\n%d\n",aux_heap);
            printf("\n%d\n",aux_data);
            printf("\n%d\n",aux_tempo);
            printf("\n%s\n",aux_estado);
            system("pause");
     */

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

LISTA *movePronto(LISTA *jobs, LISTA *pronto) {//Arrumar
    Processo *aux = jobs->inicio;

    while (quantPronto < 6 && jobs->inicio != NULL) {
        /*  COMENTAR AQUI
         * 
         * 
         */
        jobs->inicio = aux->prox;
        if (pronto->fim == NULL) { //Se a fila JOBS estiver vazia
            pronto->inicio = aux;
            aux->prox = NULL;
            pronto->fim = aux;
        } else {
            pronto->fim->prox = aux;
            aux->prox = NULL;
            pronto->fim = aux;
        }
        aux = jobs->inicio;
        quantPronto++;
    }

    return pronto;
}

LISTA *resolveProcesso(LISTA *pronto) {//Aparentemente certa

    Processo *aux = pronto->inicio;

    printf("\nResolução do processo\n");
    printf("\n%d\n", aux->id);
    printf("\n%d\n", aux->stack);
    printf("\n%d\n", aux->heap);
    printf("\n%d\n", aux->data);
    printf("\n%d\n", aux->tempoCPU);
    printf("\n%s\n", aux->estado);
    system("pause");

    aux->tempoCPU = aux->tempoCPU - quantum; //"resolve" o processo
    if (aux->tempoCPU <= 0) {//se resolveu o processo
        removeProcesso(aux);
    } else {//se não resolveu
        pronto->fim->prox = aux; //fim aponta para o processo não acabado
        aux = aux->prox; //vai pro fim da fila
    }

    printf("\nPróximo processo a ser executado será:\n");
    printf("\n%d\n", aux->id);
    printf("\n%d\n", aux->stack);
    printf("\n%d\n", aux->heap);
    printf("\n%d\n", aux->data);
    printf("\n%d\n", aux->tempoCPU);
    printf("\n%s\n", aux->estado);
    system("pause");

    return pronto;
}

/*  move UM ÚNICO processo da lista de PRONTO para esta, onde 
 *   o processo aguardará o usuário autorizá-lo a voltar para a FILA PRONTO
 *   deve ser "removido da CPU" ou seja, move o primeiro elemento do PRONTO
 *   e o retorna em último na FILA PRONTO
 */
LISTA* moveProntoParaDispositivo(LISTA *pronto, LISTA *dispositivo) { // Testado e funcionando
    Processo *aux1 = pronto->inicio;
    Processo *aux2 = dispositivo->inicio;

    if (pronto->inicio == NULL) {
        printf("\nNão há como bloquear processo.\n");

    } else {
        if (dispositivo->inicio == NULL) { //Se a fila de dispositivo estiver vazia!
            dispositivo->inicio = aux1;
            dispositivo->fim = aux1;
            dispositivo->fim->prox = NULL;
            pronto->inicio = pronto->inicio->prox;
        } else {
            dispositivo->fim = aux1;
            dispositivo->fim->prox = NULL;
            pronto->inicio = pronto->inicio->prox;
        }
    }

    return dispositivo;
}

LISTA* moveDispositivoParaPronto(LISTA *pronto, LISTA *dispositivo) {
    Processo *aux1 = pronto->fim;
    Processo *aux2 = dispositivo->inicio;
    if (dispositivo->inicio == NULL) {
        printf("\nNao ha como desbloquear processo.\n");
    } else {
        pronto->fim = dispositivo->inicio;
        pronto->fim->prox = NULL;
        dispositivo->inicio = dispositivo->inicio->prox;
    }
}

Processo *removeProcesso(Processo *l) {//recebe o inicio de PRONTO e retira UM elemento

    if (l == NULL) {
        printf("\nNada a remover.\n");
    } else {
        Processo *aux = l; //aux é o INICIO da FILA
        l = l->prox;
        free(aux);
    }
    return l;
}


//limpa os buffers

void limpa(LISTA *l) {
    Processo *aux = l->inicio;
    while (l->inicio != NULL) {
        aux = l->inicio;
        l->inicio = l->inicio->prox;
        free(aux);
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    int opc = 0, sei = 0;
    int i;
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
        system("cls");
        //quando entrar neste laço, já cria um novo processo aleatório

        sei = rand() % 10 + 1; //ta certo
        for (i = 0; i < sei; i++)
            jobs = criaProcesso(jobs);

        quantPronto = contaPronto(pronto); //conta quantos elementos tem no FILA PRONTO
        printf("Quantidade na FILA PRONTO:%d", quantPronto); //tudo certo até aqui



        //---------------------------------------------------------------------------------------------------------------------
        if (quantPronto < 5) {// a FILA PRONTO suporta apenas 5 processos carregados na memória proncipal
            pronto = movePronto(jobs, pronto);
            printf("\ninserindo na PRONTO\n");
        }
        printf("Quantidade na FILA PRONTO:%d", quantPronto);
        system("pause");
        pronto = resolveProcesso(pronto);

        /*
        //aleatoriedade
        for(i=0;i<2;i++){
                sei = (rand()%10)+1;
        }
         */

        if (sei == 10 && quantPronto > 1) {//move para a dispositivo; garante que haja pelo menos um processo na fila PRONTO
            printf("\nHouve interrupção!\n");
            dispositivo = moveProntoParaDispositivo(pronto, dispositivo);
            sleep(1);
        }

        int quantDispositivo = contaDispositivo(dispositivo);
        if (sei == 9 && quantDispositivo > 1) {//move para a pronto; garante que haja pelo menos um processo na fila DISPOSITIVO
            printf("\nHouve desbloqueio de processos!\n");
            pronto = moveDispositivoParaPronto(pronto, dispositivo);
            sleep(1);
        }

        sleep(1);

        exibirJobs(jobs);
        exibirPronto(pronto);
        exibirDispositivo(dispositivo);


        printf("\n Menu: \n");
        printf("\n1 para continuar:\n");
        printf("-1 para sair:");
        scanf("%d", &opc);
        if (opc < -1 || opc > 3) {
            printf("\nComando inválido!\n");
        } else {

            switch (opc) {

                case 1:
                    printf("\nRodando!\n");
                    sleep(2);
                    break;
                case -1:
                    printf("\nLimpando Listas...\n");
                    limpa(jobs);
                    limpa(pronto);
                    limpa(dispositivo);
                    exit(1);
                    break;
            }
        }

    }
    return 0;
}