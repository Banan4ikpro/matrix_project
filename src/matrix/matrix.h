#ifndef MATRIX_H
#define MATRIX_H

#include "config.h"

typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

// Функции для работы с матрицами
int load_matrix(const char *filename, Matrix **m);      // Загрузка матрицы
Matrix* transpose_matrix(const Matrix *m);              // Транспонирование
int add_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); // Сложение матриц
int subtract_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); // Вычитание матриц
int multiply_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); // Умножение матриц
int save_matrix(const char *filename, const Matrix *m);  // Сохранение матрицы в файл
void free_matrix(Matrix *m); // Освобождение памяти

#endif

