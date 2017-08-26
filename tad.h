/*
 *   Execício 1 - Lab_ED2 
 *   Autores:
 *   Gustavo Molina
 *   Gabriel Vinícius
 *   Luis Marcello 
 *   Pedrenrique Gonçalves
 */

#ifndef TAD_H
#define TAD_H

#ifdef __cplusplus
extern "C" {
#endif

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

void limpa(LISTA *l);
Processo *removeProcesso(Processo *l);
LISTA *criaLista();
void exibirJobs(LISTA *jobs);
void exibirPronto(LISTA *pronto);
void exibirDispositivo(LISTA *Dispositivo);
int contaPronto(LISTA *pronto);
int contaDispositivo(LISTA *dispositivo);
LISTA* criaProcesso(LISTA *l);
LISTA *movePronto(LISTA *jobs, LISTA *pronto);
LISTA *resolveProcesso(LISTA *pronto);
LISTA* moveProntoParaDispositivo(LISTA *pronto, LISTA *dispositivo);
LISTA* moveDispositivoParaPronto(LISTA *pronto, LISTA *dispositivo);
Processo *removeProcesso(Processo *l);
void limpa(LISTA *l);


#ifdef __cplusplus
}
#endif

#endif /* TAD_H */

