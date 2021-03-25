#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define DIM 25
#define SIZE 1000

typedef struct regione{
    char data[DIM];
    char stato[DIM];
    int codReg;
    char nomReg[DIM];
    float lat;
    float longi;
    int ricoverati_con_sintomi;
    int terapia_intensiva;
    int totale_ospedalizzati;
    int isolamento_domiciliare;
    int totale_positivi;
    int variazione_totale_positivi;
    int nuovi_positivi;
    int dimessi_guariti;
    int deceduti;
    int casi_da_sospetto_diagnostico;
    int casi_da_screening;
    int totale_casi;
    int tamponi;
    int casi_testati;
}Regione;

void topTerapiaIntensiva(Regione *reg, int dim){
    int k, cnt;
    Regione temp;
    for (cnt= dim-1; cnt > 0; cnt--){
        for (k = 0; k< cnt; k++){
            if ((reg+k)->terapia_intensiva < (reg+k+1)->terapia_intensiva){
                temp=*(reg+k);
                *(reg+k)=*(reg+k+1);
                *(reg+k+1)=temp;
            }    
        }
    }
    printf("topTerapiaIntensiva: ");
    for(int j=0; j<3; j++){
        printf("\n%s:%d", (reg+j)->nomReg, (reg+j)->terapia_intensiva);
    }
}

void topMenoCasi(Regione *reg, int dim){
    int k, cnt;
    Regione temp;
    for (cnt= dim-1; cnt > 0; cnt--){
        for (k = 0; k< cnt; k++){
            if ((reg+k)->totale_casi > (reg+k+1)->totale_casi){
                temp=*(reg+k);
                *(reg+k)=*(reg+k+1);
                *(reg+k+1)=temp;
            }    
        }
    }
    printf("\n\ntopMenoCasi: ");
    for(int j=0; j<3; j++){
        printf("\n%s:%d", (reg+j)->nomReg, (reg+j)->totale_casi);
    }
}

void totTerapiaIntensiva(Regione *reg, int dim){
    int sTerapiaIntensiva=0;
    for(int j=0; j<dim; j++){
        sTerapiaIntensiva+=(reg+j)->terapia_intensiva;
    }
    printf("\n\nSomma terapia intesiva e'=%d", sTerapiaIntensiva);
}

int main(){
    FILE *fp;
    Regione *reg;
    char *buffer;
    buffer = malloc(SIZE * sizeof(char));
    int k=0;
    if((fp=fopen("data.csv","r"))==NULL){
        printf("File non esistente");
    }else{
        while(fgets(buffer,SIZE,fp)){ //leggo una volta tutto il file
            k++;
        }
        fclose(fp);
        fp=fopen("data.csv","r");
        reg = malloc(k * sizeof(Regione)); //allocazione dinamica della memoria
        k=0;
        while(fgets(buffer,SIZE,fp)){
            strcpy((reg+k)->data, strtok(buffer,","));
            strcpy((reg+k)->stato,strtok(NULL,","));
            (reg+k)->codReg = atoi(strtok(NULL,","));
            strcpy((reg+k)->nomReg, strtok(NULL,","));
            (reg+k)->lat = atof(strtok(NULL,","));
            (reg+k)->longi = atof(strtok(NULL,","));
            (reg+k)->ricoverati_con_sintomi = atoi(strtok(NULL,","));
            (reg+k)->terapia_intensiva = atoi(strtok(NULL,","));
            (reg+k)->totale_ospedalizzati = atoi(strtok(NULL,","));
            (reg+k)->isolamento_domiciliare = atoi(strtok(NULL,","));
            (reg+k)->totale_positivi = atoi(strtok(NULL,","));
            (reg+k)->variazione_totale_positivi = atoi(strtok(NULL,","));
            (reg+k)->nuovi_positivi = atoi(strtok(NULL,","));
            (reg+k)->dimessi_guariti = atoi(strtok(NULL,","));
            (reg+k)->deceduti = atoi(strtok(NULL,","));
            (reg+k)->casi_da_sospetto_diagnostico = atoi(strtok(NULL,","));
            (reg+k)->casi_da_screening = atoi(strtok(NULL,","));
            (reg+k)->totale_casi = atoi(strtok(NULL,","));
            (reg+k)->tamponi = atoi(strtok(NULL,","));
            (reg+k)->casi_testati = atoi(strtok(NULL,"\n"));
            k++;
        }
        topTerapiaIntensiva(reg, k);
        totTerapiaIntensiva(reg, k);
        topMenoCasi(reg, k);
    }
}