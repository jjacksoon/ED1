#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Colecao.h"

#define TRUE 1
#define FALSE 0

//Definição das variáveis que vou usar na minha estrutura do tipo Aluno para realizar esse armazenamento
typedef struct _aluno_{
  int matricula;
  char nome[30];
  float nota;
}Aluno;

//Função para definir o MENU do programa
void menu(){
  	printf("\n-------MENU PRINCIPAL-------\n[1] - Criar uma colecao;\n[2] - Inserir aluno na colecao;\n[3] - Remover aluno da colecao;\n[4] - Consultar aluno na colecao;\n[5] - Listar elementos da colecao;\n[6] - Destruir a colecao;\n[7] - Esvaziar a colecao;\n[0] - Encerrar o programa\nDigite aqui sua opcao: ");
}

 //int(*comparacao)(void*, void*) - ponteiro para funcao comparacao que recebe dois void* e retorna uma variavel do tipo inteiro


//Funcao comparar matricula de aluno
int comparaMatriculaDeAluno(void* item, void* matChave){
  Aluno *aluno;
  int *matricula;
  aluno = (Aluno*)item; //ponteiro para uma estrutura do tipo aluno
	matricula = (int*)matChave; //ponteiro para um inteiro
	
  if(aluno -> matricula == *matricula){
    return TRUE; 
  }else{
		return FALSE;
	}
}

//Funcao comparar nome de aluno
int comparaNomeDeAluno(void* item, void* nomeChave){
	Aluno *aluno;
  char *nome;
  aluno = (Aluno*)item; //ponteiro para uma estrutura do tipo aluno
	nome = (char*)nomeChave; //ponteiro para um char

	if(strcmp(aluno -> nome, nome) == 0){ //comparando as duas strings nome do aluno na minha estrutura aluno e o nome passado como chave para o ponteiro do tipo char *nome
  /*
    -1 indicando que o parâmetro 1 é menor que o parâmetro 2;
    0 indicando que os parâmetros são iguais;
    1 caso o primeiro seja maior que o segundo parâmetro.
*/
    return TRUE; 
  }else{
		return FALSE;
	}
}

int main() {
  Colecao *colecao;
  Aluno *aluno;
  int opMenu, option = -1, colExiste = FALSE;

  do{
    menu();
    scanf("%d", &opMenu);
    switch(opMenu){
      case 1: //Criar colecao
      if(colExiste == FALSE){
        int quantidade;
        printf("Quantidade de elementos que serão adicionados na colecao: ");
        scanf("%d", &quantidade);
        colecao = colCreate(quantidade);
        if(colecao != NULL){
          printf("Colecao criada com sucesso!\n");
          colExiste = TRUE;
        }else{
          printf("Não foi possível criar a colecao.\n");
        }
      }else{
        printf("Uma colecao já foi criada.\n");
      }
      break;

      case 2: //inseri aluno na colecao
      if(colExiste == TRUE && colecao != NULL){
      //Criando uma estrutura do tipo Aluno - alocando uma estrutura do tipo Aluno
        aluno = (Aluno *)malloc(sizeof(Aluno));
        if(aluno != NULL){
          int alunoInserido;
          printf("\n----- CADASTRO DO ALUNO ----\n");
          printf("Matricula do aluno: ");
          scanf("%d", &(aluno -> matricula));
          printf("Nome do aluno: ");
          getchar();
          fgets(aluno->nome, 30, stdin);
          printf("Nota: ");
          scanf("%f", &aluno->nota);
            //fgets() - leitura de uma string a partir do teclado, usando a função fgets(variavel onde a string lida será salva, tamanho da string, de onde será lido - nesse caso do teclado é passado a constante definida em C stdin)
         

          alunoInserido = colInsert(colecao, (void*) aluno);

          if(alunoInserido == TRUE){
            printf("Aluno inserido na colecao.\n");
          }else{
            printf("Coleção cheia. Não foi possivel inserir o aluno.\n");
          }

        }
      }else{
        printf("É preciso criar primeiro uma colecao.\n");
      }
      break;

      case 3: //Remover aluno na colecao
      if(colExiste == TRUE && colecao != NULL){
        int matricula, opcao;
        Aluno* alunoRemovido;
				char nome[30];

        while(TRUE){
          printf("\nRemover por:\n[1] - Matrícula;\n[2] - Nome;\n");
          printf("Digite a opção: ");
          scanf("%d", &opcao);
					         
          if(opcao == 1){
						printf("Insira o numero da matricula do aluno: ");
						scanf("%d",&matricula);
						alunoRemovido = (Aluno*)colRemove(colecao, (void*)&matricula, comparaMatriculaDeAluno);
						break;
					}else if(opcao == 2){
						printf("Insira o nome do aluno: ");
						getchar();
						fgets(nome, 30, stdin);
						alunoRemovido = (Aluno*)colRemove(colecao, (void*)nome, comparaNomeDeAluno);
						break;
          }else{
            printf("Opção inválida.\n");
						continue;
          }
        }       
        
        if(alunoRemovido != NULL){
          printf("O aluno foi removido\n");
          printf("-------------------------\n");
          printf("Matricula: %d\n", alunoRemovido -> matricula);
          printf("Nome: %s", alunoRemovido -> nome);
          printf("Nota: %.2f\n", alunoRemovido -> nota);
        }else{
          printf("Não foi possível remover o aluno da colecao.\n");
        }
      }else{
        printf("É necessário criar uma colecao.\n");
      }
      break;

      case 4: //Consultar um aluno da colecao
      if(colExiste == TRUE && colecao != NULL){
        int matricula, opcao;
        char nome[30];
        
        while(TRUE){
          printf("\nConsultar por:\n[1] - Matrícula;\n[2] - Nome;\n");
          printf("Digite a opção: ");
          scanf("%d", &opcao);
					         
          if(opcao == 1){
						printf("Insira o numero da matricula do aluno: ");
						scanf("%d",&matricula);
						aluno = (Aluno*)colQuery(colecao, (void*)&matricula, comparaMatriculaDeAluno);
						break;
					}else if(opcao == 2){
						printf("Insira o nome do aluno: ");
						getchar();
						fgets(nome, 30, stdin);
						aluno = (Aluno*)colQuery(colecao, (void*)nome, comparaNomeDeAluno);
						break;
          }else{
            printf("Opção inválida.\n");
						continue;
          }
        }

       //(void*)&matricula - endereço da chave com nome matricula disfarcçada do tipo void* (fazendo o casting)
       //(void*)nome - variavel nome que é tipo char, mas disfarçada do tipo void* (fazendo o casting)
       //int(*comparacao)(void*, void*) - ponteiro para funcao comparacao que recebe dois void* e retorna uma variavel do tipo inteiro
       
        if(aluno != NULL){
          printf("\nAluno encontrado!\n");
          printf("-------------------------\n");
          printf("Matricula: %d\n", aluno -> matricula);
          printf("Nome: %s", aluno -> nome);
          printf("Nota: %.2f\n", aluno -> nota);
        }else{
          printf("Nenhum aluno encontrado!");
        }
      }else {
        printf("É necessário criar uma colecao.\n");        
      }
      break;
      
      case 5: //Listar elementos da colecao
      if(colExiste == TRUE && colecao != NULL){
        aluno = (Aluno*) colGetFirst(colecao);
        if(aluno != NULL){
          int indiceAluno = 1;
          while(aluno != NULL){
            printf("\n---- Aluno %d ----\n", indiceAluno);
            printf("Nome: %s", aluno -> nome);
            printf("Matricula: %d\n", aluno -> matricula);
            printf("Nota: %.2f\n", aluno -> nota);
            aluno = (Aluno*) colGetNext(colecao);
            indiceAluno++;
          }
        }else{
          printf("Lista vazia!\n");
        }
      }else{
        printf("É necessário criar uma colecao.\n");
      }
      break;

      case 6: //Destruir a colecao
      if(colExiste == TRUE && colecao != NULL){
        int colApagada;
        colApagada = colDestroy(colecao);
        if(colApagada == TRUE){
          printf("A colecao foi destruida.\n");
          colExiste = FALSE;
        }else{
          printf("Não foi possivel destruir a colecao,pois ela nao está vazia.\n");
        }
      }else{
        printf("É preciso criar primeiro uma colecao.\n");
      }
      break;

      case 7: //Esvaziar a colecao
      if(colExiste == TRUE && colecao != NULL){
        int vazia = colClean(colecao);
        if(vazia == TRUE){
          printf("Todos os itens foram apagados.\n");
        }else{
          printf("Colecao já está vazia.\n");
        }
      }else{
        printf("É preciso criar primeiro uma colecao.\n");        
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

  }while(opMenu !=0);
  return 0;
}