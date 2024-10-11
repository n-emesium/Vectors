#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define LIM 100
#define swapi(v, i, j) (iswap(v, i, j))
#define swapf(v, i, j) (fswap(v, i, j))
#define swapc(v, i, j) (cswap(v, i, j))
static char alph[26];
void init() {
    int i = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        alph[i] = c;
        i++;
    }
}
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
} data_type;
typedef struct vector {
    data_type type;
    size_t size; //number of elements
    size_t elem_size;
    void *arr;
} vector;
vector *create(size_t size, data_type type) {
    vector *v = (vector *)malloc(sizeof(vector));
    switch (type) {
        case TYPE_INT:
            v->elem_size = sizeof(int);
            break;
        case TYPE_FLOAT:
            v->elem_size = sizeof(float);
            break;
        case TYPE_CHAR:
            v->elem_size = sizeof(char);
            break;
        default: 
            free(v);
            return NULL;
    }
    v->arr = malloc(size * v->elem_size);
    v->type = type;
    v->size = size;
    return v;
}
void delete(vector *v, int index) {
    switch (v->type) {
        case TYPE_INT:
            for (int i = index; i < v->size - 1; i++) {
                ((int *)v->arr)[i] = ((int *)v->arr)[i+1];
            }
            break;
        case TYPE_FLOAT:
            for (int i = index; i < v->size - 1; i++) {
                ((float *)v->arr)[i] = ((float *)v->arr)[i + 1];
            }
            break;
        case TYPE_CHAR:
            for (int i = index; i < v->size -1; i++) {
                ((char *)v->arr)[i] = ((char * )v->arr)[i + 1];
            }
            break;
    }
    v->arr = realloc(v->arr, (v->size - 1) * v->elem_size);
    v->size--;
}
void pop(vector *v) {
    v->arr = realloc(v->arr, (v->size - 1) * v->elem_size);
    v->size--;
}
void push_back(vector *v, void *val) {
    v->arr = realloc(v->arr, (v->size + 1) * v->elem_size);
    v->size++;
    switch (v->type) {
        case TYPE_INT:
            ((int *)v->arr)[v->size - 1] = *(int *)val;
            break;
        case TYPE_FLOAT:
            ((float *)v->arr)[v->size - 1] = *(float *)val;
            break;
        case TYPE_CHAR:
            ((char *)v->arr)[v->size - 1] = *(char *)val;
            break;
    }
}
void add(vector *v, int index, void *val) {
    v->arr = realloc(v->arr, (v->size + 1) * v->elem_size);
    v->size++;
    switch (v->type) {
        case TYPE_INT:
            for (int i = index; i < v->size - 1; i++) {
                ((int *)v->arr)[i + 1] = ((int *)v->arr)[i];
            }
            ((int *)v->arr)[index] = *(int *)val;
            break;
        case TYPE_FLOAT:
            for (int i = index; i < v->size - 1; i++) {
                ((float *)v->arr)[i + 1] = ((float *)v->arr)[i];
            }
            ((float *)v->arr)[index] = *(float *)val;
            break;
        case TYPE_CHAR:
            for (int i = index; i < v->size - 1; i++) {
                ((char *)v->arr)[i + 1] = ((char *)v->arr)[i];
            }
            ((char *)v->arr)[index] = *(char *)val;
            break;
    }
}
void set(vector *v, int index, void *val) {
    switch (v->type) {
        case TYPE_INT:
            ((int *)v->arr)[index] = *(int *)val;
            break;
        case TYPE_FLOAT:
            ((float *)v->arr)[index] = *(float *)val;
            break;
        case TYPE_CHAR:
            ((char *)v->arr)[index] = *(char *)val;
            break;
    }
}
bool sorted(vector *v) {
    if (v->type == TYPE_INT) {
        int *arr = (int *)v->arr;
        for (int i = 0; i < v->size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
    } else if (v->type == TYPE_FLOAT) {
        float *arr = (float *)v->arr;
        for (int i = 0; i < v->size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
    } else {
        char *arr = (char *)v->arr;
        for (int i = 0; i < v->size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
    }
    return true;
}
int bins(vector *v, int n) {
    int *arr = (int *)v->arr;
    int l = 0;
    int h = v->size - 1;
    while (l <= h) {
        int mid = (l + h) / 2;
        if (arr[mid] == n) {
            return mid;
        } else if (arr[mid] > n) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}
int findex(vector *v, void *find) {
    switch (v->type) {
        case TYPE_INT:
            if (sorted(v)) {
                return bins(v, *(int *)find);
            } else {
                int *arr = (int *)v->arr;
                int n = *(int *)find;
                for (int i = 0; i < v->size; i++) {
                    if (arr[i] == n) {
                        return i;
                    }
                }
            }
            break;
        case TYPE_FLOAT:
            if (sorted(v)) {
                return bins(v, *(float *)find);
            } else {
                float *arr = (float *)v->arr;
                float n = *(float *)find;
                for (int i = 0; i < v->size; i++) {
                    if (arr[i] == n) {
                        return i;
                    }
                }
            }
            break;
        case TYPE_CHAR:
            if (sorted(v)) {
                return bins(v, *(char *)find);
            } else {
                char *arr = (char *)v->arr;
                char c = *(char *)find;
                for (int i = 0; i < v->size; i++) {
                    if (arr[i] == c) {
                        return i;
                    }
                }
            }
            break;
    }
    return -1;
}

void iswap(vector *v, int i, int j) {
    //integer
    int x = ((int *)v->arr)[i];
    ((int *)v->arr)[i] = ((int *)v->arr)[j];
    ((int *)v->arr)[j] = x;
}
void fswap(vector *v, int i, int j) {
    //float
    float x = ((float *)v->arr)[i];
    ((float *)v->arr)[i] = ((float *)v->arr)[j];
    ((float *)v->arr)[j] = x;
}
void cswap(vector *v, int i, int j) {
    //char
    char x = ((char *)v->arr)[i];
    ((char *)v->arr)[i] = ((char *)v->arr)[j];
    ((char *)v->arr)[j] = x;
}

int pivot(vector *v, int l, int r) {
    int start = l;
    int end = r - 1;
    int lswap = start;
    switch (v->type) {
        case TYPE_INT: {
            int *arr = (int *)v->arr;
            int p = arr[r]; // pivot
            for (int i = start; i <= end; i++) {
                if (arr[i] < p) {
                    iswap(v, i, lswap);
                    lswap++;
                }
            }
            iswap(v, lswap, r);
            return lswap;
        }
        case TYPE_FLOAT: {
            // Similar logic for float
            float *arr = (float *)v->arr;
            float p = arr[r];
            for (int i = start; i <= end; i++) {
                if (arr[i] < p) {
                    fswap(v, i, lswap);
                    lswap++;
                }
            }
            fswap(v, lswap, r);
            return lswap;
            break;
        }
        case TYPE_CHAR: {
            // Similar logic for char
            char *arr = (char *)v->arr;
            char p = arr[r];
            for (int i = start; i <= end; i++) {
                if (arr[i] < p) {
                    cswap(v, i, lswap);
                    lswap++;
                }
            }
            cswap(v, lswap, r);
            return lswap;
            break;
        }
    }
    return -1; // Handle error
}
void sort(vector *v, int l, int r) { 
    if (l < r) {
        int piv = pivot(v, l, r);
        sort(v, l, piv - 1);
        sort(v, piv + 1, r);
    }
}
void printv(vector *v) {
    switch (v->type) {
        case TYPE_INT: {
            int *arr = (int *)v->arr;
            for (int i = 0; i < v->size; i++) {
                printf("%d ", arr[i]);
            }
        }
            break;
        case TYPE_FLOAT: {
            float *arr = (float *)v->arr;
            for (int i = 0; i < v->size; i++) {
                printf("%.2f ", arr[i]);
            }
        }
            break;
        case TYPE_CHAR: {
            char *arr = (char *)v->arr;
            for (int i = 0; i < v->size; i++) {
                putchar(arr[i]);
                putchar(' ');
            }
        }
            break;
    }
    printf("\n");
}
void fill(vector *v) {
    switch (v->type) {
        case TYPE_INT:
            for (int i = 0; i < v->size; i++) {
                ((int *)v->arr)[i] = rand() % LIM;
            }
            break;
        case TYPE_FLOAT:
            for (int i = 0; i < v->size; i++) {
                ((float *)v->arr)[i] = rand() % LIM;
            }
            break;
        case TYPE_CHAR:
            init();
            for (int i = 0; i < v->size; i++) {
                ((char *)v->arr)[i] = alph[rand() % 26];
            }
            break;
    }
}
void flush(vector *v) { //sets size to 0
    v->arr = realloc(v->arr, 0);
    v->size = 0;
}
void clear(vector *v) { //sets all elements to 0
    switch (v->type) {
        case TYPE_INT:
            for (int i = 0; i < v->size; i++) {
                ((int *)v->arr)[i] = 0;
            }
            break;
        case TYPE_FLOAT:
            for (int i = 0; i < v->size; i++) {
                ((float *)v->arr)[i] = 0.0;
            }
            break;
        case TYPE_CHAR:
            for (int i = 0; i < v->size; i++) {
                ((char *)v->arr)[i] = '0';
            }
            break;
    }
}
void shuffle(vector *v) { //this function will guarantee an unbiased shuffle;
    switch (v->type) {
        case TYPE_INT:
            for (int i = v->size - 1; i > 0; i--) { //[0, ... , size - 1]; len = size
                int x = rand() % (i + 1); //x < i
                iswap(v, i, x);
            }
            //iswap(v, 0, v->size - 1);
            break;
        case TYPE_FLOAT:
            for (int i = v->size - 1; i > 0; i--) {
                int x = rand() % (i + 1);
                fswap(v, i, x);
            }
            //fswap(v, 0, v->size - 1);
            break;
        case TYPE_CHAR:
            for (int i = v->size - 1; i > 0; i--) {
                int x = rand() % (i + 1);
                cswap(v, i, x);
            }
            //swapc(v, 0, v->size - 1);
            break;
    }
}
void freev(vector *v) {
    free(v->arr);
    free(v);
}
int main() {
    srand(time(NULL));
    vector *v = create(20, TYPE_INT);
    fill(v);
    printv(v);
    shuffle(v);
    printv(v);
    freev(v);
    return 0;
}