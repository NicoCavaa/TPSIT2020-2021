#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define DIM 100


void contagi(int n, float r, int *giorni, float nCasi[]){
    int k=1;
    nCasi[0]=1;
    while(nCasi[k-1]<=(float)n){
        nCasi[k]=r*nCasi[k-1];
        *giorni=*giorni+1;
        k++;
    }
}


int main () {
    int giorni=1;
    int n;
    float r;
    float nCasi[DIM];

    printf("Inserisci numeo persone contagiate da ciascuno: ");
    scanf("%f",&r);
    printf("Inserisci il numero di studenti: ");
    scanf("%d",&n);

    contagi(n,r,&giorni,nCasi);

    printf("Numero giorni: %d",giorni);