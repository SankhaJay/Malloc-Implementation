#include<stdio.h>
#include<stddef.h>
#include "t1.h"

void init(){
    freelist -> size = 25000 - sizeof(struct info);//decresing memeory for the first meta data block
    freelist -> free = 1;
    freelist -> next = NULL;//end of the array
}

void split(struct info* slot,size_t blocksize){
}

void *MyMalloc(size_t blocksize){
    struct info *current,*previous;
    void *result;//this will be the return value of malloc function
    
    if(!(freelist->size)){
        init();
    }
    current = freelist;
    /*checking for the first fit free block in the array(memory)*/
    while((current->free==0||current->size<blocksize) && (current->next)){
        previous = current;
        current = current->next;
    }
    /*if there is a suitable block*/
    if(current->size == blocksize){
        current->free = 0;
        result = 
    } 
    
}
