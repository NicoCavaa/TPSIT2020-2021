#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct El{
    int valore;
    struct El* next;
}El;

void push(struct El *head, struct El *element){
    if (&head==NULL){
        head = element;
        element->next = NULL;
    }else{
        element->next = head;
        head = element;
    }
}

struct El* pop(struct El *head){
    struct El *ret = head;
    if(&head==NULL){
        return NULL ;
    }else{
        head = ret->next;
    }
    return ret;
}

void stampaPila(struct El* head){  
    struct El *ret;
    ret=pop(head);
    while(ret!=NULL){   
        printf("\n%d",ret->valore);
        free(ret);
        ret=pop(head); 
    }
}

int main(){

    struct El *head;
    struct El *element;
    char stringaDiNumeri[1000];

    printf("Numeri:\n");
    fflush(stdin);
    scanf("%s", stringaDiNumeri);

    for(int k = 0; stringaDiNumeri[k]!='\0'; k++){
        element = (struct El*) malloc(sizeof(struct El));
        element->valore = stringaDiNumeri[k] - 48;    
        push(&head,element);
    }

     stampaPila(&head);

    return 0;
 }