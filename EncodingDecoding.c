#include <stdlib.h>
#include <stdio.h>

#define DIM 100

int main(){
    char stringa[DIM];
    int n;
    int k;
    int cnt=1;
    printf("inserisci: \n0 Encoding \n1 Decoding \n");
    scanf("%d", &n);
    if(n==1){
        printf("DECODING");
        printf("\ninserire la stringa: "); 
        fflush(stdin);
        scanf("%s", &stringa[DIM]);
        int j=0;
        do{
            j=stringa[k]-48;
            printf("%s"stringa[k]);
            if(j<=9 && j-48>=0){
                for(int x=0; x<j; x++){
                    printf("%c", stringa[k]);
                }
            }
            k++;
        }while(stringa[k] != '\0');

    }else{
        if(n==0){
            int cnt=1;
            char stringa[DIM];
            printf("ECODING");
            printf("\ninserisci un stringa: ");
            scanf("%s", stringa);
            for(int k=0;k<strlen(stringa);k++){
                if(stringa[k]==stringa[k+1]){
                    cnt++;
                }else{
                    if(cnt!=1){
                        printf("%d%c",cnt,stringa[k]);
                        cnt=1;
                    }else{
                        printf("%c",stringa[k]);
                        cnt=1;
                    }
                }
            }
        }
    }
}

    /*int cnt=1;
    char stringa[DIM];
    printf("inserisci un stringa: ");
    scanf("%s", stringa);
    for(int k=0;k<strlen(stringa);k++){
        if(stringa[k]==stringa[k+1]){
            cnt++;
        }else{
            if(cnt!=1){
                printf("%d%c",cnt,stringa[k]);
                cnt=1;
            }else{
                printf("%c",stringa[k]);
                cnt=1;
            }
        }
    }*/