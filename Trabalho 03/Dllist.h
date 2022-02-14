#ifndef _DLLIST_H_
#define _DLLIST_H_

typedef struct _dllist_ DLList;
typedef struct _dllnode_ DLLNode;

//Criar uma LDE
DLList *dllCreate(void);

//Destruir uma LDE vazia
int dllDestroy(DLList *l);

//Destruir uma LDE mesmo quando ela não está vazia
//int dllDestroyNotEmpty(DLList *l, int(myFree)(void*));

//Inserir elemento como primeiro da LDE
int dllInsertAsFirst(DLList *l, void* data);

//Inserir elemento como último da LDE
int dllInsertAsLast(DLList *l, void* data);

//Inserir um elemento após o elemento especificado por uma chave key
int dllInsertAfterSpec(DLList *l, void *key, void* data, int(*cmp)(void*, void*));

//Inserir um elemento antes do elemento especificado por uma chave key (dado)
int dllInsertBeforeSpec(DLList *l, void *key, void* data, int(*cmp)(void*, void*));

//Remover um nó da lista especificado
void* dllRemoveSpec(DLList *l, void *key, int(*cmp)(void*, void*));

//Inserir um nó antes do anterior a um nó especificado pela chave
int dllInsertBefBefspec(DLList *l, void* key, void* data, int(*cmp)(void*, void*));

//Remover um nó após um nós especificado pela chave
void* dllRemoveAfterSpec(DLList *l, void* key, int(*cmp)(void*, void*));

//Buscar um elemento na lista circular duplamente encadeada
void* dllQuery(DLList *l, void* key, int(*cmp)(void*,void*));

//Pegar o primeiro elemento da lista duplamente encadeada
void* dllGetFirst(DLList *l);

//Pegar o proximo elemento da lista duplamente encadeada
void* dllGetNext(DLList *l);

//Verificar se uma lista duplamente encadeada está vazia
int dllIsEmptty(DLList *l);

//Esvaziar uma lista duplamente encadeada
int dllClean(DLList *l);

#endif