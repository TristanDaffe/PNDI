#include <stdio.h>
#include <stdlib.h>

#define NB_MAX_CLASSES 20

/*=====structure=======*/

typedef struct classes Classes;
struct classes {
	int number;
	int totCorrect;
	int total;
	Classes* pSuiv;
};

/*=====prototype=======*/

//displayResultsByClass
void displayResultsByClass(int realClasses[], int estimatedClasses[], int nbTests);
void displayRow(Classes* pStart);
Classes* calculResult(int realClasses[], int estimatedClasses[], int nbTests);

//displayAccuracy
void displayAccuracy(int realClasses[], int estimatedClasses[], int nbTests);
int countTot(int realClasses[], int estimatedClasses[], int nbTests);

//displayConfusionMatrice
void displayConfusionMatrix(int realClasses[], int estimatedClasses[], int nbTests);
int maxMouvement(int realClasses[], int estimatedClasses[], int nbTests);
void createMatrix( int realClasses[], int estimatedClasses[], int nbTests, int nbClasses, int matrix[NB_MAX_CLASSES][NB_MAX_CLASSES]);
void displayMatrix(int matrix[NB_MAX_CLASSES][NB_MAX_CLASSES], int nbClasses);
void displaySplitLine(int nbClasses);

/*=====definition=======*/

void displayResultsByClass(int realClasses[], int estimatedClasses[], int nbTests) {
	Classes* pStart = calculResult(realClasses, estimatedClasses, nbTests);
	displayRow(pStart);
	Classes* pClasses = pStart;
	while (pClasses != NULL) {
		Classes* pPrec = pClasses;
		pClasses = pClasses->pSuiv;
		free(pPrec);
	}
}
Classes* calculResult(int realClasses[], int estimatedClasses[], int nbTests) {
	Classes* pStart = NULL;
	for (int i = 0; i < nbTests; i++) {
		Classes* pClass = pStart;
		Classes* pPrec = NULL;

		//cherche le chainon du bon type de mouvement
		while(pClass != NULL && pClass->number != realClasses[i]) {
			pPrec = pClass;
			pClass = pClass->pSuiv;
		}
		// si le chainon n'existe pas encore, on le cr�e
		if (pClass == NULL) {
			Classes* pNouv = (Classes*)malloc(sizeof(Classes));
			if (pNouv == NULL) {
				printf("place memoire insuffisante");
			}
			else {
				pNouv->number = realClasses[i];
				pNouv->total = 0;
				pNouv->totCorrect = 0;
				pNouv->pSuiv = NULL;
				if (pPrec != NULL)
					pPrec->pSuiv = pNouv;
				else {
					if (pStart == NULL)
						pStart = pNouv;
				}
				pClass = pNouv;
			}
		}
		//ajoute le test au chainon
		pClass->total++;
		if (realClasses[i] == estimatedClasses[i])
			pClass->totCorrect++;
	}
	return pStart;
}
void displayRow(Classes* pStart) {
	printf("\tclasse \t|\tbien classes\t|\ttotal\t|\tpourcentage \n");
	Classes* pClass = pStart;
	while (pClass != NULL) {
		printf("\t %d\t|\t\t%d \t| \t %d \t| \t %.2lf%% \n", pClass->number, pClass->totCorrect, pClass->total, (double)pClass->totCorrect / pClass->total * 100);
		pClass = pClass->pSuiv;
	}
}

void displayAccuracy(int realClasses[], int estimatedClasses[], int nbTests) {
	int tot = countTot(realClasses, estimatedClasses, nbTests);
	double accuracy = (double)tot / nbTests * 100;
	printf("L'accuracy est de %.2lf%%\n", accuracy);
}
int countTot(int realClasses[], int estimatedClasses[], int nbTests) {
	int totCorrect = 0;
	for (int i = 0; i < nbTests; i++) {
		if (realClasses[i] == estimatedClasses[i])
			totCorrect++;
	}
	return totCorrect;
}

void displayConfusionMatrix(int realClasses[], int estimatedClasses[], int nbTests){
	int maxClasses = maxMouvement(realClasses, estimatedClasses, nbTests);
	int matrix[NB_MAX_CLASSES][NB_MAX_CLASSES];
	createMatrix(realClasses, estimatedClasses, nbTests, maxClasses, matrix);
	displayMatrix(matrix, maxClasses);
}
int maxMouvement(int realClasses[], int estimatedClasses[], int nbTests) {
	int maxClasses = 0;
	for (int i = 0; i < nbTests; i++) {
		if (realClasses[i] > maxClasses || estimatedClasses[i] > maxClasses)
			maxClasses = (realClasses[i] > estimatedClasses[i] ? realClasses[i] : estimatedClasses[i]);
	}
	return maxClasses;
}
void createMatrix( int realClasses[], int estimatedClasses[], int nbTests, int nbClasses, int matrix[NB_MAX_CLASSES][NB_MAX_CLASSES]) {
	for(int i = 0; i < nbClasses; i++){
		for(int j = 0; j < nbClasses; j++)
			matrix[i][j] = 0;
	}
	for(int i = 0; i < nbTests; i++){
		matrix[realClasses[i]-1][estimatedClasses[i]-1] ++;
	}
}
void displayMatrix(int matrix[NB_MAX_CLASSES][NB_MAX_CLASSES], int nbClasses) {
	//affiche la ligne de titre
	printf("\t\t|");
	for(int iColumn = 0; iColumn < nbClasses; iColumn++)
		printf("\t%d\t|", iColumn+1);
	printf("\n");
	displaySplitLine(nbClasses);
	//affiche la matrice
	for(int iLine = 0; iLine < nbClasses; iLine++){
		printf("\t%d\t|", iLine+1);
		for(int iColumn = 0; iColumn < nbClasses; iColumn++)
			printf("\t%d\t|", matrix[iLine][iColumn]);
		printf("\n");
		displaySplitLine(nbClasses);
	}
}
void displaySplitLine(int nbClasses) {
	for (int i = 0; i < nbClasses * 20; i++)
		printf("-");
	printf("\n");
}