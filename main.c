#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _MAX_STR_BUFFER 255

FILE *open_file(char *filename,FILE *fp,char *mode){
    fp=fopen(filename,mode);
    if(!fp){
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void close_file(const char *input,char *filename,FILE *in_fp,FILE *out_fp){
    fclose(in_fp);
    fclose(out_fp);
    remove(input);
    rename(filename,input);
}

void process(const char *input){
    char filename[_MAX_STR_BUFFER]={};
    char readin[_MAX_STR_BUFFER]={};
    int line=0;                                 //current line number
    const int Start_line=16;
    const int End_line=22;
    FILE *in_fp,*out_fp;

/*  open files    */
    strcpy(filename,input);
    in_fp=open_file(filename,in_fp,"r");
    out_fp=open_file(strcat(filename,"0"),out_fp,"w");    //TEMP file for output

/*  read in and write out, skipping the problem lines    */
    while(!feof(in_fp)){
        fgets(readin,255,in_fp);
        line++;
        if(line<Start_line||line>End_line)        //skip the lines between Start_line and End_line
            fputs(readin,out_fp);
    }
    close_file(input,filename,in_fp,out_fp);
}

int main(int argc, char **argv){
    if(argc<2){
        printf("Please specify a file as input\n");
        exit(EXIT_FAILURE);
    }
    int file_count=1;

    while(file_count<argc){
        process(argv[file_count]);
        file_count++;
    }
    return 0;
}
