#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char line[100]; 
    struct list *next;
    struct list *previous;
}LIST;


LIST *addtolist(LIST *listStart,char line[100]){
	LIST *newNode,*ptrList;
    if((newNode = (LIST*) malloc(sizeof(LIST))) == NULL){
		fprintf(stderr,"malloc failed");
		exit(1);
	}
	strcpy(newNode->line,line);
	newNode->next = NULL;

	if(listStart == NULL){
		listStart = newNode;
		listStart->previous = NULL;
	}
	else{
		ptrList = listStart;
		while(ptrList->next != NULL){
			ptrList = ptrList->next;
		}
		newNode->previous = ptrList;
		ptrList->next = newNode;
	}
    return listStart;
}

void printFromFile(LIST *listStart){
	LIST *ptrList;
	ptrList = listStart;
	while(ptrList->next != NULL){
		ptrList = ptrList->next;
	}
	while(ptrList->previous != NULL){
		fprintf(stdout,ptrList->line);
		ptrList = ptrList->previous;
	}
	printf("%s",ptrList->line);
	return;
}

int main(int argc, char *argv[]){
	LIST *listStart = NULL;
	FILE *inputFile;
	char inputfilename[100];
	char line[1000];
	if(argc < 2){
		fprintf(stdout ,"Not enough arguments, usage: reverse <input>\n");
		exit(1);
	}
	else if(argc > 3){
		fprintf(stdout,"Too many arguments, usage: reverse <input>\n");
		exit(1);
	}
	else{
		if((inputFile = (FILE*)malloc(sizeof(FILE))) == NULL){
			fprintf(stderr,"malloc failed");
			exit(1);
		}
		strcpy(inputfilename,argv[1]);
    	inputFile = fopen(inputfilename,"r");
		if(inputFile == NULL){
        	fprintf(stderr,"error: cannot open file '%s'\n",inputfilename);
        	exit(1);
		}
		while(fgets(line,1000,inputFile) != NULL){
			listStart = addtolist(listStart,line);
    	}
		fclose(inputFile);
		printFromFile(listStart);
	}
	return 0;
}