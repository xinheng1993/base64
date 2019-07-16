#include "readAndwrite.h"
#define READMODEL "r"
#define WRITEMODEL "w"
char* readFromfile (char* fileName){
    FILE* fp;

    printf("open file: \n\n %s\n\n",fileName);
    if((fp=fopen(fileName,READMODEL)) == 0){
        perror("open file falied");
        return 0;
    }
    int c;
    char* content;
    size_t nused, nalloc;
    content = 0;
    nused = nalloc = 0;

    while((c = fgetc(fp)) != EOF){
        if(nused == nalloc){
            char* temp = (char* )realloc(content,(nalloc+BLOCK)*sizeof(char));
            if(temp == 0){
                fprintf(stderr, "realloc failed");
            }
            content = temp;
            nalloc+=BLOCK;
        }
        if((char)c != '\n') content[nused++] = c;
    }
    content[nused] = '\0';
    fclose(fp);
    return content;
}

void writeTofile(char* fileName, char* content){
    FILE* fp;
    
    if((fp=fopen(fileName,WRITEMODEL)) == 0){
        perror("open file falied");
        return;
    }
    fprintf(fp,"%s",content);
    printf("save to file: \n\n %s\n\n",fileName);
    fclose(fp);
}
