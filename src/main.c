#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file main.c
 * @brief Основной файл с демонстрацией работы библиотеки
 */

/**
 * @brief Выполняет вычисленнее матричного выражения
 * @return Вычисленное матричное выражение в виде текстового файла
 */
int main() {
  Matrix *A = NULL, *B = NULL, *C = NULL, *D = NULL;
  Matrix *C_T = NULL, *B_plus_CT = NULL, *B_plus_CT_minus_D = NULL,
         *Result = NULL;

  // Загрузка матриц
  if (load_matrix("src/matrix/A.txt", &A) != 0 ||
      load_matrix("src/matrix/B.txt", &B) != 0 ||
      load_matrix("src/matrix/C.txt", &C) != 0 ||
      load_matrix("src/matrix/D.txt", &D) != 0) {
    fprintf(stderr, "Ошибка при загрузке матриц.\n");
    return 1;
  }

  // Транспонирование C
  C_T = transpose_matrix(C);
  // Сложение B + C^T
  if (add_matrices(B, C_T, &B_plus_CT) != 0) {
    printf("Ошибка при сложении B и C^T\n");
    return 1;
  }

  // Вычитание B + C^T - D
  if (subtract_matrices(B_plus_CT, D, &B_plus_CT_minus_D) != 0) {
    fprintf(stderr, "Ошибка при вычитании D.\n");
    return 1;
  }

  // Умножение A * (B + C^T - D)
  if (multiply_matrices(A, B_plus_CT_minus_D, &Result) != 0) {
    fprintf(stderr, "Ошибка при умножении матриц.\n");
    return 1;
  }

  // Сохранение результата
  if (save_matrix("src/output/result.txt", Result) != 0) {
    fprintf(stderr, "Ошибка при сохранении результата.\n");
    return 1;
  }

  free_matrix(A);
  free_matrix(B);
  free_matrix(C);
  free_matrix(D);
  free_matrix(C_T);
  free_matrix(B_plus_CT);
  free_matrix(B_plus_CT_minus_D);
  free_matrix(Result);

  return 0;
}
