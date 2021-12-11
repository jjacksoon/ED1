#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//Função para definir o MENU do programa
void menu(){
  	printf("-------MENU PRINCIPAL-------\n[1] - Ler a matriz A;\n[2] - Ler a matriz B;\n[3] - Multiplicar a matriz A pela matriz B;\n[4] - Calcular a Transposta da matriz A;\n[5] - Multiplicar a matriz A pela transposta da matriz B;\n[0] - Encerrar o programa\nDigite aqui sua opcao: ");
}

//Função para alocação, leitura e adicionamento de valores da Matriz
float *lerMatriz(int lMat, int cMat){
  	float *mat;
  	int i, j, k;
	//Alocando matriz em um vetor
	if(lMat > 0 && cMat > 0){
		mat = (float*)malloc(sizeof(float)*lMat*cMat);
		if(mat != NULL){
			for(i=0; i < lMat; i++){
				for(j=0; j< cMat; j++){
					printf("Digite o valor na posicao [%d][%d] na matriz: ", i, j);
					k = i*cMat + j;
					scanf("%f", &mat[k]);
				}
			}
		}
		
		return mat;
	}else{
		printf("Não é possivel criar a matriz. Uma ou mais dimensões são nulas!\n");
		return NULL;
	}  
}

//Função para imprimir a matriz desejada na tela
void imprimirMat(float *mat, int lMat, int cMat){
	int i, j, k;
	for(i=0;i<lMat; i++){
		for(j=0;j<cMat;j++){
			k = i*cMat + j;
			printf("%.2f  ",mat[k]);
		}
		printf("\n");
	}
}

// Função para multiplicação das duas matrizes A e B
float *multiplicaMatrizes(float *matA, float *matB, int lMatA, int cMatA, int lMatB, int cMatB){

	printf("Matriz A\n");
	imprimirMat(matA, lMatA, cMatA);
	printf("Matriz B\n");
	imprimirMat(matB, lMatB, cMatB);

	int i, j, k;
	float *matC;

	if(matA != NULL && matB != NULL){
		//Alocando a memória para a matriz resultante C
		matC = (float*)malloc(sizeof(float)*lMatA*cMatB);
		if(matC != NULL){
			for(i=0;i<lMatA;i++){
				for(j=0;j<cMatB;j++){
					matC[i*cMatB + j] = 0;
					for(k=0;k<cMatA;k++){
						matC[i*cMatB + j] += matA[i*cMatA + k] * matB[k*cMatB + j];
					}
				}
			}
		return matC;
		}else{
			printf("Impossivel alocar matriz resultante");
			return NULL;
		}
	}else{
		printf("Impossivel realizar operacao de multiplicacao. As matrizes A e B possuem valor NULL");
		return NULL;
	}
}

//Função para calcular a matriz transposta de uma matriz desejada
float *transpostaMat(float *matA, int lMatA, int cMatA){
	int i, j, k, t;
	float *trp;
	//Alocando matriz transposta
	trp = (float*)malloc(sizeof(float)*lMatA*cMatA);
	if(trp != NULL){
		for(i=0; i<lMatA; i++){
			for(j=0; j<cMatA; j++){
				k = i*cMatA + j;
				t = j*lMatA + i;
				trp[t] = matA[k];
			}
		}
		return trp;
	}
	else{
		printf("Impossivel realizar operacao de multiplicacao. A matriz transposta possui valor NULL");
		exit(0);
	}
}

int main() {
	int lMatA, cMatA, lMatB, cMatB, lTrpA, cTrpA, lTrpB, cTrpB, opMenu;
	float *matA, *matB, *matC, *trp;
	bool matACriada = false, matBCriada = false;
	
	do{
		menu();
		scanf("%d", &opMenu);
		switch(opMenu){
		case 1:
		//Lendo a Matriz A
		printf("Digite o numero de linhas da Matriz A: ");
		scanf("%d", &lMatA);
		printf("Digite o numero de colunas da Matriz A: ");
		scanf("%d", &cMatA);
		matA = lerMatriz(lMatA, cMatA);

		if(matA != NULL){
			matACriada = true;
			printf("A matriz A foi criada.\n");
			imprimirMat(matA, lMatA, cMatA);
		}else{
			matACriada = false;
		}
		
		break;
		
		case 2:
		printf("Digite o numero de linhas da Matriz B: ");
		scanf("%d", &lMatB);
		printf("Digite o numero de colunas da Matriz B: ");
		scanf("%d", &cMatB);
		matB = lerMatriz(lMatB, cMatB);

		if(matB != NULL){
			matBCriada = true;
			printf("A matriz B foi criada.\n");
			imprimirMat(matB,lMatB, cMatB);
		}else{
			matBCriada = false; 
		}
		
		break;

		case 3:
		//Multiplicando as duas matrizes
		if(matACriada == true && matBCriada == true){ 
			if(cMatA == lMatB){
				matC = multiplicaMatrizes(matA, matB, lMatA, cMatA, lMatB, cMatB);

				printf("MATRIZ MULTIPLICACAO AXB\n");
				imprimirMat(matC, lMatA, cMatB);
				free(matC);
			}else{
				printf("Não é possivel realizar a multiplicacao, pois o numero de colunas da Matriz A é diferente do numero de linhas da matriz B (condicao de existencia do produto)\n");
			}
		} else if(matACriada == false && matBCriada == true){
			printf("E preciso primeiro criar a matriz A para realizar a operacao!\n");
		} else if(matBCriada == false && matACriada == true){
			printf("E preciso primeiro criar a matriz B para realizar a operacao!\n");
		}else{
			printf("É preciso primeiro criar as matrizes que serao multiplicadas!\n");
		}
		break;

		case 4:
		//Transposta da matriz A
		if(matACriada == true){
			trp = transpostaMat(matA, lMatA, cMatA);
			lTrpA = cMatA;
			cTrpA = lMatA;
			printf("MATRIZ TRANSPOSTA DE A\n");
			imprimirMat(trp,lTrpA,cTrpA);
			free(trp);

		}else{
			printf("E preciso primeiro criar a matriz A para realizar a operacao!\n");
		}
		break;

		case 5:
		//Multiplicação da matriz A pela transposta de B
		if(matACriada == true && matBCriada == true){
			trp = transpostaMat(matB, lMatB, cMatB);
			lTrpB = cMatB;
			cTrpB = lMatB;
			printf("MATRIZ TRANSPOSTA DE B\n");
			imprimirMat(trp,lTrpB,cTrpB);
			if(cMatA == lTrpB){
				matC = multiplicaMatrizes(matA, trp, lMatA, cMatA, lTrpB, cTrpB);
				printf("MATRIZ MULTIPLICACAO DE A POR TRANSPOSTA DE B\n");
				imprimirMat(matC, lMatA, lMatB);
				free(matC);
				free(trp);
			}else{
				printf("Não é possivel realizar a multiplicacao, pois o numero de colunas da Matriz A é diferente do numero de linhas da matriz Transposta de B (condicao de existencia do produto)\n");
			}
		}else if(matACriada == false && matBCriada == true){
			printf("E preciso primeiro criar a matriz A para realizar a operacao!\n");
		}else if(matBCriada == false && matACriada == true){
			printf("E preciso primeiro criar a matriz B para realizar a operacao!\n");
		}else{
			printf("É preciso primeiro criar as matrizes que serao usadas na operação!\n");
		}
		break;

		case 0:
		printf("Encerrando o programa...\n");
		sleep(3);
		printf("------Programa encerrado. Obrigado.------");
		break;

		default:
		printf("Opcao invalida. Tente novamente!\n");
		}
	}while(opMenu != 0);
	
	return 0;
}