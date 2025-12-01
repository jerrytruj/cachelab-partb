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