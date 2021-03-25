#include <stdio.h>

#define MAX 3

int testa;
int Pila[MAX];

int menu_scelta(void)
{
  int selezione = 0;
  do
    {
    printf("\n" );
    printf("\n1 -> Aggiungi un dato" );
    printf("\n2 -> Estrai un dato");
    printf("\n3 -> Svuota pila");
    printf("\n4 -> Stampa pila");
    printf("\n5 -> Esci");
    printf("\n" );
    printf("\nEffettua una scelta: " );
    scanf("%d", &selezione );
    }
    while (selezione<1 || selezione>5);
  return selezione;
}

void Push() {
	int n;
	
	if(testa==MAX) 
	         printf("\n -> Pila piena" );
	else {
		 printf("\nInserisci un dato: " );
		 scanf("%d", &n);
		 Pila[testa++]=n;
	}		
}

void Pop() {
	if(testa==0) 
	     printf("\n - Pila vuota" );
	else 
	    printf("%d", Pila[--testa]);	
}

void Clear() {
	testa=0;
	printf("\n -> Pila svuotata" );			
}

void Print() {
	int i;
	if(testa==0) 
	       printf("\n -> Pila vuota" );
	else 
              for(i=testa-1;i>=0;i--)	
                  printf("indice i: %d elemento %d\n", i, Pila[i]);			

}

int main(){
	int scelta;
	
	while((scelta=menu_scelta())!=5){
             switch(scelta){
                   case 1: 
			Push();
                        break;
                   case 2:
			Pop();
               	        break;
                   case 3:
			Clear();
            	        break;
                   case 4: 
			Print();
			break;
	        case 5: 
		        break;
             }
    }             
    return 0;
}