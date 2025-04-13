#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "output.h"

void test_file_output() {
    Matrix *m = create_matrix(2, 2);
    m->data[0][0] = 1.1;
    m->data[1][1] = 2.2;

    int ok = save_matrix_to_file("test_output.txt", m);
    assert(ok == 1);

    FILE *f = fopen("test_output.txt", "r");
    assert(f != NULL);

    int rows, cols;
    elem_t val;
    fscanf(f, "%d %d", &rows, &cols);
    assert(rows == 2 && cols == 2);

    fscanf(f, ELEM_FMT, &val);
    assert(val == 1.1);

    fclose(f);
    free_matrix(m);
}

int main() {
    test_file_output();
    printf("✅ tests_output.c: Все тесты прошли успешно\n");
    return 0;
}

