#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FI_MODEL_PATH "../fimodel.csv"
#define TRAIN_SET_PATH "../../phase1/trainSet.csv"

#define TIME_FOR_A_MIN 600

typedef struct dataDixiemeSeconde DataDixiemeSeconde;
struct dataDixiemeSeconde{
    double totVacc;
    double totSquareVacc;
    int nbLine;
};

void initFiModel(FILE* fiModel);

void main(void){
    FILE* fiModel;
    FILE* trainSet;

    fopen_s(&trainSet, TRAIN_SET_PATH, "r");
    fopen_s(&fiModel, FI_MODEL_PATH, "w+");
    initFiModel(fiModel);

    if(trainSet == NULL || fiModel == NULL){
        printf("erreur ouverture des fichier\n");
    }
    else{
    //utilisé pour la moyenne global
        //nombre de ligne pour le mouvement
        double totMovement = 0;
        //somme des vacc pour ce mouvement
        int totNbVacc = 0;

        char movementType[20];
        char currentMovement[20];
        double vacc;
        char line[10000];
        char* token;
        char* nextToken;

        //contient les Vacc d'un mouvement pour chaque dixieme de seconde
        DataDixiemeSeconde data[TIME_FOR_A_MIN];
        for(int i = 0; i < TIME_FOR_A_MIN; i++){
            data[i].totVacc = 0;
            data[i].totSquareVacc = 0;
            data[i].nbLine = 0;
        }


        //supprime la ligne des titres
        fgets(line, sizeof(line), trainSet);
        //récupere la première ligne de données
        fgets(line, sizeof(line), trainSet);

        while(!feof(trainSet)){
        //lis le titre du mouvement en cours
            token = strtok_s(line, ";", &nextToken);
            strcpy(currentMovement, token);
    printf("%s\n", currentMovement);
    printf("[");
            do{
    printf("|");
                //passe la colonne d'index et du genre
                token = strtok_s(NULL, ";", &nextToken);
                token = strtok_s(NULL, ";", &nextToken);

                int iColumn = 0;
                //récupere les Vacc de la ligne
                token = strtok_s(NULL, ";", &nextToken);
                while(iColumn < TIME_FOR_A_MIN && token != NULL){
                    sscanf_s(token, "%lf", &vacc);
                    data[iColumn].totVacc += vacc;
                    data[iColumn].totSquareVacc += vacc * vacc;
                    data[iColumn].nbLine++;

                    totNbVacc += vacc;
                    totMovement++;
                    
                    iColumn++;
                    token = strtok_s(NULL, ";", &nextToken);
                }
            //passe a la ligne suivante
                fgets(line, sizeof(line), trainSet);
                token = strtok_s(line, ";", &nextToken);
                strcpy(movementType, token);
            }while(strcmp(movementType, currentMovement) == 0 && !feof(trainSet));
    printf("]\n");
        //ecriture des vacc dans fiModel
            fprintf(fiModel, "%c", '\n');
            //ecriture des moyennes
            fprintf(fiModel, "%s;", currentMovement);
            for(int i = 0; i < TIME_FOR_A_MIN; i++)
                fprintf(fiModel, "%lf;", data[i].totVacc / data[i].nbLine);
            fprintf(fiModel, "%c", '\n');    
            //ecriture des ecart types
            fprintf(fiModel, "%s;", currentMovement);
            for(int i = 0; i < TIME_FOR_A_MIN; i++){
                double standartDeviation = data[i].totSquareVacc / data[i].nbLine - data[i].totVacc / data[i].nbLine;
                fprintf(fiModel, "%lf;", standartDeviation);
            }
            fprintf(fiModel, "%c", '\n');
            //écriture de la moyenne générale
            fprintf(fiModel, "%s;", currentMovement);
            fprintf(fiModel, "%lf;", totNbVacc / totMovement);
            fprintf(fiModel, "%c", '\n');

            fgets(line, sizeof(line), trainSet);
        }

        fclose(trainSet);
        fclose(fiModel);
    }
}

void initFiModel(FILE* fiModel){
    fprintf(fiModel, "%s;", "mouvement");
    for(int i = 0; i < TIME_FOR_A_MIN; i++)
        fprintf(fiModel, "%s;", "Vacc");
    fprintf(fiModel, "%s", "\n");
}