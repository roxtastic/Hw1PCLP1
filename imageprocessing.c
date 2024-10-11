#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define magicnum255 255
// TODO(ilinca.tololoi): Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    int *temp = NULL;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            temp = image[i][j];
            image[i][j] = image[i][M - j - 1];
            image[i][M - j - 1] = temp;
        }
    }
    return image;
}

// TODO(ilinca.tololoi): Task 2
int ***rotate_left(int ***image, int N, int M) {
    int i = 0, j = 0;
    int ***image2 = (int ***)malloc(M * sizeof(int **));
    for (i = 0; i < M; i++) {
     image2[i] = (int **)malloc(N * sizeof(int *));
    }
    for (i = 0; i < M; i++) {
     for (j = 0; j < N; j++) {
      image2[i][j] = image[j][M - i - 1];
    }
}
    return image2;
}
// TODO(ilinca.tololoi): Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int i = 0, j = 0, k = 0;
    int ***image2 = (int ***)malloc(h * sizeof(int **));
    for (i = 0; i < h; i++) {
        image2[i] = (int **)malloc(w * sizeof(int *));
        for (j = 0; j < w; j++) {
            image2[i][j] = (int *)malloc(sizeof(int) * 3);
        }
    }
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            for (k = 0; k < 3; k++) {
                if (y + i < N && x + j < M) {
                   image2[i][j][k] = image[y + i][x + j][k];
                } else {
                    image2[i][j][k] = 0;
                }
            }
    }
}
    return image2;
}


// TODO(ilinca.tololoi): Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int new_N = N + 2 * rows;
    int new_M = M + 2 * cols;
    int ***extdimage = (int ***)malloc(new_N * sizeof(int **));
    for (int i = 0; i < new_N; i++) {
        extdimage[i] = (int **)malloc(new_M * sizeof(int *));
        for (int j = 0; j < new_M; j++) {
            extdimage[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            extdimage[i][j][0] = new_R;
            extdimage[i][j][1] = new_G;
            extdimage[i][j][2] = new_B;
        }
    }
    for (int i = rows; i < N + rows; i++) {
        for (int j = cols; j < M + cols; j++) {
            for (int k = 0; k < 3; k++) {
                extdimage[i][j][k] = image[i - rows][j - cols][k];
            }
        }
    }
    return extdimage;
}
// TODO(ilinca.tololoi): Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    int valid_N = (y + N_src <= N_dst) ? N_src : N_dst - y;
    int valid_M = (x + M_src <= M_dst) ? M_src : M_dst - x;
    for (int i = 0; i < valid_N; i++) {
        for (int j = 0; j < valid_M; j++) {
            for (int k = 0; k < 3; k++) {
                image_dst[y + i][x + j][k] = image_src[i][j][k];
            }
        }
    }
    return image_dst;
}
// TODO(ilinca.tololoi): Task 6
int clamp(int value) {
    if (value < 0) {
        return 0;
    } else if (value > magicnum255) {
        return magicnum255;
    } else {
        return value;
    }
}
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int ***result = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        result[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            result[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            float sumR = 0, sumG = 0, sumB = 0;
            for (int fi = 0; fi < filter_size; fi++) {
                for (int fj = 0; fj < filter_size; fj++) {
                    int ni = i + fi - filter_size / 2;
                    int nj = j + fj - filter_size / 2;
                    if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                        sumR += (float)image[ni][nj][0] * filter[fi][fj];
                        sumG += (float)image[ni][nj][1] * filter[fi][fj];
                        sumB += (float)image[ni][nj][2] * filter[fi][fj];
                    }
                }
            }
            result[i][j][0] = clamp((int)sumR);
            result[i][j][1] = clamp((int)sumG);
            result[i][j][2] = clamp((int)sumB);
        }
    }

    return result;
}
