#ifndef MATRIX_H

#define MATRIX_H
#define MAX_THREADS 8
#include <stddef.h>

typedef struct
{
    int **matrix;
    size_t lines;
    size_t cols;
} Matrix;

typedef struct
{
    const Matrix *m1;
    const Matrix *m2;
    Matrix *res;
    char *printName;
    int startRow;
    int endRow;
} TMatrixArgs;

void initializeMatrix(Matrix *m, size_t lines, size_t cols);
void fillMatrix(const Matrix *m);
void printMatrix(const Matrix *m);
void multiplyMatrices(const Matrix *m1, const Matrix *m2, Matrix *res, char *printName);
void multiplyTMatrices(const Matrix *m1, const Matrix *m2, Matrix *res, char *printName);
void *tMultiply(void *arg);
void freeMatrices(int matrixQty, ...);

#endif // MATRIX_H