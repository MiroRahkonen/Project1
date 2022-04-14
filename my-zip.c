#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[]){
    FILE *inputfile;
    int i, counter = 1, emptytest;
	char current_char, next_char;

    if(argc<2){
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

	for(i=1;i<argc;i++){
		inputfile = fopen(argv[i],"r");
    	if(inputfile == NULL){
        	fprintf(stderr,"my-unzip: cannot open file\n");
        	exit(1);
    	}
    	emptytest = fgetc(inputfile);
    	if(emptytest == EOF){    /*testing if file is empty*/
        	fclose(inputfile);
	    }
    	rewind(inputfile);
		current_char = fgetc(inputfile);	/*reading the first letter which will be used in comparison*/
		while(1>0){
			next_char = fgetc(inputfile);
			if(next_char == EOF){
				fclose(inputfile);	/*if char is EOF there is no more text in the file*/
				break;
			}
			if(current_char == next_char){
				counter++;			/*counter keeps track of how many repeating letters there are back to back*/
			}
			else{
				fwrite(&counter,sizeof(counter),1,stdout);		/*Writing the compressed number and letter*/
				fwrite(&current_char,sizeof(char),1,stdout);	/*to the file and resetting counter*/
				counter = 1;
			}
			current_char = next_char;	/*saving the second letter as the new first letter for next comparison*/
		}
	}
    return 0;
}
