#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define LIM 100
#define swapi(v, i, j) (iswap(v, i, j))
#define swapf(v, i, j) (fswap(v, i, j))
#define swapc(v, i, j) (cswap(v, i, j))
#define vprint(v) (printv(v))
#define tint TYPE_INT
#define tfloat TYPE_FLOAT
#define tchar TYPE_CHAR
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
void usort(vector *v, int l, int r) { 
    if (l < r) {
        int piv = pivot(v, l, r);
        usort(v, l, piv - 1);
        usort(v, piv + 1, r);
    }
}
void sort(vector *v) {
    usort(v, 0, v->size - 1);
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
/**
 * Merges two vectors into a new vector.
 * 
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return A new vector containing elements of both vectors.
 */

vector *merge(vector *v1, vector *v2) {
    if (v1->type == v2->type) {
        vector *v3 = create(v1->size + v2->size, v1->type);
        if (v1->type == tint) {
            for (int i = 0; i < v1->size; i++) {
                ((int *)v3->arr)[i] = ((int *)v1->arr)[i];
            }
            for (int i = 0; i < v2->size; i++) {
                ((int *)v3->arr)[i + v1->size] = ((int *)v2->arr)[i];
            }
        } else if (v1->type == tfloat) {
            for (int i = 0; i < v1->size; i++) {
                ((float *)v3->arr)[i] = ((float *)v1->arr)[i];
            }
            for (int i = 0; i < v2->size; i++) {
                ((float *)v3->arr)[i + v1->size] = ((float *)v2->arr)[i];
            }
        } else if (v1->type == tchar) {
            for (int i = 0; i < v1->size; i++) {
                ((char *)v3->arr)[i] = ((char *)v1->arr)[i];
            }
            for (int i = 0; i < v2->size; i++) {
                ((char *)v3->arr)[i + v1->size] = ((char *)v2->arr)[i];
            }
        }
        
        return v3;
    } else {
        printf("Fatal error: vector types do not match.\n");
        return NULL;
    }
}

void reverse(vector *v) {
    switch (v->type) {
        case tint:
            for (int i = 0; i < v->size / 2; i++) {
                iswap(v, i, v->size - i - 1);
            }
            break;
        case tfloat:
            for (int i = 0; i < v->size / 2; i++) {
                fswap(v, i, v->size - i - 1);
            }
            break;
        case tchar:
            for (int i = 0; i < v->size / 2; i++) {
                cswap(v, i, v->size - i - 1);
            }
            break;
    }
}
vector *clone(vector *v) {
    if (v == NULL) {
        printf("Fatal error: vector is NULL.\n");
        return NULL;
    }
    vector *c = create(v->size, v->type);
    if (v->type == tint) {
        for (int i = 0; i < v->size; i++) {
            ((int *)c->arr)[i] = ((int *)v->arr)[i];
        }
    } else if (v->type == tfloat) {
        for (int i = 0; i < v->size; i++) {
            ((float *)c->arr)[i] = ((float *)v->arr)[i];
        }
    } else if (v->type == tchar) {
        for (int i = 0; i < v->size; i++) {
            ((char *)c->arr)[i] = ((char *)v->arr)[i];
        }
    }
    return c;
}
void freev(vector *v) {
    free(v->arr);
    free(v);
}
void driver() { //you can use this to test your code
    // Test for Integer Vector
    init();
    srand(time(NULL));
    printf("Testing Integer Vector:\n");
    vector *v_int = create(10, TYPE_INT);
    fill(v_int);
    printf("Filled Vector: ");
    printv(v_int);
    
    shuffle(v_int);
    printf("Shuffled Vector: ");
    printv(v_int);
    
    sort(v_int);
    printf("Sorted Vector: ");
    printv(v_int);
    
    int val_to_add = 42;
    push_back(v_int, &val_to_add);
    printf("After Push Back (42): ");
    printv(v_int);
    
    int index_to_delete = 3; // Delete index 3
    delete(v_int, index_to_delete);
    printf("After Deleting Index 3: ");
    printv(v_int);
    
    // Cleanup
    freev(v_int);
    
    // Test for Float Vector
    printf("\nTesting Float Vector:\n");
    vector *v_float = create(5, TYPE_FLOAT);
    fill(v_float);
    printf("Filled Vector: ");
    printv(v_float);
    
    sort(v_float);
    printf("Sorted Vector: ");
    printv(v_float);
    
    float float_val_to_add = 3.14;
    push_back(v_float, &float_val_to_add);
    printf("After Push Back (3.14): ");
    printv(v_float);
    
    // Cleanup
    freev(v_float);
    
    // Test for Character Vector
    printf("\nTesting Character Vector:\n");
    vector *v_char = create(8, TYPE_CHAR);
    fill(v_char);
    printf("Filled Vector: ");
    printv(v_char);
    
    sort(v_char);
    printf("Sorted Vector: ");
    printv(v_char);
    
    char char_val_to_add = 'z';
    push_back(v_char, &char_val_to_add);
    printf("After Push Back ('z'): ");
    printv(v_char);
    
    // Cleanup
    freev(v_char);
}

int main() {
    driver(); // Call the driver function to test
    return 0;
}
