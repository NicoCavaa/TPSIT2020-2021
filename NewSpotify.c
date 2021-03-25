#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define DIM 25
#define SIZE 100

typedef struct canzone{
    int num;
    char nome_canzone[DIM];
    char artista[DIM];
    struct canzone *next;
}Canzone;

void push(Canzone* c, int cnt, char* nomeCanzone, char* nomeArtista){
    Canzone* canz;
    canz = c;  
    if(cnt == 1){
        canz->num = cnt;                   
        strcpy(canz->nome_canzone,nomeCanzone);
        strcpy(canz->artista,nomeArtista);
    }else{
        while (canz->next != NULL){
            canz = canz->next;
        }
        canz->next = (Canzone*) malloc (sizeof(Canzone));
        canz->next->num = cnt;
        strcpy(canz->next->nome_canzone,nomeCanzone);
        strcpy(canz->next->artista,nomeArtista);
        canz->next->next = NULL;        
    }
}

bool prova(int* vet,int cerca,int dim){
    bool ok=false;
    for(int k=0;k<dim;k++){
        if(cerca==*(vet+k)){
            ok=true;
            k=dim;
        }
    }
    return ok;
}

void canzoniRand(Canzone* c, int dim){
    Canzone* canz;
    int k=0;
    int* vet = malloc(dim  * sizeof(int));
    srand(time(NULL));
    for (int j = 0; j < dim; j++){
        canz = c;
        k = 0;
        while(k < *(vet+j)){
            if(k==*(vet+j)){              
                printf("%2d, %s, %s\n",canz->num,canz->nome_canzone,canz->artista);
            }
            canz = canz->next;
            k++;
        }
    }
}

void main(){

    Canzone *playlist;
    playlist = (Canzone*) malloc (sizeof(Canzone));

    FILE *fp;

    char* buffer;
    buffer = malloc(SIZE * sizeof(char));       
    int k=0;

    int cnt=0;
    char* artista = malloc(SIZE * sizeof(char));   
    char* nome_canzone = malloc(SIZE * sizeof(char));  

    fp=fopen("canzoni.csv","r");

    if(fp==NULL){
        printf("File non esistente");
    }else{
        while(fgets(buffer,SIZE,fp)){
            strcpy(nome_canzone,strtok(NULL,","));   
            strcpy(artista,strtok(NULL,"\n"));
            push(playlist,cnt,nome_canzone,artista);    
            k++;
        }
    }
    canzoniRand(playlist,k);  
