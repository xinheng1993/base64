#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readAndwrite.h"
#include "tools.h"
#include "base64Table.h"
int main(int argc, char* argv[])
{
    char errorMessage[] = "***erroe:\n***command: \n\n\t***base64 encode/decode srcFilename.extension descFilename.extension***\n";
    //command error check
    {
        int i;
        for(i=0;i<3;++i){
            if(argv[i] == 0){
                fprintf(stderr,errorMessage,argv[1]);
                return 0;
            }
        }
    }
    /*initialize file directory*/
    char filedir[BUFFER];
    getcwd(filedir,sizeof(filedir));
    strcat(filedir,"\\");

    //init input file path
    char inFilePath[BUFFER];
    strcpy(inFilePath,filedir);
    strcat(inFilePath,argv[2]);

    //init output file path
    char outFilePath[BUFFER];
    strcpy(outFilePath,filedir);
    strcat(outFilePath,argv[3]);

    //get input string
    char* input = readFromfile(inFilePath);

    printf("src:\n    %s\n\n",input);
    char* result;

    //set lable according to seconde command
    char second[BUFFER];
    strcpy(second,argv[1]);
    str_uppercase(second);
    if(strcmp(second,"DECODE")==0){

        result = decode(input);

    }else if(strcmp(second,"ENCODE")==0){

        result = encode(input);

    }else{
        fprintf(stderr,errorMessage);
        return 0;
    }

    //setup output string

    //write to file
    writeTofile(outFilePath,result);
    //show result on screen
    printf("dest:\n    %s\n",result);
    //free memory
    free(input);
    free(result);
    return 0;
}
