#include <stdio.h>
#include <stdlib.h>
#include "Dllist.h"

#define TRUE 1
#define FALSE 0

typedef struct _dllnode_{
  void* data;
  struct _dllnode_ *next;
  struct _dllnode_ *prev;
}DLLNode;

typedef struct _dllist_{
  DLLNode *first;
  DLLNode *cur; //Para fazer o interador, isto é, listar todos os nós da lista
}DLList;


//Criar uma LDE vazia
DLList *dllCreate(){
  DLList *l;
  l = (DLList*)malloc(sizeof(DLList));
  if(l != NULL){
    l -> first = NULL;
    l -> cur = NULL;
    return l;
  }
  return NULL;
}

//Destruir uma LDE vazia
int dllDestroy(DLList *l){
  if(l != NULL){
    if(l -> first == NULL){
      free(l);
      return TRUE;
    }
  }
  return FALSE;
}

//Destruir uma LDE mesmo quando ela não está vazia
/*
int dllDestroyNotEmpty(DLList *l, int(myFree)(void*)){
  DLLNode *cur, *prev;
  if(l != NULL){
    if(l -> first != NULL){
      cur = l -> first;
      while(cur != NULL){
        myFree(cur -> data);
        prev = cur;
        cur = cur -> next;
        free(prev);
      }
    }
    free(l);
    return TRUE;
  }
  return FALSE;  
}
*/

//Inserir elemento como primeiro da LDE
int dllInsertAsFirst(DLList *l, void* data){
  DLLNode *newNode;
  if(l != NULL){
    newNode = (DLLNode*)malloc(sizeof(DLLNode));
    if(newNode != NULL){
      newNode -> prev = NULL;
      newNode -> data = data;
      newNode -> next = l -> first;
      if(l -> first != NULL){
        l -> first -> prev = newNode;
      }
      l -> first = newNode;
      return TRUE;
    }
  }
  return FALSE;
}

//Inserir elemento como último da LDE
int dllInsertAsLast(DLList *l, void* data){
  DLLNode *newNode, *last;
  last = NULL;
  if(l != NULL){
    newNode = (DLLNode*)malloc(sizeof(DLLNode));
    if(newNode != NULL){
      newNode -> data = data;
      newNode -> next = NULL;
      if(l -> first != NULL){
        last = l -> first;
        while(last -> next != NULL){
          last = last -> next;
        }
      }
      newNode -> prev = last;
      if(last != NULL){
        last -> next = newNode;
      }else{
        l -> first = newNode;
      }
      return TRUE;
    }
  }
  return FALSE;
}


//Inserir um elemento após o elemento especificado por uma chave key (dado)
int dllInsertAfterSpec(DLList *l, void* key, void* data, int(*cmp)(void*, void*)){
  DLLNode *newNode, *spec, *nextNode;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      spec = l -> first;
      status = cmp(spec -> data, key);
      while(status != TRUE && spec -> next != NULL){
        spec = spec -> next;
        status = cmp(spec -> data, key);
      }
      if(status == TRUE){
        newNode = (DLLNode*)malloc(sizeof(DLLNode));
        if(newNode != NULL){
          newNode -> data = data;
          newNode -> prev = spec;
          nextNode = spec -> next;
          newNode -> next = nextNode;
          if(nextNode != NULL){
            nextNode -> prev = newNode;
          }
          spec -> next = newNode;
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}


//Inserir um elemento antes do elemento especificado por uma chave key (dado)
int dllInsertBeforeSpec(DLList *l, void* key, void* data, int(*cmp)(void*, void*)){
  DLLNode *newNode, *spec, *before;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      spec = l -> first;
      status = cmp(spec -> data, key);
      while(status != TRUE && spec -> next != NULL){
        spec = spec -> next;
        status = cmp(spec -> data, key);
      }
      if(status == TRUE){
        newNode = (DLLNode*)malloc(sizeof(DLLNode));
        if(newNode != NULL){
          newNode -> data = data;
          newNode -> next = spec;
          before = spec -> prev;
          newNode -> prev = before;
          spec -> prev = newNode;
          if(before != NULL){
            before -> next = newNode;
          }else{
            l -> first = newNode;
          }
        }
        return TRUE;
      }
    }
  }
  return FALSE;
}


//Remover um nó da lista especificado
void* dllRemoveSpec(DLList *l, void* key, int(*cmp)(void*, void*)){
  DLLNode *spec, *nextNode, *prevNode;
  void* data;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      spec = l -> first;
      status = cmp(spec -> data, key);
      while(status != TRUE && spec -> next != NULL){
        spec = spec -> next;
        status = cmp(spec -> data, key);
      }
      if(status == TRUE){
        data = spec -> data;
        prevNode = spec -> prev;
        nextNode = spec -> next;
        if(prevNode != NULL){
          prevNode -> next = nextNode;
        }else{
          l -> first = nextNode;
        }
        if(nextNode != NULL){
          nextNode -> prev = prevNode;
        }
        free(spec);
        return data;
      }
    }
  }
  return NULL;
}

//Inserir um nó antes do anterior a um nó especificado pela chave
int dllInsertBefBefSpec(DLList *l, void* key, void* data, int(*cmp)(void*, void*)){
  DLLNode *newNode, *spec, *before, *prevNode;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      before = NULL;
      spec = l -> first;
      status = cmp(spec -> data, key);
      while(status != TRUE && spec -> next != NULL){
        before = spec;
        spec = spec -> next;
        status = cmp(spec -> data, key);
      }
      if(status == TRUE && before != NULL){
        newNode = (DLLNode*)malloc(sizeof(DLLNode));
        if(newNode != NULL){
          newNode -> data = data;
          newNode -> next = before;
          prevNode = before -> prev;
          newNode -> prev = prevNode;
          before -> prev = newNode;
          if(prevNode != NULL){
            prevNode -> next = newNode;
          }else{
            l -> first = newNode;
          }
        }
        return TRUE;
      }
    }
  }
  return FALSE;
}

//Remover um nó após um nós especificado pela chave
void* dllRemoveAfterSpec(DLList *l, void* key, int(*cmp)(void*, void*)){
  DLLNode *spec, *current,*nextNode;
  void* data;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      spec = l -> first;
      status = cmp(spec -> data, key);
      while(status != TRUE && spec -> next != NULL){
        spec = spec -> next;
        status = cmp(spec -> data, key);
      }
      if(status == TRUE && spec -> next != NULL){
        current = spec -> next;
        data = nextNode -> data;
        if(current -> next != NULL){
          nextNode = current -> next;
          spec -> next = nextNode;
          nextNode -> prev = spec;
        }else{
          spec -> next = current -> next;
        }
        free(current);
        return data;
      }
    }
  }
  return NULL;
}

//Buscar um elemento na lista circular duplamente encadeada
void* dllQuery(DLList *l, void* key, int(*cmp)(void*,void*)){
  DLLNode *current;
  int status;
  if(l != NULL){
    if(l -> first != NULL){
      current = l -> first;
      status = cmp(current -> data, key);
      while(status != TRUE && current -> next != NULL){
        current = current -> next;
        status = cmp(current -> data, key);        
      }
      if(status == TRUE){
        return current -> data;
      }
    }
  }
  return NULL;
}


//Pegar o primeiro elemento da lista duplamente encadeada
void* dllGetFirst(DLList *l){
  DLLNode *first;
  if(l != NULL){
    if(l -> first != NULL){
      l -> cur = l -> first;
      first = l -> cur;
      return first -> data; 
    }
  }
  return NULL;
}

//Pegar o proximo elemento da lista duplamente encadeada
void* dllGetNext(DLList *l){
  DLLNode *next;
  if(l != NULL){
    next = l -> cur;
    if(next -> next != NULL){
      l -> cur = next -> next;
      return l -> cur -> data;
    }
  }
  return NULL;
}

//Verificar se uma lista duplamente encadeada está vazia
int dllIsEmptty(DLList *l){
  if(l != NULL){
    if(l -> first == NULL){
      return TRUE;
    }
  }
  return FALSE;
}

//Esvaziar uma lista duplamente encadeada
int dllClean(DLList *l){
  DLLNode *current, *aux;
  if(l != NULL){
    if(l -> first != NULL){
      current = l -> first;
      while(current -> next != NULL){
        aux = current;
        current = current -> next;
        free(aux);
      }
      free(current);
      l -> first = NULL;
      return TRUE;
    }
  }
  return FALSE;
}