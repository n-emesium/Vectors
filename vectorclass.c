#include <stddef.h>
#include <stdio.h>
#include <vectorlib.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int mcapacity;
    int size;
    int *arr;
} vector;
int indexof(vector *v, int n) { //n is the element to be searched for;
    int index = -1;
    for (int i = 0; i < v->size; i++) {
        if (v->arr[i] == n) {
            index = i;
            break;
        }
    }
    return index;
}
void create(vector *v) {
    v->arr = (int *)malloc(10 * sizeof(int));
    if (v->arr == NULL) {
        printf("Cannot allocate memory. ");
        exit(EXIT_FAILURE);
    }
    v->size = 0;
    v->mcapacity = 10;
}
bool checkc(vector *v) {
    if (v->size == v->mcapacity) {
        v->mcapacity *= 2;
        v->arr = (int *)realloc(v->arr, v->mcapacity * sizeof(int));
        if (v->arr == NULL) {
            printf("Reallocation failed, terminating program. ");
            return false;
        }
    }
    return true;
}
void push(vector *v, int n) {
    if (checkc(v)) {
        v->arr[v->size] = n;
        v->size++;  
    }
}
void push_at(vector *v, int i, int n) {
    if (checkc(v)) {
        for (int c = i; c < v->size-1; c++) {
            v->arr[c + 1] = v->arr[c]; 
        }
        v->arr[i] = n;
        v->size++;
    }
}
int pull(vector *v, int n) { //for removing a specific element;
    int i = indexof(v,n);
    if (i == -1) {
        printf("No such element found. ");
        return;
    }
    int f = v->arr[i];
    for (int j = i; j < v->size-1; j++) {
        v->arr[j] = v->arr[j+1];
    }
    v->arr = (int *)realloc(v->arr, (v->size - 1) * sizeof(int));
    v->size--;
    return f;
}
int pull_at(vector *v, int i) { //removes the element at the specified index;
    int f = v->arr[i];
    for (int j = i+1; j < v->size; j++) {
        v->arr[j-1] = v->arr[j];
    }
    v->arr = (int *)realloc(v->arr, (v->size - 1) * sizeof(int));
    v->size--;
    return f;
}
void vfree(vector *v) {
    free(v->arr);
    free(v);
}