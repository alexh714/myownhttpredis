#include <stdlib.h>
#define BYTE unsigned char
#define INITSIZE 1000
#define HASHOFFSET 464
#define HASHPRIME 657193 //old value 6514497923

//#include <stdio.h>

BYTE* bytestorage[INITSIZE];

int currentCapacity = INITSIZE;

int hash(char *key, unsigned int keysize);
void store(char *key, unsigned int keysize, char *value, unsigned int size);
BYTE* retrieve(char *key, int keysize);
int copydata(char*,char*,int);
void deleteByKey(char *key,int keysize);

void initmemory(){
    int i;
    for(i = 0; i < INITSIZE; i++){
        bytestorage[i] = (BYTE*)malloc(sizeof(BYTE));
        bytestorage[i] = '\0';
    }
    return;
}
void store(char *key, unsigned int keysize, char *value, unsigned int size){
    //(BYTE*)malloc(INITSIZE * sizeof(BYTE));
    int loc = hash(key,keysize);
    //printf("the location stored in %d",loc);
    BYTE* data = (BYTE*)malloc( size * sizeof(BYTE));
    copydata(data,value,size);
    //printf("what is data? data == ");
    //printf("%s\n",data);
    bytestorage[loc] = data;
    return;
}
BYTE* retrieve(char *key,int keysize){
    int loc = hash(key,keysize);
    //printf("the location of the word should be in %d",loc);
    //printf("inside retrieve idk\n%s",bytestorage[loc]);
    return bytestorage[loc];
}
int hash(char *key, unsigned int keysize){
    unsigned int hash = HASHOFFSET;
    unsigned int keyhash = HASHOFFSET;
    int i = 0;
    for(i = 0; i < keysize; i++){
        hash = hash ^ key[i];
        hash = hash * HASHPRIME;
        keyhash += hash;
    }
    return hash % currentCapacity;
}
int copydata(char*dest,char*src,int size){
    int i = 0;
    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }
    return 0;
}
void deleteByKey(char *key,int keysize){
    int loc = hash(key,keysize);
    free(bytestorage[loc]);
    bytestorage[loc] = (BYTE*)malloc(sizeof(BYTE));
    bytestorage[loc] = '\0';
    return; 
}