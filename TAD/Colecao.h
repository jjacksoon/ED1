/*-------------------------------------------------------------------------------------------------------
Colecao.h - arquivo com as especificações para o TAD Colecao, tipo de dado para uma colecão do tipo void

Autores: Jackson Silva Nascimento e Pedro Rocha Boucinhas Pacheco
Ano: 2021
--------------------------------------------------------------------------------------------------------*/

#ifndef _COLECAO_H   //pré processamento
#define _COLECAO_H

//Evitando que o arquivo seja inserido mais de uma vez
/*----------------------------------
  Definições Locais
----------------------------------*/
typedef struct _colecao_ Colecao;


/*----------------------------------------------------
  Funções que implementam as operações do TAD Colecao
------------------------------------------------------*/

//Criar colecao
Colecao *colCreate(int n);

//Inserir elemento na colecao
int colInsert(Colecao *colecao, void* item);

//Remover elemento da colecao
void* colRemove(Colecao *colecao, void* chave, int(*comparacao)(void*, void*));
 //int(*comparacao)(void*, void*) - ponteiro para funcao comparacao que recebe dois void* e retorna uma variavel do tipo inteiro
 
//Buscar elemento na colecao
void* colQuery(Colecao *colecao, void* chave, int(*comparacao)(void*,void*));

//Limpar a colecao
int colClean(Colecao *colecao);

//Destruir a colecao
int colDestroy(Colecao *colecao);

//Pegar o primeiro elemento da colecao
void* colGetFirst(Colecao *colecao);

//Pegar o proximo elemento da colecao
void* colGetNext(Colecao *colecao);

#endif