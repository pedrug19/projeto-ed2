# Projeto de ED2

Criar filas de processos (Job, Pronto, Dispositivo), mais ou menos essa estrutura:

FILA DE ESCALONAMENTO ED2

FILA JOBS (RECEBE PROCESSOS CRIADOS) ----> FILA PRONTO (RECEBE PROCESSOS PARADOS PARA EXECUÇÃO ---> FILA DISPOSITIVO (EXECUÇÃO) ---> FILA PRONTO ---> .......

************************************************************************************************************

* ESTRUTURA DE PROCESSOS:



		TYPEDEF STRUCT PROCESSOS{
			PONTEIRO DA PILHA;
			STATUS;
			ID;
		} PROCESSOS;



* PROCESSOS TEM TEMPO DE EXECUÇÃO E CONTADOR

* DAQUI 15 DIAS...

* 2 semanas: 15/8/2017 para o dia 29/8/2017
