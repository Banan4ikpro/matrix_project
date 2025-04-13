#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "output.h"

/**
 * @file tests_main.c
 * @brief Общие тесты
 */

/**
 * @brief Тестирование файла main.c
 */
void test_expression() {
    Matrix *A = create_matrix(2, 2);
    Matrix *B = create_matrix(2, 2);
    Matrix *C = create_matrix(2, 2);
    Matrix *D = create_matrix(2, 2);

    // Пример: A = I, B = D, C = D -> выражение = C^T
    A->data[0][0] = 1; A->data[1][1] = 1;

    D->data[0][0] = 2; D->data[0][1] = 1;
    D->data[1][0] = 0; D->data[1][1] = 3;

    copy_matrix(D, B);
    copy_matrix(D, C);

    Matrix *CT = transpose_matrix(C);
    Matrix *sum = add_matrix(B, CT);
    Matrix *expr = sub_matrix(sum, D);
    Matrix *result = mul_matrix(A, expr);

    // Проверим конкретный элемент
    assert(result->data[0][0] == CT->data[0][0]);

    // Очистка
    free_matrix(A); free_matrix(B); free_matrix(C); free_matrix(D);
    free_matrix(CT); free_matrix(sum); free_matrix(expr); free_matrix(result);
}

/**
 * @brief Выполнение теста
 */
int main() {
    test_expression();
    printf("✅ tests_main.c: Интеграционные тесты прошли успешно\n");
    return 0;
}

