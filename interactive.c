#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "imageprocessing.h"

#define MAX_COMMAND_LENGTH 3
#define MAX_FILTER_SIZE 10
#define Magic_number15 15
#define Magic_number100 100
#define Magic_number250 250
#define Magic_number50 50

int main() {
  int ****images = (int ****)malloc(Magic_number15 * sizeof(int ***));
  float ***filters = (float ***)malloc(Magic_number15 * sizeof(float **));
  int images_count = 0, filter_count = 0;
  int N[Magic_number15], M[Magic_number15], FDIM[Magic_number15];

  while (1) {
    char command[Magic_number250];
    scanf("%s", command);
    if (strcmp(command, "e") == 0) {
      break;
    }
    if (strcmp(command, "l") == 0) {
      char n[Magic_number15], m[Magic_number15], path[Magic_number100];
      scanf("%s %s %s", n, m, path);
      N[images_count] = atoi(n);
      M[images_count] = atoi(m);

      int ***img = (int ***)malloc(N[images_count] * sizeof(int **));
      for (int i = 0; i < N[images_count]; i++) {
        img[i] = (int **)malloc(M[images_count] * sizeof(int *));
        for (int j = 0; j < M[images_count]; j++) {
          img[i][j] = (int *)malloc(MAX_COMMAND_LENGTH * sizeof(int));
        }
      }

      read_from_bmp(img, N[images_count], M[images_count], path);

      images[images_count] = img;
      images_count++;
    }
    if (strcmp(command, "s") == 0) {
      char s[Magic_number15], path[Magic_number100];
      scanf("%s%s", s, path);
      int index = atoi(s);

      write_to_bmp(images[index], N[index], M[index], path);
    }
    if (strcmp(command, "ah") == 0) {
      char s[Magic_number15];
      scanf("%s", s);
      int index = atoi(s);
      images[index] = flip_horizontal(images[index], N[index], M[index]);
    }
    if (strcmp(command, "ar") == 0) {
      char s[Magic_number15];
      scanf("%s", s);
      int index = atoi(s);
      images[index] = rotate_left(images[index], N[index], M[index]);
      int temp = N[index];
      N[index] = M[index];
      M[index] = temp;
    }
    if (strcmp(command, "ac") == 0) {
      char a1[Magic_number15], a2[Magic_number15], a3[Magic_number15],
          a4[Magic_number15], a5[Magic_number15];
      scanf("%s%s%s%s%s", a1, a2, a3, a4, a5);
      int index = atoi(a1);
      int x = atoi(a2);
      int y = atoi(a3);
      int w = atoi(a4);
      int h = atoi(a5);
      images[index] = crop(images[index], N[index], M[index], x, y, h, w);
      N[index] = h;
      M[index] = w;
    }
    if (strcmp(command, "ae") == 0) {
      char a1[Magic_number15], a2[Magic_number15], a3[Magic_number15],
          a4[Magic_number15], a5[Magic_number15], a6[Magic_number15];
      scanf("%s%s%s%s%s%s", a1, a2, a3, a4, a5, a6);
      int index = atoi(a1);
      int rows = atoi(a2);
      int cols = atoi(a3);
      int R = atoi(a4);
      int G = atoi(a5);
      int B = atoi(a6);
      images[index] =
          extend(images[index], N[index], M[index], rows, cols, R, G, B);
      N[index] = N[index] + 2 * rows;
      M[index] = M[index] + 2 * cols;
    }
    if (strcmp(command, "ap") == 0) {
      char a1[Magic_number15];
      scanf("%s", a1);
      int index_dst = atoi(a1);
      scanf("%s", a1);
      int index_src = atoi(a1);
      scanf("%s", a1);
      int x = atoi(a1);
      scanf("%s", a1);
      int y = atoi(a1);
      images[index_dst] =
          paste(images[index_dst], N[index_dst], M[index_dst],
                images[index_src], N[index_src], M[index_src], x, y);
    }
    if (strcmp(command, "cf") == 0) {
      char s[Magic_number15];
      scanf("%s", s);
      int size = atoi(s);

      float **fil = (float **)malloc(size * sizeof(float *));
      for (int i = 0; i < size; i++) {
        fil[i] = (float *)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++) {
          char nr[Magic_number50];
          scanf("%s", nr);
          fil[i][j] = (float)atof(nr);
        }
      }

      filters[filter_count] = fil;
      FDIM[filter_count] = size;
      filter_count++;
    }
    if (strcmp(command, "af") == 0) {
      char a1[Magic_number15], a2[Magic_number15];
      scanf("%s%s", a1, a2);
      int index_img = atoi(a1);
      int index_filter = atoi(a2);
      images[index_img] =
          apply_filter(images[index_img], N[index_img], M[index_img],
                       filters[index_filter], FDIM[index_filter]);
    }
    if (strcmp(command, "df") == 0) {
      char s[Magic_number15];
      scanf("%s", s);
      int index_filter = atoi(s);

      for (int i = 0; i < FDIM[index_filter]; i++) {
        free(filters[index_filter][i]);
      }
      free(filters[index_filter]);

      for (int i = index_filter; i < filter_count; i++) {
        filters[i] = filters[i + 1];
        FDIM[i] = FDIM[i + 1];
      }

      filter_count--;
    }
    if (strcmp(command, "di") == 0) {
      char s[Magic_number15];
      scanf("%s", s);
      int index_img = atoi(s);

      for (int i = 0; i < N[index_img]; i++) {
        for (int j = 0; j < M[index_img]; j++) {
          free(images[index_img][i][j]);
        }
        free(images[index_img][i]);
      }
      free(images[index_img]);

      for (int i = index_img; i < images_count; i++) {
        images[i] = images[i + 1];
        N[i] = N[i + 1];
        M[i] = M[i + 1];
      }

      images_count--;
    }
  }

  for (int img = 0; img < images_count; img++) {
    for (int i = 0; i < N[img]; i++) {
      for (int j = 0; j < M[img]; j++) {
        free(images[img][i][j]);
      }
      free(images[img][i]);
    }
    free(images[img]);
  }
  free(images);

  for (int fil = 0; fil < filter_count; fil++) {
    for (int i = 0; i < FDIM[fil]; i++) {
      free(filters[fil][i]);
    }
    free(filters[fil]);
  }
  free(filters);

  return 0;
}
