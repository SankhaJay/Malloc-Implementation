#include<stdio.h>
#include "t1.h"
//#include "malloc.h"
//char memory[20000];
int main(){
 
    int *p = (int*)MyMalloc(100*sizeof(int));
    char *q = (char*)MyMalloc(250*sizeof(char));
    int *r = (int*)MyMalloc(1000*sizeof(int));
    MyFree(p);
    char *w = (char*)MyMalloc(700);
    MyFree(r);
    int *k = (int*)MyMalloc(500*sizeof(int));
    printf("Allocation and deallocation is done successfully!");
 
}
