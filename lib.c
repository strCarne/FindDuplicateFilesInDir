#include "lib.h"

void parseFiles(DIR *dir, long minFileSize, long maxFileSize, char *currDirPath, Vector *storage) {

    struct dirent *entry;
    while ((entry = readdir(dir)) != 0) {

        char *dName = joinPathes(currDirPath, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            DIR *childDir = opendir(dName);
            if (childDir) {
                parseFiles(childDir, minFileSize, maxFileSize, dName, storage);
                closedir(childDir);
            }

        } else {
            long fileSize = sizeOfFile(dName);
            if (minFileSize <= fileSize && fileSize <= maxFileSize) {
                append(*storage, dName);
            }
        }
    }
}

char isDigit(char c) {
    return '0' <= c && c <= '9';
}

int charDigitToInt(char c) {
    return c - '0';
}

struct ASCIIToIntResp *asciiToInt(char const *string) {
    struct ASCIIToIntResp *resp = (struct ASCIIToIntResp *)malloc(sizeof(struct ASCIIToIntResp));

    int size;
    for (size = 0; *(string + size); ++size) {}

    if (size == 0) {
        resp->ok = 0;
        return resp;
    }

    int rank = 1;
    int number = 0;
    for (int i = size - 1; i >= 0; --i, rank *= 10) {
        if (!isDigit(string[i])) {
            resp->ok = 0;
            return resp;
        }

        number += charDigitToInt(string[i]) * rank;
    }

    resp->value = number;
    resp->ok = 1;

    return resp;
}

char *joinPathes(char *path1, char *path2) {
    size_t l1 = strlen(path1);
    size_t l2 = strlen(path2);

    size_t finalLen = l1 + l2 + 1 + 1;
    char *finalPath = calloc(finalLen, sizeof(char));

    int i = 0;
    for (; path1[i] != 0; ++i) {
        finalPath[i] = path1[i];
    }

    finalPath[i++] = '/';

    for (int j = 0; path2[j] != 0; ++j, ++i) {
        finalPath[i] = path2[j];
    }

    return finalPath;
}

long sizeOfFile(char *fileName) {
    struct stat *buffer = calloc(1, sizeof(struct stat));
    stat(fileName, buffer);

    long size = buffer->st_size;
    free(buffer);
    return size;
}

char filesAreSimilar(char *f1, char *f2) {
    char *buffer1 = readFile(f1);
    char *buffer2 = readFile(f2);
    if (buffer1 == buffer2) {
        return 1;
    }
    if (buffer1 == 0 || buffer2 == 0) {
        return 0;
    }
    for (int i = 0; buffer1[i] != 0 && buffer2[i] != 0; ++i) {
        if (buffer1[i] != buffer2[i]) {
            return 0;
        }
    }
    return 1;
}

void printSimilarFiles(Vector storage) {
    for (size_t i = 0; i < storage->len - 1; ++i) {
        long mainFileSize = sizeOfFile(storage->array[i]);
        for (size_t j = i + 1; j < storage->len; ++j) {
            long fileSize = sizeOfFile(storage->array[j]);
            if (mainFileSize != fileSize) {
                continue;
            }

            if (filesAreSimilar(storage->array[i], storage->array[j])) {
                printf("%s == %s ", storage->array[i], storage->array[j]);
                char *content = readFile(storage->array[i]);
                if (content) {
                    printf("Content: \"%s\"\n", content);
                } else {
                    printf("Files are empty\n");
                }
            }
        }
    }
}

char *readFile(char *fileName) {
    long size = sizeOfFile(fileName);

    char *buffer = calloc(size + 1, sizeof(char));

    FILE *fd = fopen(fileName, "rb");
    if (fd == 0) {
        free(buffer);
        return 0;
    }

    if (fread(buffer, size,  1, fd) != 1) {
        free(buffer);
        fclose(fd);
        return 0;
    }

    fclose(fd);
    return buffer;
}