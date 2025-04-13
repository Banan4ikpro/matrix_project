#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Создание матрицы
Matrix* create_matrix(int rows, int cols) {
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        m->data[i] = calloc(cols, sizeof(double));
    return m;
}

// Освобождение памяти
void free_matrix(Matrix *m) {
    for (int i = 0; i < m->rows; i++)
        free(m->data[i]);
    free(m->data);
    free(m);
}

// Загрузка из файла
int load_matrix(const char *filename, Matrix **m) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    int rows, cols;
    fscanf(f, "%d %d", &rows, &cols);
    Matrix *temp = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(f, "%lf", &temp->data[i][j]);
    fclose(f);
    *m = temp;
    return 1;
}

// Печать матрицы
void print_matrix(const Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++)
            printf("%8.2lf ", m->data[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Копирование
Matrix* copy_matrix(const Matrix *m) {
    Matrix *copy = create_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            copy->data[i][j] = m->data[i][j];
    return copy;
}

// Сложение
Matrix* add_matrix(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *res = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] + b->data[i][j];
    return res;
}

// Вычитание
Matrix* sub_matrix(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *res = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] - b->data[i][j];
    return res;
}

// Умножение
Matrix* mul_matrix(const Matrix *a, const Matrix *b) {
    if (a->cols != b->rows) return NULL;
    Matrix *res = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < b->cols; j++)
            for (int k = 0; k < a->cols; k++)
                res->data[i][j] += a->data[i][k] * b->data[k][j];
    return res;
}

// Транспонирование
Matrix* transpose_matrix(const Matrix *m) {
    Matrix *t = create_matrix(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            t->data[j][i] = m->data[i][j];
    return t;
}

// Рекурсивный детерминант
double determinant(Matrix *m) {
    if (m->rows != m->cols) return 0;
    if (m->rows == 1) return m->data[0][0];
    if (m->rows == 2)
        return m->data[0][0]*m->data[1][1] - m->data[0][1]*m->data[1][0];

    double det = 0;
    for (int p = 0; p < m->cols; p++) {
        Matrix *sub = create_matrix(m->rows - 1, m->cols - 1);
        for (int i = 1; i < m->rows; i++) {
            int col = 0;
            for (int j = 0; j < m->cols; j++) {
                if (j == p) continue;
                sub->data[i - 1][col++] = m->data[i][j];
            }
        }
        double sign = (p % 2 == 0) ? 1 : -1;
        det += sign * m->data[0][p] * determinant(sub);
        free_matrix(sub);
    }
    return det;
}

