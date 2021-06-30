// Stefan Rares Constantin - 315CA

#include "functions.h"

//roteste matricea in sensul acelor de ceasornic
void rotate_r(int **a, int x1, int y1, int x2, int y2, int *ok)
{
	*ok = 1;
	int width, height;
	width = x2 - x1;
	height = y2 - y1;
	if (width != height) { //daca selectia curenta nu e patrata
		*ok = 0;
		printf("The selection must be square\n");
		return;
	}

	for (int i = 0; i < width / 2; i++) {
		for (int j = i; j < width - i - 1; j++) {
			int aux = a[y1 + i][x1 + j];
			a[y1 + i][x1 + j] = a[y1 + width - 1 - j][x1 + i];
			a[y1 + width - 1 - j][x1 + i] =
			a[y1 + width - 1 - i][x1 + width - 1 - j];
			a[y1 + width - 1 - i][x1 + width - 1 - j] =
			a[y1 + j][x1 + width - 1 - i];
			a[y1 + j][x1 + width - 1 - i] = aux;
		}
	}
}

void rotate_r_pixel(pixel **a, int x1, int y1, int x2, int y2, int *ok)
{
	*ok = 1;
	int width, height;
	width = x2 - x1;
	height = y2 - y1;
	if (width != height) {
		*ok = 0;
		printf("The selection must be square\n");
		return;
	}

	for (int i = 0; i < width / 2; i++) {
		for (int j = i; j < width - i - 1; j++) {
			pixel aux = a[y1 + i][x1 + j];
			a[y1 + i][x1 + j] = a[y1 + width - 1 - j][x1 + i];
			a[y1 + width - 1 - j][x1 + i] =
			a[y1 + width - 1 - i][x1 + width - 1 - j];
			a[y1 + width - 1 - i][x1 + width - 1 - j] =
			a[y1 + j][x1 + width - 1 - i];
			a[y1 + j][x1 + width - 1 - i] = aux;
		}
	}
}

//roteste intreaga imagine, chiar daca nu este patrata
int **rotate_whole(int **a, int *width, int *height, int *ok, int *x1, int *y1,
				   int *x2, int *y2)
{
	*ok = 1;
	int **new = alloc_matrix_int(*width, *height);
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++)
			new[i][j] = a[*height - 1 - j][i];
	}
	free_matrix_int(a, *height);
	swap_int(height, width);
	*x1 = 0;
	*y1 = 0;
	*x2 = *width;
	*y2 = *height;
	return new;
}

pixel **rotate_whole_pixel(pixel **a, int *width, int *height, int *ok, int *x1,
						   int *y1, int *x2, int *y2)
{
	*ok = 1;
	pixel **new = alloc_matrix_pixel(*width, *height);
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++)
			new[i][j] = a[*height - 1 - j][i];
	}
	free_matrix_pixel(a, *height);
	swap_int(height, width);
	*x1 = 0;
	*y1 = 0;
	*x2 = *width;
	*y2 = *height;
	return new;
}

//am facut functii individuale pt fiecare operatie pt ca au outputuri diferite
void rotate_r90(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height)
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	else
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	if (ok)
		printf("Rotated 90\n");
}

void rotate_r90_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					  int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height)
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	else
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	if (ok)
		printf("Rotated 90\n");
}

void rotate_r180(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated 180\n");
}

void rotate_r180_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated 180\n");
}

void rotate_r270(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated 270\n");
}

void rotate_r270_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated 270\n");
}

void rotate_l90(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated -90\n");
}

void rotate_l90_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					  int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated -90\n");
}

void rotate_l180(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated -180\n");
}

void rotate_l180_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	} else {
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	}
	if (ok)
		printf("Rotated -180\n");
}

void rotate_l270(int ***a, int *x1, int *y1, int *x2, int *y2, int *width,
				 int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height)
		*a = rotate_whole(*a, width, height, &ok, x1, y1, x2, y2);
	else
		rotate_r(*a, *x1, *y1, *x2, *y2, &ok);
	if (ok)
		printf("Rotated -270\n");
}

void rotate_l270_pixel(pixel ***a, int *x1, int *y1, int *x2, int *y2,
					   int *width, int *height)
{
	int ok;
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height)
		*a = rotate_whole_pixel(*a, width, height, &ok, x1, y1, x2, y2);
	else
		rotate_r_pixel(*a, *x1, *y1, *x2, *y2, &ok);
	if (ok)
		printf("Rotated -270\n");
}

//creierul operatiilor de rotire, decide ce fel de rotatie trb executata -int
void rotate(char *command, int ***a, int *x1, int *y1, int *x2, int *y2,
			int *width, int *height)
{
	char *str_angle = strtok(command, " ");
	str_angle = strtok(NULL, " ");
	if (!str_angle) {
		printf("Invalid parameters\n");
		return;
	}
	int angle = atoi(str_angle);
	if (angle == 90)
		rotate_r90(a, x1, y1, x2, y2, width, height);
	else if (angle == 180)
		rotate_r180(a, x1, y1, x2, y2, width, height);
	else if (angle == 270)
		rotate_r270(a, x1, y1, x2, y2, width, height);
	else if (angle == -90)
		rotate_l90(a, x1, y1, x2, y2, width, height);
	else if (angle == -180)
		rotate_l180(a, x1, y1, x2, y2, width, height);
	else if (angle == -270)
		rotate_l270(a, x1, y1, x2, y2, width, height);
	else if (angle == 0)
		printf("Rotated 0\n");
	else if (angle == 360)
		printf("Rotated 360\n");
	else if (angle == -360)
		printf("Rotated -360\n");
	else
		printf("Unsupported rotation angle\n");
}

//creierul operatiilor de rotire, decide ce fel de rotatie trb executata -pixel
void rotate_pixel(char *command, pixel ***a, int *x1, int *y1, int *x2, int *y2,
				  int *width, int *height)
{
	char *str_angle = strtok(command, " ");
	str_angle = strtok(NULL, " ");
	if (!str_angle) {
		printf("Invalid parameters\n");
		return;
	}
	int angle = atoi(str_angle);
	if (angle == 90)
		rotate_r90_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == 180)
		rotate_r180_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == 270)
		rotate_r270_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == -90)
		rotate_l90_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == -180)
		rotate_l180_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == -270)
		rotate_l270_pixel(a, x1, y1, x2, y2, width, height);
	else if (angle == 0)
		printf("Rotated 0\n");
	else if (angle == 360)
		printf("Rotated 360\n");
	else if (angle == -360)
		printf("Rotated -360\n");
	else
		printf("Unsupported rotation angle\n");
}
