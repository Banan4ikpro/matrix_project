#ifndef MATRIX_H
#define MATRIX_H

#include "config.h"

typedef struct {
    int rows;
    int cols;
    elem_t **data;
} Matrix;

Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix *m);

int load_matrix(const char *filename, Matrix **m);
void print_matrix(const Matrix *m);

Matrix* copy_matrix(const Matrix *m);
Matrix* add_matrix(const Matrix *a, const Matrix *b);
Matrix* sub_matrix(const Matrix *a, const Matrix *b);
Matrix* mul_matrix(const Matrix *a, const Matrix *b);
Matrix* transpose_matrix(const Matrix *m);
double determinant(Matrix *m);

#endif

