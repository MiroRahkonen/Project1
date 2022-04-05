#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[]){
    char *filename,line[1000];
    int i,test;
    FILE *file;

    if(argc < 2){   /*Testing if a filename is provided*/
        fprintf(stdout,"my-cat: [file ...]\n");
        exit(0);
    }
    else{
        for(i=1; i<argc; i++){
            filename = argv[i];
            file = fopen(filename,"r");
            if(file == NULL){       /*Testing if the file is in current directory*/
                fprintf(stderr,"my-cat: cannot open file\n");
                exit(1);
            }
            test = fgetc(file);
            if(test == EOF){    /*Testing if file is empty in which case*/
                fclose(file);   /*the file is closed and nothing is read*/
            }
            else{
                rewind(file);   /*Going back to start of file so nothing is skipped*/
                while(fgets(line,1000,file) != NULL){
                    fprintf(stdout,"%s",line);  /*Printint file line by line*/
                }
            }
        }
    }
    fclose(file);
    return 0;
}