#include <stdio.h>

#define FICHIER "../../../donn�es/data_subjects_info.csv"
#define FICHIER_CIBLE "../../../donn�es/copie.csv"
#define FICHIER_NOUV "../../../donn�es/nouveau.csv"

typedef struct data Data;
struct data {
    double userAccX;
    double userAccY;
    double userAccZ;

};

void main(void) {

    FILE* trainSet;

    fopen_s(&trainSet, "../../..//donn�es/A_DeviceMotion_data/A_DeviceMotion_data/dws_2/sub_1.csv", "r");

    if (trainSet == NULL)
        printf("erreur cr�ation file trainset / testset");
    else {

        Data data;
        char line[1000];
        double trash;

        //lis dans le file
        fgets(&line, sizeof(line), trainSet);
        fgets(&line, sizeof(line), trainSet);
        sscanf_s(line, "%lf, %f, %f, %f, %lf, %f, %f, %f, %f, %lf, %lf, %lf, %lf", &trash, &trash, &trash, &trash, &trash, &trash, &trash, &trash, &trash, &trash, &data.userAccX, &data.userAccY, &data.userAccZ);
        printf("%s\n", line);
        printf("%lf\n", trash);
        printf("%lf\n, %lf, %lf", data.userAccX, data.userAccY, data.userAccZ);

        fclose(trainSet);
    } 

    //�criture dans un fichier
    /*fopen_s(&fichierCible, FICHIER_NOUV, "a");

    if (fichierCible == NULL) {
        printf("erreur cr�ation du fichier");
    }
    else {
        bool continu = true;
        char texte[100];
        char reponse;

        while (continu) {
            printf("entrez :");
            scanf_s("%s", texte, 100);
            fprintf(fichierCible, "%s,", texte);
            getchar();

            printf("continuer ? y/n");
            scanf_s("%c", &reponse, 1);
            continu = reponse == 'y';
        }
        fclose(fichierCible);
       */
}