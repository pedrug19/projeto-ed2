# Projeto de ED2

Criar filas de processos (Job, Pronto, Dispositivo), mais ou menos essa estrutura:

FILA DE ESCALONAMENTO ED2


											                             {   /-->{ FILA PRONTO: RECEBE PROCESSOS DE JOB --->\
											                             {  /	 										                           \			
FILA JOB: ID1231, ID23131, ID1232132, ID232424 --> { /													                        \
											                             { \												                           \
											                             {  \<--{ FILA EXECUÇÃO: RECEBE PROCESSOS DE PRONTO  <--\

************************************************************************************************************

>>> ESTRUTURA DE PROCESSOS:

STRUCT PROCESSOS{
	PONTEIRO DA PILHA;
	STATUS;
	ID;	
} PROCESSOS;

>>> PROCESSOS TEM TEMPO DE EXECUÇÃO E CONTADOR

>>> DAQUI 15 DIAS...

>>> 2 semanas: 15/8/2017 para o dia 29/8/2017
