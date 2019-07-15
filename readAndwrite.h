#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 1024
#define BLOCK 128

#ifndef READANDWRITE
#define READANDWRITE
char* readFromfile (char* fileName);
void writeTofile(char* fileName, char* content);
#endif
