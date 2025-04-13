#ifndef OUTPUT_H
#define OUTPUT_H

#include "matrix.h"

void print_matrix_console(const Matrix *m);
int save_matrix_to_file(const char *filename, const Matrix *m);

#endif

