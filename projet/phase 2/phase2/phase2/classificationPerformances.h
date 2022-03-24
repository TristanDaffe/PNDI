#include <stdio.h>
#include <stdlib.h>

typedef struct classes Classes;
struct classes {
	int number;
	int totCorrect;
	int total;
	Classes* pSuiv;
};

//prototype
void displayResultsByClass(int realClasses[], int estimatedClasses[], int nbTests);
void displayRow(Classes* pStart);
Classes* calculResult(int realClasses[], int estimatedClasses[], int nbTests);
//int maxMouvement(int realClasses[], int estimatedClasses[], int nbTests);


void displayResultsByClass(int realClasses[], int estimatedClasses[], int nbTests) {
	Classes* pStart = calculResult(realClasses, estimatedClasses, nbTests, &pStart);
	displayRow(pStart);

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
		// si le chainon n'existe pas encore, on le crée
		if (pClass == NULL) {
			Classes* pNouv = (Classes*)malloc(sizeof(Classes));
			if (pNouv == NULL) {
				printf("place mémoire insuffisante");
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

//int maxMouvement(int realClasses[], int estimatedClasses[], int nbTests) {
//	int maxClasses = 0;
//	for (int i = 0; i < nbTests; i++) {
//		if (realClasses[i] > maxClasses || estimatedClasses[i] > maxClasses)
//			maxClasses = (realClasses[i] > estimatedClasses[i] ? realClasses[i] : estimatedClasses[i]);
//	}
//	return maxClasses;
//}