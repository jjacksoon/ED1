#include "Dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef struct _aluno_ {
  int matricula;
  char nome[30];
  float nota;
} Aluno;

// Função para definir o MENU do programa
void menu() {
  printf("\n-------MENU PRINCIPAL-------\n[1] - Criar uma lista;\n[2] - "
         "Inserir aluno na lista;\n[3] - Remover aluno da lista;\n[4] - "
         "Consultar aluno na lista;\n[5] - Listar elementos da lista;\n[6] - "
         "Destruir a lista;\n[7] - Esvaziar a lista;\n[0] - Encerrar o "
         "programa\nDigite aqui sua opcao: ");
}

// Funcao comparar matricula de aluno
int comparaMatriculaDeAluno(void *item, void *matChave) {
  Aluno *aluno;
  int *matricula;
  aluno = (Aluno *)item;       // ponteiro para uma estrutura do tipo aluno
  matricula = (int *)matChave; // ponteiro para um inteiro

  if (aluno->matricula == *matricula) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// Funcao comparar nome de aluno
int comparaNomeDeAluno(void *item, void *nomeChave) {
  Aluno *aluno;
  char *nome;
  aluno = (Aluno *)item;    // ponteiro para uma estrutura do tipo aluno
  nome = (char *)nomeChave; // ponteiro para um char

  if (strcmp(aluno->nome, nome) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// Função myFree
int myFree(void *item) {
  Aluno *aluno;
  aluno = (Aluno *)item;
  free(aluno);
  return TRUE;
}

int main() {
  DLList *lista;
  Aluno *aluno;
  int opMenu, option = -1, colExiste = FALSE;

  do {
    menu();
    scanf("%d", &opMenu);
    switch (opMenu) {
    case 1: // Criar colecao
      if (colExiste == FALSE) {
        lista = dllCreate();
        if (lista != NULL) {
          printf("Lista criada com sucesso!\n");
          colExiste = TRUE;
        } else {
          printf("Não foi possível criar a lista.\n");
        }
      } else {
        printf("Uma lista já foi criada.\n");
      }
      break;

    case 2: // inseri aluno na colecao
      if (colExiste == TRUE && lista != NULL) {
        // Criando uma estrutura do tipo Aluno - alocando uma estrutura do tipo
        // Aluno
        aluno = (Aluno *)malloc(sizeof(Aluno));
        if (aluno != NULL) {
          int alunoInserido;
          printf("\n----- CADASTRO DO ALUNO ----\n");
          printf("Matricula do aluno: ");
          scanf("%d", &(aluno->matricula));
          printf("Nome do aluno: ");
          getchar();
          fgets(aluno->nome, 30, stdin);
          printf("Nota: ");
          scanf("%f", &aluno->nota);

          alunoInserido = dllInsertAsLast(lista, (void *)aluno);

          if (alunoInserido == TRUE) {
            printf("Aluno inserido na lista.\n");
          } else {
            printf("Erro ao inserir aluno na lista\n");
          }
        }
      } else {
        printf("É preciso criar primeiro uma lista.\n");
      }
      break;

    case 3: // Remover aluno na colecao
      if (colExiste == TRUE && lista != NULL) {
        int matricula, opcao;
        Aluno *alunoRemovido;
        char nome[30];

        while (TRUE) {
          printf("\nRemover por:\n[1] - Matrícula;\n[2] - Nome;\n");
          printf("Digite a opção: ");
          scanf("%d", &opcao);

          if (opcao == 1) {
            printf("Insira o numero da matricula do aluno: ");
            scanf("%d", &matricula);
            alunoRemovido = (Aluno *)dllRemoveSpec(lista, (void *)&matricula,
                                                   comparaMatriculaDeAluno);
            break;
          } else if (opcao == 2) {
            printf("Insira o nome do aluno: ");
            getchar();
            fgets(nome, 30, stdin);
            alunoRemovido =
                (Aluno *)dllRemoveSpec(lista, (void *)nome, comparaNomeDeAluno);
            break;
          } else {
            printf("Opção inválida.\n");
            continue;
          }
        }

        if (alunoRemovido != NULL) {
          printf("O aluno foi removido\n");
          printf("-------------------------\n");
          printf("Matricula: %d\n", alunoRemovido->matricula);
          printf("Nome: %s", alunoRemovido->nome);
          printf("Nota: %.2f\n", alunoRemovido->nota);
        } else {
          printf("Não foi possível remover o aluno da lista. Verifique se "
                 "matricula ou nome estao corretos.\n");
        }
      } else {
        printf("É necessário criar uma lista.\n");
      }
      break;

    case 4: // Consultar um aluno da colecao
      if (colExiste == TRUE && lista != NULL) {
        int matricula, opcao;
        char nome[30];

        while (TRUE) {
          printf("\nConsultar por:\n[1] - Matrícula;\n[2] - Nome;\n");
          printf("Digite a opção: ");
          scanf("%d", &opcao);

          if (opcao == 1) {
            printf("Insira o numero da matricula do aluno: ");
            scanf("%d", &matricula);
            aluno = (Aluno *)dllQuery(lista, (void *)&matricula,
                                      comparaMatriculaDeAluno);
            break;
          } else if (opcao == 2) {
            printf("Insira o nome do aluno: ");
            getchar();
            fgets(nome, 30, stdin);
            aluno = (Aluno *)dllQuery(lista, (void *)nome, comparaNomeDeAluno);
            break;
          } else {
            printf("Opção inválida.\n");
            continue;
          }
        }

        if (aluno != NULL) {
          printf("\nAluno encontrado!\n");
          printf("-------------------------\n");
          printf("Matricula: %d\n", aluno->matricula);
          printf("Nome: %s", aluno->nome);
          printf("Nota: %.2f\n", aluno->nota);
        } else {
          printf("Nenhum aluno encontrado!");
        }
      } else {
        printf("É necessário criar uma colecao.\n");
      }
      break;

    case 5: // Listar elementos da lista
      if (colExiste == TRUE && lista != NULL) {
        aluno = (Aluno *)dllGetFirst(lista);
        if (aluno != NULL) {
          int indiceAluno = 1;
          while (aluno != NULL) {
            printf("\n---- Aluno %d ----\n", indiceAluno);
            printf("Nome: %s", aluno->nome);
            printf("Matricula: %d\n", aluno->matricula);
            printf("Nota: %.2f\n", aluno->nota);
            aluno = (Aluno *)dllGetNext(lista);
            indiceAluno++;
          }
        } else {
          printf("Lista vazia!\n");
        }
      } else {
        printf("É necessário criar uma colecao.\n");
      }
      break;

    case 6: // Destruir a colecao
      if (colExiste == TRUE && lista != NULL) {
        int colApagada;
        int listaVazia;
        listaVazia = dllIsEmptty(lista);
        if (listaVazia == TRUE) {
          colApagada = dllDestroy(lista);
        } else {
					printf("É necessário esvaziar a lista.\n");
          //colApagada = dllDestroyNotEmpty(lista, myFree);
        }
        if (colApagada == TRUE) {
          printf("A lista foi destruida.\n");
          colExiste = FALSE;
        }
      } else {
        printf("É preciso criar primeiro uma lista.\n");
      }
      break;

    case 7: // Esvaziar a colecao
      if (colExiste == TRUE && lista != NULL) {
        int vazia = dllClean(lista);
        if (vazia == TRUE) {
          printf("Todos os itens foram apagados.\n");
        } else {
          printf("lista já está vazia.\n");
        }
      } else {
        printf("É preciso criar primeiro uma lista.\n");
      }
      break;

    case 0:
      printf("Encerrando programa....\n");
      sleep(3);
      printf("------Programa encerrado. Obrigado.------");
      break;

    default:
      printf("Opcao invalida. Tente novamente!\n");
    }

  } while (opMenu != 0);
  return 0;
}