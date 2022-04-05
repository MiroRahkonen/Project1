#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc,char *argv[]){
    FILE *file;
    int i,test;
    char *filename,*line,*searchword;
    size_t len = 0;
    
    if(argc < 2){  /*Testing if a searchterm is provided*/
        fprintf(stdout,"my-grep: searchterm [file ...]\n");
        exit(0);
    }
    else if(argc == 2){ /*Only a searchterm is provided, reading from stdin*/
        searchword = argv[1];
        int asciivalue = (int) searchword[0];
        strcpy(searchword,argv[1]);
        while (getline(&line,&len,stdin) != -1) {
		    if(line[0] == '\n'){
			    break;
            }
            else if(asciivalue == -62){         /*ascii value of empty string is -62*/
                fprintf(stdout,"%s",line);      /*in which case everything is printed*/
            }
            else if(strstr(line,searchword) != NULL){   /*checking if strstr returns something other than NULL*/
                fprintf(stdout,"%s",line);              /*which means the word is included in the line*/
            }
		}
    }
    else{ /*Searching text from all provided filenames*/  
        searchword = argv[1];
        int asciivalue = (int) searchword[0];   /*Getting ascii value of first character which*/
        for(i=2; i<argc; i++){                  /*is used to check if it is an empty string*/
            filename = argv[i];
            file = fopen(filename,"r");
            if(file == NULL){       /*checking if file exists*/
                fprintf(stderr,"my-grep: cannot open file\n");
                exit(1);
            }

            test = fgetc(file);
            if(test == EOF){    /*testing if file is empty in which case*/
                fclose(file);   /*the file is skipped*/
            }
            else{
                rewind(file);   /*Going back to the start so no characters are skipped*/
                while(getline(&line,&len,file) != -1){
                    if(asciivalue == -62){          /*ascii value of empty string is -62*/
                        fprintf(stdout,"%s",line);  /*in which case everything is printed*/
                    }
                    else if(strstr(line,searchword) != NULL){    /*checking if strstr returns something which*/
                        fprintf(stdout,"%s",line);          /*means the word is included in the line*/
                    }
                }
                fclose(file);
            }
        }
    }
    return 0;
}