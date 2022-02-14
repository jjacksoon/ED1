#ifndef _COLECAO_C   //pré processamento
#define _COLECAO_C

#include <stdlib.h>
#include <stdio.h>
#include "Colecao.h"

#define TRUE 1
#define FALSE 0

//Defininindo minha estrutura que vai ter as variáveis que vou usar no armazenamento
typedef struct _colecao_{
  int quantItens;
  int quantMaxItens;
  int atual;
  void **item;    //ponteiro item do tipo void* para armazenamento dos endereços dos elementos da minha coleção sem querer saber o tipo
}Colecao;

Colecao *colCreate(int n){ 
  //n - tamanho da colecao
  Colecao *colecao;   //ponteiro *colecao do tipo colecao
  if(n > 0){
    colecao = (Colecao *)malloc(sizeof(Colecao*)); //Criando uma colecao (alocando uma estrutura do tipo colecao)
    if(colecao != NULL){
      colecao -> item = (void**)malloc(sizeof(void*)*n); //alocando o vetor (ponteiro) item de dentro da colecao - dentro da minha struct colecao eu tenho uma variável que é um ponteiro e eu vou alocar esse vetor (Quero mexer no campo item da estrutura do tipo struct _colecao_ cujo endereço está na variavel *colecao do tipo Colecao)
      colecao -> quantItens = 0;
      colecao -> quantMaxItens = n;
      colecao -> atual = 0;   //inicializando a variável atual com zero para ser utilizada futuramente nas funções getFirst, getNext
      return colecao;
    }
    free(colecao);
  }
  return NULL;
}

int colInsert(Colecao *colecao, void* item){
  if(colecao != NULL){
    if(colecao -> quantItens < colecao -> quantMaxItens){ //Se a colecao não estiver cheia
      colecao -> item[colecao -> quantItens] = item; //item é colocado na posicao livre da colecao que não tem nenhum elemento, isto é, em colecao -> quantItens
      colecao -> quantItens++;
      return TRUE;
    }
  }
  return FALSE;
}


void* colRemove(Colecao *colecao, void* chave, int(*comparacao)(void*, void*)){
 //int(*comparacao)(void*, void*) - ponteiro para funcao comparacao que recebe dois void* e retorna uma variavel do tipo inteiro

  int i, status;
  void* dadoEncontrado;
  if(colecao != NULL){
    if(colecao -> quantItens > 0){
      i=0;
      for(i=0; i < colecao -> quantItens; i++){
        status = comparacao(colecao -> item[i], chave);
        if(status == TRUE){
          dadoEncontrado = colecao -> item[i];
          for(int j=i; j < colecao -> quantItens; j++){   //colocando os elementos abaixo do meu elemento a ser removido em uma posição anterior ao que eles estavam
            colecao -> item[j] = colecao -> item[j+1];
          }
            colecao -> quantItens--;
            return dadoEncontrado;
        }
      }
    }
  }
  return NULL;
}

void* colQuery(Colecao *colecao, void* chave, int(*comparacao)(void*,void*)){
  //int(*comparacao)(void*, void*) - ponteiro para funcao comparacao que recebe dois void* e retorna uma variavel do tipo inteiro

  int i, status;
  if(colecao != NULL){
    if(colecao -> quantItens > 0){   //se a colecao não está vazia
      i=0;
      for(int i=0; i < colecao -> quantItens; i++){
        status = comparacao(colecao -> item[i],chave);
        if(status == TRUE){
          return colecao -> item[i];
        }
      }
    }
  }
    return NULL;
}

int colClean(Colecao *colecao){
  if(colecao != NULL){
    if(colecao -> quantItens > 0){ //se a colecao não estiver vazia eu faço a limpeza
      for(int i=0; i < colecao -> quantItens; i++){ //vai de zero até i < quantItens da colecao
        colecao -> item[i] = NULL;    //cada item da minha colecao vai receber NULL
      }
      colecao -> quantItens = 0;    //colocar a quantidade de itens da minha colecao em zero
      return TRUE;
    }
  }
  return FALSE;
}

int colDestroy(Colecao *colecao){
  if(colecao != NULL){
    if(colecao -> quantItens == 0){   //Se a colecao estiver vazia
      free(colecao -> item);    //Desmontando de cima para baixo: primeiro o ponteiro do tipo void* para armazenamento dos elementos da minha colecao sem saber o tipo
      free(colecao);    //ponteiro do tipo colecao
      return TRUE;
    }
  }
  return FALSE;
}

void* colGetFirst(Colecao *colecao){
  if(colecao != NULL){
    if(colecao -> quantItens > 0){    //Se a colecao tiver pelo menos um elemento
      colecao -> atual = 0;   //variavel atual recebe zero 
      return colecao -> item[colecao -> atual]; //retorno o primeiro item da colecao, isto é, o item na posicao zero que é item[colecao -> atual]
    }
  }
  return NULL;
}

void* colGetNext(Colecao *colecao){
  if(colecao != NULL){
    colecao -> atual++;   //incremento a variável atual
    if(colecao -> atual < colecao -> quantItens){   //verifico se a variavel atual do meu ponteiro colecao é menor que a quantidade de itens da minha colecao (ex: se minha colecao tem 3 itens, verifico se atual < 3)
      return colecao -> item[colecao -> atual];
    }
  }
  return NULL;
}

#endif