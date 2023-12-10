#ifndef VECTOR_H
#define VECTOR_H

#include "stdlib.h"

typedef struct Vector* Vector;

struct Vector {
    char **array;
    size_t len;
    size_t cap;
};

Vector newVector(size_t length, size_t capacity);

void append(Vector v, char *elem);

#endif