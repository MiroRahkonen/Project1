#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char line[100]; 
    struct list *next;
    struct list *previous;
}LIST;


LIST *addtolist(LIST *listStart,char line[100]){	/*This function adds the line to the end of the list*/
	LIST *newNode,*ptrList;
    if((newNode = (LIST*) malloc(sizeof(LIST))) == NULL){	/*allocating space for*/
		fprintf(stderr,"malloc failed");					/*the next node in the list*/
		exit(1);
	}
	strcpy(newNode->line,line);
	newNode->next = NULL;

	if(listStart == NULL){			/*Here we either make the new node the start of the list*/
		listStart = newNode;		/*or find the last place in the list and add it as the*/
		listStart->previous = NULL;	/*last one*/
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

void printFromFile(LIST *listStart){	/*This function prints all the lines from the linked list*/
	LIST *ptrList;
	ptrList = listStart;
	while(ptrList->next != NULL){		/*Here we go to the end of the list*/
		ptrList = ptrList->next;
	}
	while(ptrList->previous != NULL){	/*We start printing from the last one*/
		fprintf(stdout,ptrList->line);	/*and go towards the start of the list*/
		ptrList = ptrList->previous;
	}
	fprintf(stdout,ptrList->line);		/*We print the last one remaining*/
	return;
}

int main(int argc, char *argv[]){
	LIST *listStart = NULL;
	FILE *inputFile;
	char inputfilename[100];
	char line[1000];
	if(argc != 2){
		fprintf(stdout ,"usage: reverse <input>\n");
		exit(1);
	}
	else{
		if((inputFile = (FILE*)malloc(sizeof(FILE))) == NULL){
			fprintf(stderr,"malloc failed");
			exit(1);
		}
		strcpy(inputfilename,argv[1]);	/*Copying the second argument as the input file name*/
    	inputFile = fopen(inputfilename,"r");
		if(inputFile == NULL){
        	fprintf(stderr,"error: cannot open file '%s'\n",inputfilename);
        	exit(1);
		}
		while(fgets(line,1000,inputFile) != NULL){	/*Reading lines from the file and sending them*/
			listStart = addtolist(listStart,line);	/*to the function that adds them to the linked list*/
    	}
		fclose(inputFile);
		printFromFile(listStart);
	}
	return 0;
}