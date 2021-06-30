// Stefan Rares Constantin - 315CA

#pragma once
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COM_LEN 50
#define TRUE 1

typedef struct pixel {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
} pixel;

void  swap_int(int *n, int *m);
int **alloc_matrix_int(int n, int m);
void  free_matrix_int(int **a, int n);
void  read_matrix_int(FILE *image, int **a, int n, int m, char *tip);
void  print_matrix_int(FILE *file, int **a, int n, int m);
char *alloc_string(int size);
void  load_p12(char *file_name, char *tip, char **next_file);
void  load_p3(char *file_name, char *tip, char **next_file);
void  load(char *command, char **next_file);
void  selectt(char *command, int *x1, int *y1, int *x2, int *y2, int width,
			  int height);
void  selectt_all(int *x1, int *y1, int *x2, int *y2, int width, int height);
void  rotate_r(int **a, int x1, int y1, int x2, int y2, int *ok);
void  rotate_r90(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height);
void  rotate_r180(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				  int *height);
void  rotate_r270(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				  int *height);
void  rotate_l90(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height);
void  rotate_l180(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				  int *height);
void  rotate_l270(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				  int *height);
void  rotate(char *command, int ***a, int *x1, int *y1, int *x2, int *y2,
			 int *width, int *height);
int **rotate_whole(int **a, int *width, int *height, int *ok, int *x1, int *y1,
				   int *x2, int *y2);
pixel **rotate_whole_pixel(pixel **a, int *width, int *height, int *ok, int *x1,
						   int *y1, int *x2, int *y2);
int **crop(int **a, int x1, int y1, int x2, int y2, int *width, int *height);
int if_grayscale(pixel **a, int x1, int y1, int x2, int y2);
void grayscale(pixel **a, int x1, int y1, int x2, int y2);
void sepia(pixel **a, int x1, int y1, int x2, int y2, int max_val);
void save(char *command, char *tip, int max_val, int **a, int width,
		  int height);
void read_matrix_pixel(FILE *image, pixel **a, int n, int m, char *tip);
void print_matrix_pixel(FILE *file, pixel **a, int n, int m);
pixel **alloc_matrix_pixel(int n, int m);
void free_matrix_pixel(pixel **a, int n);
void rotate_pixel(char *command, pixel ***a, int *x1, int *y1, int *x2, int *y2,
				  int *width, int *height);
void rotate_r_pixel(pixel **a, int x1, int y1, int x2, int y2, int *ok);
void rotate_r90_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					  int *width, int *height);
void rotate_r180_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height);
void rotate_r270_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height);
void rotate_l90_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					  int *width, int *height);
void rotate_l180_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height);
void rotate_l270_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height);
pixel **crop_pixel(pixel **a, int x1, int y1, int x2, int y2, int *width,
				   int *height);
void save_pixel(char *command, char *tip, int max_val, pixel **a, int width,
				int height);
