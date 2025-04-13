#include <stdio.h>
#include "output.h"
#include "config.h" 

/**
 * @file output.c
 * @brief  Функции вывода матриц в консоль
 */

/**
 * @brief Выводит матрицу в консоль
 * @param Matrix Указатель на матрицу
 */
void print_matrix_console(const Matrix *m) {
    if (!m) {
        printf("Матрица пуста\n");
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++)
            printf("%8.*d ", PRINT_PRECISION, m->data[i][j]);  // Используем PRINT_PRECISION
        printf("\n");
    }
    printf("\n");
}


