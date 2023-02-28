#include <stdlib.h>
#include <stdio.h>
#define BYTE unsigned char
#define INITSIZE 1000
//BYTE **bytestorage;
extern int hash(char *key, unsigned int keysize);
//void initmemory();
extern void store(char *key, unsigned int keysize, char *value, unsigned int size);
extern BYTE* retrieve(char *key, int);
void add2Storage();
void take4Storage();
void printMenu();
int main(){
	//initmemory();
    char word1[3] = "Hel";
    char word2[3] = "Cau";
    unsigned int res1 = hash(word1,3);
    unsigned int res2 = hash(word2,3);
    printf("the value for word 1 is: %d\n\n",res1);
    printf("the value for word 2 is: %d\n",res2);

    
    int i = 0;
    int running = 1;
    int storing = 1;
    char inputchoice = '\0';
    while(running){
        printMenu();
        inputchoice = fgetc(stdin);
        if(inputchoice == '1' || inputchoice == 'a' || inputchoice == 'A'){
            add2Storage();
        }
        if(inputchoice == '2' || inputchoice == 'g' || inputchoice == 'G'){
            take4Storage();
        }
        if(inputchoice == '0' || inputchoice == 'q' || inputchoice == 'Q'){
            running = 0;
        }

    }
    //char* storedvalue = retrieve(keyinput,keysize);
    //printf("take back your value:\n");
    //printf("%s",storedvalue);
	return 0;
}
void add2Storage(){
    fgetc(stdin);
    fflush(stdin);
    char keyinput[255];
    int keysize = 0;
    char valueinput[65535];
    int valuesize = 0;
    int i;
    printf("enter your key\n");
    fgets(keyinput, sizeof(keyinput), stdin);
    for(i = 0; i < 255; i++){
        if(keyinput[i]=='\n'){
            keysize = i;
            break;
        }
    }
    fgetc(stdin);
    fflush(stdin);
    printf("enter the value you want to store\n");
    fgets(valueinput, sizeof(valueinput), stdin);
    for(i = 0; i < 65535; i++){
        if(valueinput[i]=='\n'){
            valuesize = i;
            break;
        }
    }
    //printf("the size of key: %d\n\n",keysize);
    //printf("the value of value: %d\n\n",valuesize);
    //printf("what is in the keyvalue?\n%s_Hi",keyinput);
    for(i = 0; i < 255 && 0; i++){
        fputc(keyinput[i],stdout);
        fputc('\n',stdout);
        if(keyinput[i]=='\n'){
            printf("new line found");
        }
    }
    store(keyinput, keysize, valueinput, valuesize);
}
void take4Storage(){
    fgetc(stdin);
    char keyinput[255];
    int keysize = 0;
    int i;
    printf("enter your key\n");
    fgets(keyinput, sizeof(keyinput), stdin);
    for(i = 0; i < 255; i++){
        if(keyinput[i]=='\n'){
            keysize = i;
            break;
        }
    }
    char* storedvalue = retrieve(keyinput,keysize);
    printf("take back your value:\n");
    printf("%s\n",storedvalue);
}
void printMenu(){
    printf("Type 1 or a or A to add new key\n");
    printf("Type 2 or g or G to retrieve\n");
    printf("Type 0 or q or Q to quit\n");
}