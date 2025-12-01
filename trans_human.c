char transpose_submit_desc[] = "Transpose submission";

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, l;
    int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

    if (M == 32 && N == 32)
    {
        /* code */
        for (i = 0; i < 32; i += 8)
        {
            for (j = 0; j < 32; j += 8)
            {
                /* code */
                if (i != j)
                {
                    for (k = i; k < i + 8; k++)
                    {
                        /* code */
                        temp0 = A[k][j];
                        temp1 = A[k][j + 1];
                        temp2 = A[k][j + 2];
                        temp3 = A[k][j + 3];
                        temp4 = A[k][j + 4];
                        temp5 = A[k][j + 5];
                        temp6 = A[k][j + 6];
                        temp7 = A[k][j + 7];

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
                    for (k = i; k < i + 8; k++)
                    {
                        for (l = j; l < j + 8; l++)
                        {
                            if (k != l)
                            {
                                /* code */
                                B[l][k] = A[k][l];
                            }
                            else
                            {
                                temp0 = A[k][l];
                            }
                        }
                        B[k][k] = temp0;
                    }
                }
            }
        }
    }
    else if (M == 64 && N == 64)
    {
        for (i = 0; i < 64; i += 4)
        {
            /* code */
            for (j = 0; j < 64; j += 4)
            {
                /* code */
                for (k = i; k < i + 4; k++)
                {
                    /* code */
                    temp0 = A[k][j];
                    temp1 = A[k][j + 1];
                    temp2 = A[k][j + 2];
                    temp3 = A[k][j + 3];

                    B[j][k] = temp0;
                    B[j + 1][k] = temp1;
                    B[j + 2][k] = temp2;
                    B[j + 3][k] = temp3;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < N; i += 16)
        {
            /* code */
            for (j = 0; j < M; j += 16)
            {
                /* code */
                for (k = i; k < N && k < i + 16; k++)
                {
                    /* code */
                    for (l = j; l < M && l < j + 16; l++)
                    {
                        /* code */
                        B[l][k] = A[k][l];
                    }
                }
            }
        }
    }
}