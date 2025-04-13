#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Загрузка матрицы с автоматическим определением размеров
int load_matrix(const char *filename, Matrix **m) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    char line[1024];
    int rows = 0;
    int cols = -1;

    // Первый проход — определим размеры
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) == 0 || line[0] == '\n') continue;

        int temp_cols = 0;
        char *token = strtok(line, " \t\n\r");
        while (token != NULL) {
            temp_cols++;
            token = strtok(NULL, " \t\n\r");
        }

        if (cols == -1) {
            cols = temp_cols; // Запоминаем количество столбцов по первой строке
        } else if (cols != temp_cols) {
            fclose(file);
            return -2; // Разное количество столбцов — ошибка формата
        }

        rows++;
    }

    rewind(file); // Сбросить указатель файла для второго прохода

    // Выделяем память
    *m = (Matrix *)malloc(sizeof(Matrix));
    (*m)->rows = rows;
    (*m)->cols = cols;
    (*m)->data = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*m)->data[i] = (int *)malloc(cols * sizeof(int));
    }

    // Второй проход — читаем данные
    int r = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) == 0 || line[0] == '\n') continue;

        int c = 0;
        char *token = strtok(line, " \t\n\r");
        while (token != NULL && c < cols) {
            (*m)->data[r][c++] = atoi(token);
            token = strtok(NULL, " \t\n\r");
        }
        r++;
    }

    fclose(file);
    return 0;
}


// Транспонирование матрицы
Matrix* transpose_matrix(const Matrix *m) {
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->rows = m->cols;
    result->cols = m->rows;
    result->data = (int **)malloc(result->rows * sizeof(int *));
    for (int i = 0; i < result->rows; i++) {
        result->data[i] = (int *)malloc(result->cols * sizeof(int));
    }

    // Заполнение транспонированной матрицы
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[j][i] = m->data[i][j];
        }
    }

    return result;
}

// Сложение двух матриц
int add_matrices(const Matrix *m1, const Matrix *m2, Matrix **result) {
    if (!m1 || !m2) return -1;
    if (m1->rows != m2->rows || m1->cols != m2->cols) return -2;

    *result = (Matrix *)malloc(sizeof(Matrix));
    if (!(*result)) return -3;

    (*result)->rows = m1->rows;
    (*result)->cols = m1->cols;
    (*result)->data = (int **)malloc((*result)->rows * sizeof(int *));
    for (int i = 0; i < (*result)->rows; i++) {
        (*result)->data[i] = (int *)malloc((*result)->cols * sizeof(int));
    }

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            (*result)->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }

    return 0;
}


// Вычитание двух матриц
int subtract_matrices(const Matrix *m1, const Matrix *m2, Matrix **result) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return -1;
    }

    *result = malloc(sizeof(Matrix));
    if (!*result) return -1;

    (*result)->rows = m1->rows;
    (*result)->cols = m1->cols;
    (*result)->data = malloc((*result)->rows * sizeof(int *));
    if (!(*result)->data) return -1;

    for (int i = 0; i < (*result)->rows; i++) {
        (*result)->data[i] = malloc((*result)->cols * sizeof(int));
        if (!(*result)->data[i]) return -1;
    }

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            (*result)->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }

    return 0;
}


// Умножение двух матриц
int multiply_matrices(const Matrix *m1, const Matrix *m2, Matrix **result) {
    if (m1->cols != m2->rows) {
        return -1;
    }
	
    *result = (Matrix *)malloc(sizeof(Matrix));
	
    if (!*result) return -1;

    (*result)->rows = m1->rows;
    (*result)->cols = m2->cols;
    (*result)->data = (int **)malloc((*result)->rows * sizeof(int *));
    if (!(*result)->data) return -1;

    for (int i = 0; i < (*result)->rows; i++) {
        (*result)->data[i] = (int *)malloc((*result)->cols * sizeof(int));
        if (!(*result)->data[i]) return -1;
    }

    for (int i = 0; i < (*result)->rows; i++) {
        for (int j = 0; j < (*result)->cols; j++) {
            (*result)->data[i][j] = 0;
            for (int k = 0; k < m1->cols; k++) {
                (*result)->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }

    return 0;
}

// Сохранение матрицы в файл
int save_matrix(const char *filename, const Matrix *m) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    

    // Запись данных матрицы
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(file, "%d ", m->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

// Освобождение памяти, занятой матрицей
void free_matrix(Matrix *m) {
    if (m) {
        for (int i = 0; i < m->rows; i++) {
            free(m->data[i]);
        }
        free(m->data);
        free(m);
    }
}


