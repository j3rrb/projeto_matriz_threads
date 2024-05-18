#include <stdio.h>

#include "matrix.h"

int main()
{
    Matrix A, Z, Y;
    Matrix B, W, X;
    Matrix C, U, V;
    Matrix D, S, T;
    Matrix E, Q, R;

    {
        initializeMatrix(&Z, 5, 5);
        fillMatrix(&Z);

        initializeMatrix(&Y, 5, 5);
        fillMatrix(&Y);

        multiplyTMatrices(&Z, &Y, &A, "Matrix A (ZxY) Thread");
        multiplyMatrices(&Z, &Y, &A, "Matrix A (ZxY)");

        printMatrix(&A);
        printf("\n");
    }

    {
        initializeMatrix(&W, 100, 100);
        fillMatrix(&W);

        initializeMatrix(&X, 100, 100);
        fillMatrix(&X);

        multiplyTMatrices(&W, &X, &B, "Matrix B (XxB) Thread");
        multiplyMatrices(&W, &X, &B, "Matrix B (XxB)");
        printf("\n");
    }

    {
        initializeMatrix(&U, 1000, 1000);
        fillMatrix(&U);

        initializeMatrix(&V, 1000, 1000);
        fillMatrix(&V);

        multiplyTMatrices(&U, &V, &C, "Matrix C (UxV) Thread");
        multiplyMatrices(&U, &V, &C, "Matrix C (UxV)");
        printf("\n");
    }

    {
        initializeMatrix(&S, 2000, 2000);
        fillMatrix(&S);

        initializeMatrix(&T, 2000, 2000);
        fillMatrix(&T);

        multiplyTMatrices(&S, &T, &D, "Matrix D (SxT) Thread");
        multiplyMatrices(&S, &T, &D, "Matrix D (SxT)");
        printf("\n");
    }

    {
        initializeMatrix(&Q, 3000, 3000);
        fillMatrix(&Q);

        initializeMatrix(&R, 3000, 3000);
        fillMatrix(&R);

        multiplyTMatrices(&Q, &R, &E, "Matrix E (QxR) Thread");
        multiplyMatrices(&Q, &R, &E, "Matrix E (QxR)");
        printf("\n");
    }

    freeMatrices(15, &A, &Z, &Y, &B, &W, &X, &C, &U, &V, &D, &S, &T, &E, &Q, &R);

    return 0;
}
