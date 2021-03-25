#include <stdio.h>
#include <stdlib.h>


struct node{
    int val;
    struct node* next;
};


int isempty(struct node* head){
    return (head == NULL) ? 1 : 0;
}


void enqueue(struct node** head, struct node** tail, 
             struct node* element){
    
    if(isempty(*head))
        *head = element;
    else
        (*tail)->next = element;
    
    *tail = element;
    element->next = NULL;

    return;
}


struct node* dequeue(struct node** head,
                     struct node** tail){
    
    struct node* ret = *head;

    if(isempty(*head))
        return NULL;
    else
        *head = ret->next;
    
    if(*head == NULL)
        *tail = NULL;

    return ret;
}


void printQueue(struct node** head,
                struct node** tail){
    struct node* support;
}


int main(){
    
    struct node* head;
    struct node* tail;
    struct node* input_node;
    int end;
    
    do{
        input_node = (struct node*) malloc(sizeof(struct node));

        printf("Numero: ");
        scanf("%d", &input_node->val);
        
        enqueue(&head, &tail, input_node);

        printf("Ancora: ");
        fflush(stdin);
        scanf("%d", &end);

    }while(end != 0);

    printQueue(&head, &tail);

    return 0;
}