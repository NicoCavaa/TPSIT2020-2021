#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(){
    int *pi;
    *pi = 15;
    printf("%p \n", pi);
    pi = pi + 1;
    printf("%p", pi);

}