#ifndef vectorlib
#define vectorlib
#include <stdbool.h>
#include <stddef.h>
typedef struct {
    int mcapacity;
    int size;
    int *arr;
} vector;
int indexof(vector *v, int n);
void create(vector *v);
bool checkc(vector *v);
void push(vector *v, int n);
void push_at(vector *v, int i, int n);
int pull(vector *v, int n);
int pull_at(vector *v, int i);
void vfree(vector *v);
#endif