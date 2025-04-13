#include <stdio.h>
#include "matrix.h"

int main() {
    Matrix *A, *B, *C, *D;

    if (!load_matrix("data/A.txt", &A) ||
        !load_matrix("data/B.txt", &B) ||
        !load_matrix("data/C.txt", &C) ||
        !load_matrix("data/D.txt", &D)) {
        printf("Ошибка загрузки матриц\n");
        return 1;
    }

    Matrix *CT = transpose_matrix(C);
    Matrix *BplusCT = add_matrix(B, CT);
    Matrix *expr = sub_matrix(BplusCT, D);
    Matrix *result = mul_matrix(A, expr);

    printf("Результат выражения A×(B+C^T−D):\n");
    print_matrix(result);

    // Очистка
    free_matrix(A); free_matrix(B); free_matrix(C); free_matrix(D);
    free_matrix(CT); free_matrix(BplusCT); free_matrix(expr); free_matrix(result);
    return 0;
}

