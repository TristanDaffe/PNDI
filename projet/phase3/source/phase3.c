#include <stdio.h>
#include <stdlib.h>

#define FI_MODEL_PATH "../fimodel.csv"
#define TRAIN_SET_PATH "../../phase1/trainSet.csv"

typedef struct dataDixiemeSeconde DataDixiemeSeconde;
struct dataDixiemeSeconde{
    double totVac;
    double totCarreVacc;
    int nbLigne;
};

void main(void){
    FILE* fiModel;
    FILE* trainSet;

    fopen_s(&trainSet, TRAIN_SET_PATH, "r");
    fopen_s(&fiModel, FI_MODEL_PATH, "w+");

    if(trainSet == NULL || fiModel == NULL){
        printf("erreur ouverture des fichier\n");
    }
    else{
        printf("000");
    }
}