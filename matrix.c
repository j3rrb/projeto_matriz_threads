#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>

#include "matrix.h"

void initializeMatrix(Matrix *m, size_t lines, size_t cols)
{
    m->lines = lines;
    m->cols = cols;

    m->matrix = (int **)calloc(lines, sizeof(int *));

    if (m->matrix == NULL)
    {
        fprintf(stderr, "Matrix lines allocation failed!");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lines; i++)
    {
        m->matrix[i] = (int *)calloc(cols, sizeof(int));

        if (m->matrix[i] == NULL)
        {
            fprintf(stderr, "Matrix cols allocation failed!");
            exit(EXIT_FAILURE);
        }
    }
}

void fillMatrix(const Matrix *m)
{
    srand(time(NULL));

    for (size_t i = 0; i < m->lines; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            m->matrix[i][j] = (rand() % 19) - 9;
        }
    }
}

void printMatrix(const Matrix *m)
{
    for (size_t i = 0; i < m->lines; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            printf("%3d ", m->matrix[i][j]);
        }

        printf("\n");
    }
}

void *tMultiply(void *arg)
{
    TMatrixArgs *args = (TMatrixArgs *)arg;

    for (int i = args->startRow; i < args->endRow; i++)
    {
        for (int j = 0; j < args->res->cols; j++)
        {
            args->res->matrix[i][j] = 0;
            for (int k = 0; k < args->m1->cols; k++)
            {
                args->res->matrix[i][j] += args->m1->matrix[i][k] * args->m2->matrix[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

void multiplyTMatrices(const Matrix *m1, const Matrix *m2, Matrix *res, char *printName)
{
    if (m1->cols != m2->lines)
    {
        fprintf(stderr, "Incompatible dimensions\n");
        exit(EXIT_FAILURE);
    }

    initializeMatrix(res, m1->lines, m2->cols);

    pthread_t threads[MAX_THREADS];
    TMatrixArgs args[MAX_THREADS];

    int chunkSize = res->lines / MAX_THREADS;
    int startRow = 0;
    int endRow = 0;

    {
        clock_t start = clock();
        for (int i = 0; i < MAX_THREADS; i++)
        {
            endRow = startRow + chunkSize;
            if (i == MAX_THREADS - 1)
            {
                endRow = res->lines;
            }

            args[i].m1 = m1;
            args[i].m2 = m2;
            args[i].res = res;
            args[i].printName = printName;
            args[i].startRow = startRow;
            args[i].endRow = endRow;

            pthread_create(&threads[i], NULL, tMultiply, &args[i]);

            startRow = endRow;
        }

        for (int i = 0; i < MAX_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }
        clock_t end = clock();

        printf("Time taken for %s: %.6f secs\n", printName, (double)(end - start) / CLOCKS_PER_SEC);
    }
}

void multiplyMatrices(const Matrix *m1, const Matrix *m2, Matrix *res, char *printName)
{
    if (m1->cols != m2->lines)
    {
        fprintf(stderr, "Incompatible dimensions\n");
        exit(EXIT_FAILURE);
    }

    initializeMatrix(res, m1->lines, m2->cols);

    {
        clock_t start = clock();
        for (size_t i = 0; i < res->lines; i++)
        {
            for (size_t j = 0; j < res->cols; j++)
            {
                res->matrix[i][j] = 0;
                for (size_t k = 0; k < m1->cols; k++)
                {
                    res->matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
                }
            }
        }
        clock_t end = clock();

        printf("Time taken for %s: %.6f secs\n", printName, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
}

void freeMatrices(int matrixQty, ...)
{
    va_list args;
    va_start(args, matrixQty);

    for (int i = 0; i < matrixQty; i++)
    {
        Matrix *m = va_arg(args, Matrix *);
        for (size_t j = 0; j < m->lines; j++)
        {
            free(m->matrix[j]);
        }
        free(m->matrix);
        m->matrix = NULL;
        m->lines = 0;
        m->cols = 0;
    }

    va_end(args);
}
