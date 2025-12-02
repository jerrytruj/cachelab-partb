/*
 * ai_trans.c
 * Generated using ChatGPT (OpenAI GPT-5.1), December 2025
 * Team members:
 * Dajani Green
 * Jerry Trujillo
 */

char ai_trans_desc[] = "AI-Generated Transpose";

void ai_trans(int M, int N, int A[N][M], int B[M][N]) {

    int i, j, k, l;
    int t0, t1, t2, t3, t4, t5, t6, t7;

    if (M == 32 && N == 32) {
        for (i = 0; i < 32; i += 8)
            for (j = 0; j < 32; j += 8)
                for (k = i; k < i + 8; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[j][k] = t0;
                    B[j+1][k] = t1;
                    B[j+2][k] = t2;
                    B[j+3][k] = t3;
                    B[j+4][k] = t4;
                    B[j+5][k] = t5;
                    B[j+6][k] = t6;
                    B[j+7][k] = t7;
                }
    }

    else if (M == 64 && N == 64) {
        for (i = 0; i < 64; i += 8)
            for (j = 0; j < 64; j += 8) {
                
                for (k = i; k < i + 4; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[j][k]     = t0;
                    B[j+1][k]   = t1;
                    B[j+2][k]   = t2;
                    B[j+3][k]   = t3;

                    B[j][k+4]   = t4;
                    B[j+1][k+4] = t5;
                    B[j+2][k+4] = t6;
                    B[j+3][k+4] = t7;
                }

                for (l = j; l < j + 4; l++) {
                    t0 = B[l][i+4];
                    t1 = B[l][i+5];
                    t2 = B[l][i+6];
                    t3 = B[l][i+7];
                    
                    B[l][i+4] = A[i+4][l];
                    B[l][i+5] = A[i+5][l];
                    B[l][i+6] = A[i+6][l];
                    B[l][i+7] = A[i+7][l];
                    
                    B[l+4][i]   = t0;
                    B[l+4][i+1] = t1;
                    B[l+4][i+2] = t2;
                    B[l+4][i+3] = t3;
                }

                for (k = i + 4; k < i + 8; k++)
                    for (l = j + 4; l < j + 8; l++)
                        B[l][k] = A[k][l];
            }
    }

    else {
        for (i = 0; i < N; i += 17)
            for (j = 0; j < M; j += 17)
                for (k = i; k < N && k < i + 17; k++)
                    for (l = j; l < M && l < j + 17; l++)
                        B[l][k] = A[k][l];
    }
}
