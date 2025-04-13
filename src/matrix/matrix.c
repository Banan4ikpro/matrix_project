#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file matrix.c
 * @brief Основная реализация операций с матрицами
 */

/**
 * @brief Загружает матрицу из текстового файла
 * @param filename Имя файла
 * @return Указатель на загруженную матрицу или NULL в случае ошибки
 */
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


/**
 * @brief Транспонирует матрицу
 * @param Matrix Указатель на матрицу
 * @return Указатель на новую транспонированную матрицу, либо NULL в случае ошибки
 */ 
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

/**
 * @brief Складывает две матрицы
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае ошибки
 */
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


/**
 * @brief Вычитает одну матрицу из другой
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат вычитания, либо NULL в случае ошибки
 */
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


/**
 * @brief Умножает две матрицы
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат умножения, либо NULL в случае ошибки
 */
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

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param Matrix Указатель на матрицу
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int save_matrix(const char *filename, const Matrix *m) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(file, "%d ", m->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param Matrix Указатель на матрицу
 */
void free_matrix(Matrix *m) {
    if (m) {
        for (int i = 0; i < m->rows; i++) {
            free(m->data[i]);
        }
        free(m->data);
        free(m);
    }
}

/**
 * @brief Копирует матрицу
 * @param source Указатель на исходную матрицу
 * @return Указатель на копию матрицы или NULL в случае ошибки
 */
Matrix* copy_matrix(const Matrix *source) {
    // Создаем новую матрицу для результата
    Matrix *destination = (Matrix *)malloc(sizeof(Matrix));
    destination->rows = source->rows;
    destination->cols = source->cols;
    destination->data = (int **)malloc(destination->rows * sizeof(int *));
    for (int i = 0; i < destination->rows; i++) {
        destination->data[i] = (int *)malloc(destination->cols * sizeof(int));
    }

    // Копирование данных из source в destination
    for (int i = 0; i < source->rows; i++) {
        for (int j = 0; j < source->cols; j++) {
            destination->data[i][j] = source->data[i][j];
        }
    }

    return destination; // Возвращаем указатель на новую матрицу
}



/**
 * @brief Вычисляет детерминант квадратной матрицы
 * @param Matrix Указатель на квадратную матрицу
 * @return Значение детерминанта матрицы
 */
int determinant_matrix (const Matrix *m) {
    if (m->rows != m->cols) {
        return 0; // Детерминант можно вычислить только для квадратных матриц
    }

    if (m->rows == 1) {
        return m->data[0][0]; // Для 1x1 матрицы детерминант — это сам элемент
    }

    int det = 0;
    for (int i = 0; i < m->cols; i++) {
        Matrix *minor = get_minor(m, 0, i); // Получаем минор для элемента [0][i]
        int sign = (i % 2 == 0) ? 1 : -1; // Чередование знаков
        det += sign * m->data[0][i] * determinant(minor); // Рекурсивно вычисляем детерминант
        free_matrix(minor); // Освобождаем память от временной минорной матрицы
    }

    return det;
}



