#include <stdio.h>
#include "output.h"

// Вывод матрицы в консоль
void print_matrix_console(const Matrix *m) {
    if (!m) {
        printf("Матрица пуста\n");
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++)
            printf("%8.2lf ", m->data[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Сохранение матрицы в файл
int save_matrix_to_file(const char *filename, const Matrix *m) {
    FILE *f = fopen(filename, "w");
    if (!f) return 0;

    fprintf(f, "%d %d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++)
            fprintf(f, "%.10lf ", m->data[i][j]);
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

