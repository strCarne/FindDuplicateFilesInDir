#include "stdio.h"
#include "dirent.h"
#include "lib.h"
#include "errors.h"
#include "Vector.h"

#define CLI_ARGS_NUM 4

#define DIR_NAME_CLI_ARG 1
#define N1_CLI_ARG 2
#define N2_CLI_ARG 3

int main(int argc, char **argv) {

    if (argc != CLI_ARGS_NUM) {
        printf(ERROR_CLI_ARGS);
        return CLI_ARGS_ERROR_CODE;
    }

    struct ASCIIToIntResp *resp = asciiToInt(argv[N1_CLI_ARG]);
    if (!resp->ok) {
        free(resp);
        printf(ERROR_N1_IS_NOT_A_NUMBER);
        return CLI_ARGS_ERROR_CODE;
    }
    long n1 = resp->value;
    free(resp);

    resp = asciiToInt(argv[N2_CLI_ARG]);
    if (!resp->ok) {
        free(resp);
        printf(ERROR_N2_IS_NOT_A_NUMBER);
        return CLI_ARGS_ERROR_CODE;
    }
    long n2 = resp->value;
    free(resp);

    if (n1 < 0 || n1 > n2) {
        printf(ERROR_N1_N2);
        return CLI_ARGS_ERROR_CODE;
    }

    char *dirName = argv[DIR_NAME_CLI_ARG];
    DIR *dir = opendir(dirName);

    if (!dir) {
        printf(ERROR_OPEN_DIR);
        return INTERNAL_ERROR_CODE;
    }

    Vector storage = newVector(0, 8);
    parseFiles(dir, n1, n2, dirName, &storage);
    closedir(dir);

    printSimilarFiles(storage);

    return 0;
}