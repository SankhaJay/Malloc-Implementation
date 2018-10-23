#include<stdio.h>
#include<stddef.h>
#include "t1.h"

struct info *freelist = (void*)memory;

void init(){
    freelist->size = 25000 - sizeof(struct info);//decresing memeory for the first meta data block
    freelist->free = 1;
    freelist->next = NULL;//end of the array
}

void merge(){
    struct info* current;
    current = freelist; //initializing current to the start of the memory
    while(current->next){ //loopig through memory fromm the beginning
        if(current->free && (current->next->free)){ //checking whether adjacent blocks are free
            current->next = current->next->next; //combining two blocks
            current->size = current->size+current->next->size + sizeof(struct info); //increasing the size of the new block(current)
        }
    current = current->next;
    }
}

void split(struct info* slot,size_t blocksize){
    struct info* new =(void*)((void*)slot+blocksize+sizeof(struct info));
    new->size = slot->size - blocksize - sizeof(struct info);//seperating the extra memory block as "new"
    new->free = 1;
    new->next = slot->next;//slot->next is still unchanged at this line of code
    slot->next = new;
    slot->free = 0;
    merge();//Merge the new block if possible

}

void* MyMalloc(size_t blocksize){
    struct info* current;
    struct info* previous;
    void* result;//this will be the return value of malloc function
    
    if(!(freelist->size)){
        init();
    }
    current = freelist;
    /*checking for the first fit free block in the array(memory)*/
    while((current->free==0||current->size<blocksize) && (current->next)){
        previous = current;
        current = current->next;
    }
    /*if there is a suitable block which has the same size as required*/
    if(current->size == blocksize){
        current->free = 0;//don't have to update meta data here because the data that there is already is enough and correct
        current = current + 1;
        result = (void*)current;
        printf("Block allocation succesful");
        return result;
    } 
    /*if there is a suitabale block but the size is larger than required.Allocated memory block using split*/
    else if(current->size > blocksize){
        split(current,blocksize);
        current = current + 1;
        result = (void*)current;
        printf("Block allocation succesful");
        return result;
    }
    /*if code gets here that means there isn't a suitable block*/
    else{
        result = NULL;
        printf("Block allocation unsuccesful !!");
        return result;
    }
}

void MyFree(void* ptr){
    if((ptr>=(void*)memory && ptr<=(void*)(memory+25000))){//ptr has to be between 'memory' and 'memory' + 25000
        struct info* new = ptr;
        new = new - 1; //to access meta data block 
        new->free = 1;
        merge();  
    }
    else
        printf("Provided pointer is not valid");
}
