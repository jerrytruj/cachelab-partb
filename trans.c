/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /* Loop indices */
    int i, j, k, l;
    /* Temporaires to hold one row or part of a row */
    int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

    /* Case 1: 32 x 32 Matrix */
    if (M == 32 && N == 32)
    {
        /* iterate over the top-left corner of each 8x8 block */
        for (i = 0; i < 32; i += 8)
        {
            for (j = 0; j < 32; j += 8)
            {
                /* Non diagnol 8x8 block */
                if (i != j)
                {
                    /* For each row k inside this 8x8 block */
                    for (k = i; k < i + 8; k++)
                    {
                        /* Load 8 elements from row k of A into temp variables */
                        temp0 = A[k][j];
                        temp1 = A[k][j + 1];
                        temp2 = A[k][j + 2];
                        temp3 = A[k][j + 3];
                        temp4 = A[k][j + 4];
                        temp5 = A[k][j + 5];
                        temp6 = A[k][j + 6];
                        temp7 = A[k][j + 7];

                        /* Write them into B as a column slice */
                        B[j][k] = temp0;
                        B[j + 1][k] = temp1;
                        B[j + 2][k] = temp2;
                        B[j + 3][k] = temp3;
                        B[j + 4][k] = temp4;
                        B[j + 5][k] = temp5;
                        B[j + 6][k] = temp6;
                        B[j + 7][k] = temp7;
                    }
                }
                else
                {
                    /* Diagnol 8x8 block */
                    for (k = i; k < i + 8; k++)
                    {
                        for (l = j; l < j + 8; l++)
                        {
                            /* Non-diagonal element */
                            if (k != l)
                            {
                                /* Directly transpose */
                                B[l][k] = A[k][l];
                            }
                            else
                            {
                                /* For diagnol element, store it in temp and delay writing to B*/
                                temp0 = A[k][l];
                            }
                        }
                        /* After finishing row k, write the saved diagnol element */
                        B[k][k] = temp0;
                    }
                }
            }
        }
    }
    /* Case 2: 64x64 Matrix*/
    else if (M == 64 && N == 64)
    {
        /* Process the 64x64 amtrix using 4x4 blocks */
        for (i = 0; i < 64; i += 4)
        {

            for (j = 0; j < 64; j += 4)
            {
                /* Each row k inside 4x4 block */
                for (k = i; k < i + 4; k++)
                {
                    /* Load 4 elements from row k of A into temp variables */
                    temp0 = A[k][j];
                    temp1 = A[k][j + 1];
                    temp2 = A[k][j + 2];
                    temp3 = A[k][j + 3];

                    /* Store them in B as a column slice */
                    B[j][k] = temp0;
                    B[j + 1][k] = temp1;
                    B[j + 2][k] = temp2;
                    B[j + 3][k] = temp3;
                }
            }
        }
    }
    /* Case 3: 61x67 Matrix*/
    else
    {
        /* Use 16x16 blocks */
        for (i = 0; i < N; i += 16)
        {

            for (j = 0; j < M; j += 16)
            {
                /* Iterate rows withing the block without going past N */
                for (k = i; k < N && k < i + 16; k++)
                {
                    /* Iterate columns within the block without going past M */
                    for (l = j; l < M && l < j + 16; l++)
                    {
                        /* transpose */
                        B[l][k] = A[k][l];
                    }
                }
            }
        }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
