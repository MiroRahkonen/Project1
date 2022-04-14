#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[]){
    char *filename,line[1000];
    int i,test;
    FILE *file;

    if(argc < 2){
        exit(0);
    }
    else{
        for(i=1; i<argc; i++){
            filename = argv[i];
            file = fopen(filename,"r");
            if(file == NULL){
                fprintf(stderr,"my-cat: cannot open file\n");
                exit(1);
            }
            test = fgetc(file);
            if(test == EOF){    /*testing if file is empty*/
                fclose(file);
            }
            else{
                rewind(file);
                while(fgets(line,1000,file) != NULL){
                    fprintf(stdout,"%s",line);
                }
            }
        }
    }
    fclose(file);
    return 0;
}
