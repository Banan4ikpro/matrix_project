#include <stdio.h>
#include <assert.h>
#include "matrix.h"

/**
 * @file tests_matrix.c
 * @brief Набор тестов для библиотеки matrix
 */

/**
 * @brief Тестирование добавления матриц
 */
void test_add_matrix() {
    Matrix *a = create_matrix(2, 2);
    Matrix *b = create_matrix(2, 2);

    a->data[0][0] = 1; a->data[0][1] = 2;
    a->data[1][0] = 3; a->data[1][1] = 4;

    b->data[0][0] = 5; b->data[0][1] = 6;
    b->data[1][0] = 7; b->data[1][1] = 8;

    Matrix *sum = add_matrix(a, b);
    assert(sum->data[0][0] == 6);
    assert(sum->data[1][1] == 12);

    free_matrix(a);
    free_matrix(b);
    free_matrix(sum);
}

/**
 * @brief Тестирование нахождения детерминанта
 */
void test_determinant() {
    Matrix *m = create_matrix(2, 2);
    m->data[0][0] = 1; m->data[0][1] = 2;
    m->data[1][0] = 3; m->data[1][1] = 4;

    elem_t det = determinant(m);
    assert(det == -2);

    free_matrix(m);
}

/**
 * @brief Выполнение теста
 */
int main() {
    test_add_matrix();
    test_determinant();
    printf("✅ tests_matrix.c: Все тесты прошли успешно\n");
    return 0;
}

