#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    FILE *file;
    int i,j,test_empty,compr_number;
    char compr_letter;
    size_t size;

    if(argc<2){
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }
    for(i=1;i<argc;i++){
        file = fopen(argv[i],"r");
        if(file == NULL){   /*testing if file exists*/
            fprintf(stderr,"my-unzip: cannot open file\n");
            exit(1);
        }
        test_empty = fgetc(file);
        if(test_empty == EOF){    /*testing if file is empty*/
            fclose(file);
        }
        rewind(file);
        while(1>0){
            size = fread(&compr_number,sizeof(compr_number),1,file);  /*saving number to compr_number and as size, if size isn't 1,*/ 
            if(size != 1){                                            /*no number is read and the end is reached*/
                fclose(file);
			    break;
		    }
            compr_number = (int) compr_number;
            fread(&compr_letter,sizeof(compr_letter),1,file);
            for(j=0;j<compr_number;j++){
                fwrite(&compr_letter,sizeof(char),1,stdout);    /*writing the compressed letter as many times*/
            }                                                   /*as indicated by the compressed number*/
	    }
    }
    if(argc == 2){      /*Pringing an extra new-line so printing to the*/
        printf("\n");   /*terminal is cleaner*/
    }
    return 0;
}