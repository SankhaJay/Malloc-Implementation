#include<stdio.h>
#include<stddef.h>
#include "t1.h"

void init(){
    freelist -> size = 25000 - sizeof(struct info);//decresing memeory for the first meta data block
    freelist -> free = 1;
    freelist -> next = NULL;//end of the array
}

void split(struct info* slot,size_t blocksize){
    struct info* new =  ;//"new" is the extra memory block
    new->size = slot->size - size - sizeof(struct block);//seperting the extra memory block as "new"
    new->free = 1;
    new->next = slot->next;//slot->next is still unchanged at this line of code
    slot->next = new;
    slot->free = 0;

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
        current->free = 0;//don't have to update meta data here because the data that there is already is enough and correct
        current = current + 1;
        result = (void*)current;
        printf("Block allocation succesful");
        return result;
    } 
    else if(current->size > blocksize){
        split(current,blocksize);
    }
}
