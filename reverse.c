#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char line[100]; 
    struct LIST *next;
    struct LIST *previous;
} LIST;


/*void addtolist(LIST *start,char line[100]){
    LIST* new

    return;
}*/

void printToScreen(char *array){


	return;
}


void saveToFile(char argv[]){



	return;
}


int main(int argc, char *argv[]){
	FILE* inputFile,*outputFile;
	char inputfilename[100] = "file.txt";
	char line[100];
    LIST *list = NULL;
	char array[100][200];
	int stepper = 0;

	if((inputFile = (FILE*)malloc(sizeof(FILE))) == NULL){
		printf("Malloc failed.");
		exit(1);
	}
	/*
	inputfilename = *argv[1];

	strcpy(inputfilename,argv[1]);
	printf("%s\n",inputfilename);*/

	if(argc < 2){
		printf("Not enough arguments.");
		exit(1);
	}

    inputFile = fopen("file.txt","r");
	if(inputFile == NULL){
        printf("No such file exists.");
        exit(1);
	}
	while(fgets(line,200,inputFile) != NULL){
        strcpy(array[stepper],line);
		printf("%s",array[stepper]);
		stepper += 1;
    }
	fclose(inputFile);
    
	printf("\n");

	switch(argc){
		case 2:
			for(; stepper > -1; stepper--){
				printf("%s",array[stepper]);
			}
			break;

		case 3:
			if((outputFile = (FILE*)malloc(sizeof(FILE))) == NULL){
				printf("Malloc failed.");
				exit(1);
			}
			outputFile = fopen("output.txt","w");
			if(outputFile == NULL){
				printf("Failed to create file.");
				exit(1);
			}
			for(; stepper > -1; stepper--){
				fputs(array[stepper],outputFile);
			}
			printf("Text copied to file in reverse.\n");
			fclose(outputFile);
			break;

		default:
			printf("Too many arguments\n");
	}
}