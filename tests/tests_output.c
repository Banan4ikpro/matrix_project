#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "output.h"

/**
 * @file tests_output.c
 * @brief Набор тестов для библиотеки output
 */

/**
 * @brief Тестирование функции вывода матриц в консоль
 */
void test_print_matrix_console() {
    // Создаём тестовую матрицу размером 2x3
    Matrix test_matrix;
    test_matrix.rows = 2;
    test_matrix.cols = 3;
    test_matrix.data = (int **)malloc(test_matrix.rows * sizeof(int *));
    for (int i = 0; i < test_matrix.rows; i++) {
        test_matrix.data[i] = (int *)malloc(test_matrix.cols * sizeof(int));
    }

    // Заполняем матрицу тестовыми данными
    test_matrix.data[0][0] = 1;
    test_matrix.data[0][1] = 2;
    test_matrix.data[0][2] = 3;
    test_matrix.data[1][0] = 4;
    test_matrix.data[1][1] = 5;
    test_matrix.data[1][2] = 6;

    // Ожидаемый результат с учётом PRINT_PRECISION
    const char *expected_output = "   1.00    2.00    3.00 \n   4.00    5.00    6.00 \n\n";

    // Перенаправляем вывод в строку
    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Ошибка при открытии файла");
        return;
    }
    FILE *original_stdout = stdout;  // Сохраняем оригинальный стандартный вывод
    stdout = output_file;  // Перенаправляем stdout в файл

    // Вызов функции, которая должна вывести матрицу
    print_matrix_console(&test_matrix);

    // Восстанавливаем стандартный вывод
    fflush(stdout);
    stdout = original_stdout;

    // Открываем файл и считываем его содержимое
    fseek(output_file, 0, SEEK_SET);
    char output_content[100];
    fgets(output_content, sizeof(output_content), output_file);

    // Сравниваем содержимое файла с ожидаемым выводом
    if (strcmp(output_content, expected_output) == 0) {
        printf("Тест passed: Матрица выведена корректно.\n");
    } else {
        printf("Тест failed: Ожидаемый вывод не совпадает с фактическим.\n");
        printf("Ожидалось:\n%s\n", expected_output);
        printf("Получено:\n%s\n", output_content);
    }

    // Освобождаем память и закрываем файл
    fclose(output_file);
    for (int i = 0; i < test_matrix.rows; i++) {
        free(test_matrix.data[i]);
    }
    free(test_matrix.data);
}

/**
 * @brief Выполнение теста
 */
int main() {
    test_file_output();
    printf("✅ tests_output.c: Все тесты прошли успешно\n");
    return 0;
}

