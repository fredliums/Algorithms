#ifndef __MATRIX_H__
#define __MATRIX_H__

#define MATRIX_MAX_W 999

typedef struct _Matrix {
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix* init_matrix(Matrix *L, int m, int n);
Matrix* new_matrix(int m, int n);
Matrix* copy_matrix(Matrix *L, Matrix *N);
Matrix* set_matrix(Matrix *L, int value);
void print(const Matrix *L);
void free_matrix(Matrix *L);

#endif

