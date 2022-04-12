#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char line[1000]; 
    struct list *next;
    struct list *previous;
}LIST;


LIST *addtolist(LIST *listStart,char line[1000]){	/*This function adds the line to the end of the list*/
	LIST *newNode,*ptrList;
    if((newNode = (LIST*) malloc(sizeof(LIST))) == NULL){	/*allocating space for*/
		fprintf(stderr,"malloc failed");					/*the next node in the list*/
		exit(1);
	}
	strcpy(newNode->line,line);
	if(listStart == NULL){			/*Here we either make the new node the start of the list*/
		listStart = newNode;		/*or find the last place in the list and add it as the*/
		listStart->previous = NULL;	/*last one*/
		listStart->next = NULL;
	}
	else{
		ptrList = listStart;
		while(ptrList->next != NULL){
			ptrList = ptrList->next;
		}
		newNode->previous = ptrList;
		newNode->next = NULL;
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
		fprintf(stdout,"%s",ptrList->line);	/*and go towards the start of the list*/
		ptrList = ptrList->previous;
	}
	fprintf(stdout,"%s",ptrList->line);		/*We print the last one remaining*/
	return;
}

int main(int argc, char *argv[]){
	LIST *listStart = NULL;
	FILE *inputFile;
	char inputfilename[100];
	char line[1000];
	int test;
	if(argc != 2){
		fprintf(stdout ,"usage: reverse <input>\n");
		exit(1);
	}
	else{
		strcpy(inputfilename,argv[1]);	/*Copying the second argument as the input file name*/
    	inputFile = fopen(inputfilename,"r");
		if(inputFile == NULL){
        	fprintf(stderr,"error: cannot open file '%s'\n",inputfilename);
        	exit(1);
		}
		test = fgetc(inputFile);
		if(test == EOF){		/*testing if file is empty*/
			fclose(inputFile);
			exit(1);
		}
		else{
			rewind(inputFile);	/*Going to the start of the file so the first character doesn't get removed*/
			while(fgets(line, 1000, inputFile) != NULL){	/*Reading lines from the file and sending them*/
				listStart = addtolist(listStart, line);		/*to the function that adds them to the linked list*/
    		}
		}
		fclose(inputFile);
		printFromFile(listStart);	/*calling the function that prints the list in reverse*/
	}
	return 0;
}