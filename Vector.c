#include "Vector.h"

Vector newVector(size_t length, size_t capacity) {
    struct Vector *v = malloc(sizeof(struct Vector));
    if (length <= capacity) {
        v->len = length;
        v->cap = capacity;
    } else {
        v->len = 0;
        v->cap = 4;
    }

    v->array = calloc(v->cap, sizeof(char *));
    return v;
}

void resize(Vector v, size_t len) {
    if (len <= v->cap) {
        v->len = len;
        return;
    }

    size_t cap = len + len / 2;
    char **array = calloc(cap, sizeof(char *));
    for (int i = 0; i < v->len; ++i) {
        array[i] = v->array[i];
    }

    free(v->array);
    v->array = array;
    v->len = len;
    v->cap = cap;
}

void append(Vector v, char *elem) {
    resize(v, v->len + 1);
    v->array[v->len - 1] = elem;
}