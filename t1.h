git #include<stdio.h>
#include<stddef.h>

char memory[25000];

struct info{
    size_t size;
    int free;//free = 1 if memory block is free to use
    struct info* next;//pointer to find the next block
};

struct info *freelist = (void*)memory;

void init();
void *MyMalloc(size_t blocksize);
void MyFree(void* ptr);
void split(struct info* slot,size_t blocksize);
void merge(vooid *ptr);