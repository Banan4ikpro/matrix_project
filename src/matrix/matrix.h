#ifndef MATRIX_H
#define MATRIX_H
#include "../../include/config.h"

/**
 * @file matrix.h
 * @brief Заголовочный файл для matrix
 */
 
/**
 * @brief Структура матрицы
 */
typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

/**
 * @brief Загружает матрицу из текстового файла
 * @param filename Имя файла
 * @return Указатель на загруженную матрицу или NULL в случае ошибки
 */
int load_matrix(const char *filename, Matrix **m); 

/**
 * @brief Транспонирует матрицу
 * @param Matrix Указатель на матрицу
 * @return Указатель на новую транспонированную матрицу, либо NULL в случае ошибки
 */     
Matrix* transpose_matrix(const Matrix *m);              

/**
 * @brief Складывает две матрицы
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае ошибки
 */
int add_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); 

/**
 * @brief Вычитает одну матрицу из другой
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат вычитания, либо NULL в случае ошибки
 */
int subtract_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); 

/**
 * @brief Умножает две матрицы
 * @param m1 Указатель на первую матрицу
 * @param m2 Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат умножения, либо NULL в случае ошибки
 */
int multiply_matrices(const Matrix *m1, const Matrix *m2, Matrix **result); 

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param Matrix Указатель на матрицу
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int save_matrix(const char *filename, const Matrix *m); 
 
/**
 * @brief Освобождает память, выделенную под матрицу
 * @param Matrix Указатель на матрицу
 */
void free_matrix(Matrix *m); 

/**
 * @brief Копирует матрицу
 * @param source Указатель на исходную матрицу
 * @return Указатель на копию матрицы или NULL в случае ошибки
 */
int copy_matrix(const Matrix *source);


/**
 * @brief Вычисляет детерминант квадратной матрицы
 * @param Matrix Указатель на квадратную матрицу
 * @return Значение детерминанта матрицы
 */
int determinant_matrix (const Matrix *m);

#endif

