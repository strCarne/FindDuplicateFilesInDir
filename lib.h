#ifndef LIB_H
#define LIB_H

#define _DEFAULT_SOURCE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "sys/stat.h"
#include "Vector.h"

void parseFiles(DIR *dir, long minFileSize, long maxFileSize, char *currDirPath, Vector *storage);

struct ASCIIToIntResp  {
    int value;
    char ok;
};

struct ASCIIToIntResp *asciiToInt(char const *string);

char *joinPathes(char *path1, char *path2);

long sizeOfFile(char *fileName);

void printSimilarFiles(Vector storage);

char *readFile(char *fileName);

#endif