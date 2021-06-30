// Stefan Rares Constantin - 315CA

#include "functions.h"

void swap_int(int *n, int *m)
{
	int aux;
	aux = *n;
	*n = *m;
	*m = aux;
}

pixel **alloc_matrix_pixel(int n, int m)
{
	pixel **a = (pixel **)malloc(n * sizeof(pixel *));
	if (!a)
		exit(-1);
	for (int i = 0; i < n; i++) {
		a[i] = (pixel *)malloc(m * sizeof(pixel));
		if (!a[i]) {
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			exit(-1);
		}
	}
	return a;
}

void read_matrix_pixel(FILE *image, pixel **a, int n, int m, char *tip)
{
	if (!strcmp(tip, "P3")) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				fscanf(image, "%u%u%u", &a[i][j].red, &a[i][j].green,
				       &a[i][j].blue);
	} else {
		unsigned char aux;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				fread(&aux, sizeof(unsigned char), 1, image);
				a[i][j].red = (int)aux;
				fread(&aux, sizeof(unsigned char), 1, image);
				a[i][j].green = (int)aux;
				fread(&aux, sizeof(unsigned char), 1, image);
				a[i][j].blue = (int)aux;
			}
	}
}

void print_matrix_pixel(FILE *file, pixel **a, int n, int m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			fprintf(file, "%u %u %u ", a[i][j].red, a[i][j].green,
					a[i][j].blue);
		fprintf(file, "\n");
	}
}

void free_matrix_pixel(pixel **a, int n)
{
	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
}

int **alloc_matrix_int(int n, int m)
{
	int **a = (int **)malloc(n * sizeof(int *));
	if (!a)
		exit(-1);
	for (int i = 0; i < n; i++) {
		a[i] = (int *)malloc(m * sizeof(int));
		if (!a[i]) {
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			exit(-1);
		}
	}
	return a;
}

void free_matrix_int(int **a, int n)
{
	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
}

void read_matrix_int(FILE *image, int **a, int n, int m, char *tip)
{
	if (!strcmp(tip, "P1") || !strcmp(tip, "P2")) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				fscanf(image, "%d", &a[i][j]);
		}
	} else {
		unsigned char aux;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				fread(&aux, sizeof(unsigned char), 1, image);
				a[i][j] = (int)aux;
			}
		}
	}
}

void print_matrix_int(FILE *file, int **a, int n, int m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			fprintf(file, "%d ", a[i][j]);
		fprintf(file, "\n");
	}
}

char *alloc_string(int size)
{
	char *string = (char *)malloc((size + 1) * sizeof(char));
	if (!string)
		exit(-1);
	return string;
}

void load_p12(char *file_name, char *tip, char **next_file)
{
	FILE *image = fopen(file_name, "r");
	if (!image) { //verific daca exista fisierul
		printf("Could not open %s\n", file_name);
		return;
	}
	int width, height, **img_matrix, max_val = 0, pos; //datele matricei
	int x1, y1, x2, y2; //coordonatele punctelor care marcheaza zona de lucru
	fseek(image, 2, SEEK_SET);
	fscanf(image, "%d%d%d", &width, &height, &max_val);
	pos = (int)ftell(image);
	fclose(image);
	x1 = 0; y1 = 0; x2 = width; y2 = height;        //valorile default
	img_matrix = alloc_matrix_int(height, width);   //declar matricea imaginii
	if (!strcmp(tip, "P4") || !strcmp(tip, "P5")) { //deschid fisierul
		image = fopen(file_name, "rb");
		fseek(image, pos + 1, SEEK_SET);
	} else {
		image = fopen(file_name, "r");
		fseek(image, pos, SEEK_SET);
	}

	read_matrix_int(image, img_matrix, height, width, tip); //citesc matricea
	printf("Loaded %s\n", file_name); //daca s-a ajuns aici, s-a incarcat bine

	char *command = alloc_string(COM_LEN); //comanda introdusa
	fgets(command, COM_LEN, stdin);
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = 0;
	char *com_copy = alloc_string(COM_LEN); //copie pt strtok
	strcpy(com_copy, command);

	while (TRUE) { //citesc si execut instruciunile introduse
		char *type_com = strtok(com_copy, " "); //TIPUL instructiunii
		if (!strcmp(type_com, "ROTATE")) {
			rotate(command, &img_matrix, &x1, &y1, &x2, &y2, &width, &height);
		} else if (!strcmp(type_com, "SELECT")) {
			type_com = strtok(NULL, " ");
			if (!strcmp(type_com, "ALL")) {
				selectt_all(&x1, &y1, &x2, &y2, width, height);
				printf("Selected ALL\n");
			} else {
				selectt(command, &x1, &y1, &x2, &y2, width, height);
			}
		} else if (!strcmp(type_com, "PRINT")) {
			print_matrix_int(stdout, img_matrix, height, width);
		} else if (!strcmp(type_com, "LOAD")) {
			type_com = strtok(NULL, " ");
			strcpy(*next_file, type_com);
			break;
		} else if (!strcmp(type_com, "EXIT")) {
			strcpy(*next_file, "\0");
			break;
		} else if (!strcmp(type_com, "CROP")) {
			img_matrix = crop(img_matrix, x1, y1, x2, y2, &width, &height);
			selectt_all(&x1, &y1, &x2, &y2, width, height);
			printf("Image cropped\n");
		} else if (!strcmp(type_com, "SHOW")) {
			printf("%d %d %d %d\n", x1, y1, x2, y2);
		} else if (!strcmp(type_com, "SEPIA")) {
			printf("Sepia filter not available\n");
		} else if (!strcmp(type_com, "GRAYSCALE")) {
			printf("Grayscale filter not available\n");
		} else if (!strcmp(type_com, "SAVE")) {
			save(command, tip, max_val, img_matrix, width, height);
		} else {
			printf("Invalid command\n");
		}

		fgets(command, COM_LEN, stdin); //citirea urmatoarei comenzi
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = 0;
		strcpy(com_copy, command);
	}

	free_matrix_int(img_matrix, height); //eliberarea memoriei
	fclose(image);
	free(com_copy);
	free(command);
}

void load_p3(char *file_name, char *tip, char **next_file)
{
	FILE *image = fopen(file_name, "r"); //verific daca exista fisierul
	if (!image) {
		printf("Could not load %s\n", file_name);
		return;
	}
	int width, height, max_val, pos;
	int x1, y1, x2, y2;
	fseek(image, 2, SEEK_SET);
	fscanf(image, "%d%d%d", &width, &height, &max_val);
	x1 = 0; y1 = 0; x2 = width; y2 = height;
	pixel **img_matrix = alloc_matrix_pixel(height, width);
	pos = (int)ftell(image);
	printf("Loaded %s\n", file_name);
	if (!strcmp(tip, "P6")) {
		fclose(image);
		image = fopen(file_name, "rb"); //nu trb verificat pt ca sigur exista
		fseek(image, pos + 1, SEEK_SET);
	}
	read_matrix_pixel(image, img_matrix, height, width, tip); //citire matrice
	char *command = alloc_string(COM_LEN); //comanda introdusa
	fgets(command, COM_LEN, stdin);        //citirea comenzii
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = 0;
	char *com_copy = alloc_string(COM_LEN); //copie pt strtok
	strcpy(com_copy, command);

	while (TRUE) { //citesc si execut instruciunile introduse
		char *type_com = strtok(com_copy, " ");
		if (!strcmp(type_com, "PRINT")) {
			print_matrix_pixel(stdout, img_matrix, height, width);
		} else if (!strcmp(type_com, "LOAD")) {
			type_com = strtok(NULL, " ");
			strcpy(*next_file, type_com);
			break;
		} else if (!strcmp(type_com, "EXIT")) {
			strcpy(*next_file, "\0");
			break;
		} else if (!strcmp(type_com, "SHOW")) {
			printf("%d %d %d %d\n", x1, y1, x2, y2);
		} else if (!strcmp(type_com, "SELECT")) {
			type_com = strtok(NULL, " ");
			if (!strcmp(type_com, "ALL")) {
				selectt_all(&x1, &y1, &x2, &y2, width, height);
				printf("Selected ALL\n");
			} else {
				selectt(command, &x1, &y1, &x2, &y2, width, height);
			}
		} else if (!strcmp(type_com, "ROTATE")) {
			rotate_pixel(command, &img_matrix, &x1, &y1, &x2, &y2, &width,
						 &height);
		} else if (!strcmp(type_com, "CROP")) {
			img_matrix = crop_pixel(img_matrix, x1, y1, x2, y2, &width,
									&height);
			selectt_all(&x1, &y1, &x2, &y2, width, height);
			printf("Image cropped\n");
		} else if (!strcmp(type_com, "SAVE")) {
			save_pixel(command, tip, max_val, img_matrix, width, height);
		} else if (!strcmp(type_com, "GRAYSCALE")) {
			grayscale(img_matrix, x1, y1, x2, y2);
		} else if (!strcmp(type_com, "SEPIA")) {
			if (!if_grayscale(img_matrix, x1, y1, x2, y2))
				sepia(img_matrix, x1, y1, x2, y2, max_val);
			else
				printf("Sepia filter not available\n");
		} else {
			printf("Invalid command\n");
		}

		fgets(command, COM_LEN, stdin); //citirea urmatoarei comenzi
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = 0;
		strcpy(com_copy, command);
	}

	free_matrix_pixel(img_matrix, height); //eliberarea memoriei
	free(command);
	free(com_copy);
	fclose(image);
}

//creierul opertaiunii de load, decide ce fel de fisier se deschide
void load(char *command, char **next_file)
{
	char *file_name = strtok(command, " ");
	file_name = strtok(NULL, " ");

	FILE *image = fopen(file_name, "rt");
	if (!image) { //daca esueaza LOAD-ul
		printf("Failed to load %s\n", file_name);
		strcpy(*next_file, "vreau sa intru in examen");
		return;
	}
	char tip[2];
	fscanf(image, "%s", tip); //P1, P2, P3, etc.
	if (!strcmp(tip, "P1") || !strcmp(tip, "P2") || !strcmp(tip, "P4") ||
	    !strcmp(tip, "P5")) //daca nu-i color
		load_p12(file_name, tip, next_file);
	else if (!strcmp(tip, "P3") || !strcmp(tip, "P6")) //daca e color
		load_p3(file_name, tip, next_file);
	fclose(image);
}

void selectt(char *command, int *x1, int *y1, int *x2, int *y2, int width,
			 int height)
{
	int   nx1, ny1, nx2, ny2;
	char *coord = strtok(command, " ");
	coord = strtok(NULL, " ");
	if (!coord || (coord[0] >= 'a' && coord[0] <= 'z')) {
		printf("Invalid command\n");
		return;
	}
	nx1 = atoi(coord);
	coord = strtok(NULL, " ");
	if (!coord || (coord[0] >= 'a' && coord[0] <= 'z')) {
		printf("Invalid command\n");
		return;
	}
	ny1 = atoi(coord);
	coord = strtok(NULL, " ");
	if (!coord || (coord[0] >= 'a' && coord[0] <= 'z')) {
		printf("Invalid command\n");
		return;
	}
	nx2 = atoi(coord);
	coord = strtok(NULL, " ");
	if (!coord || (coord[0] >= 'a' && coord[0] <= 'z')) {
		printf("Invalid command\n");
		return;
	}
	ny2 = atoi(coord);

	if (nx1 > nx2)
		swap_int(&nx1, &nx2);
	if (ny1 > ny2)
		swap_int(&ny1, &ny2);

	int ok = 1;
	if (nx1 < 0 || nx1 > width) //daca nx1 nu e coordonata valida
		ok = 0;
	if (ny1 < 0 || ny1 > height) //daca ny1 nu e coordonata valida
		ok = 0;
	if (nx2 < nx1 || nx2 > width) //daca nx2 nu e coordonata valida
		ok = 0;
	if (ny2 < ny1 || ny2 > height) //daca ny2 nu e coordonata valida
		ok = 0;
	if (nx2 - nx1 < 1 && ny2 - ny1 < 1)
		ok = 0;
	if (nx1 == nx2 || ny1 == ny2)
		ok = 0;
	if (ok) { //daca toate coord sunt bune, sa le atribuie
		*x1 = nx1;
		*y1 = ny1;
		*x2 = nx2;
		*y2 = ny2;
		printf("Selected %d %d %d %d\n", nx1, ny1, nx2, ny2);
	} else {
		printf("Invalid set of coordinates\n");
	}
}

void selectt_all(int *x1, int *y1, int *x2, int *y2, int width, int height)
{
	*x1 = 0;
	*y1 = 0;
	*x2 = width;
	*y2 = height;
}

int **crop(int **a, int x1, int y1, int x2, int y2, int *width, int *height)
{
	int height_copy = *height;
	if (x2 - x1 == *width && y2 - y1 == *height)
		return a;
	*width = x2 - x1;
	*height = y2 - y1;
	//construiesc o matrice noua si o inlocuiesc pe cea veche
	int **new = alloc_matrix_int(*height, *width);
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++)
			new[i][j] = a[y1 + i][x1 + j];
	}
	free_matrix_int(a, height_copy); //eliberez memoria pentru cea veche
	return new; //o intorc pe cea noua
}

pixel **crop_pixel(pixel **a, int x1, int y1, int x2, int y2, int *width,
				   int *height)
{
	int height_copy = *height;
	if (x2 - x1 == *width && y2 - y1 == *height)
		return a;
	*width = x2 - x1;
	*height = y2 - y1;
	pixel **new = alloc_matrix_pixel(*height, *width);
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++)
			new[i][j] = a[y1 + i][x1 + j];
	}
	free_matrix_pixel(a, height_copy);
	return new;
}

// verifica daca selectia curenta este grayscale; folosita pt sepia
int if_grayscale(pixel **a, int x1, int y1, int x2, int y2)
{
	int ok = 0;
	for (int i = y1; i < y2; i++) {
		if (ok) {
			for (int j = x1; j < x2; j++)
				if (a[i][j].red != a[i][j].green ||
				    a[i][j].green != a[i][j].blue ||
				    a[i][j].blue != a[i][j].red) {
					ok = 1;
					break;
				}
		}
	}
	return ok;
}

void grayscale(pixel **a, int x1, int y1, int x2, int y2)
{
	double new_color;
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			new_color = (a[i][j].red + a[i][j].green + a[i][j].blue) / 3;
			a[i][j].red = round(new_color);
			a[i][j].green = a[i][j].red;
			a[i][j].blue = a[i][j].red;
		}
	}
	printf("Grayscale filter applied\n");
}

void sepia(pixel **a, int x1, int y1, int x2, int y2, int max_val)
{
	double nred, ngreen, nblue;
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			nred =
			0.393 * a[i][j].red + 0.769 * a[i][j].green + 0.189 * a[i][j].blue;
			if (nred > max_val) //daca e mai mare de 255, o fac 255
				nred = max_val;
			else
				nred = round(nred);

			ngreen =
			0.349 * a[i][j].red + 0.686 * a[i][j].green + 0.168 * a[i][j].blue;
			if (ngreen > max_val) //daca e mai mare de 255, o fac 255
				ngreen = max_val;
			else
				ngreen = round(ngreen);

			nblue =
			0.272 * a[i][j].red + 0.534 * a[i][j].green + 0.131 * a[i][j].blue;
			if (nblue > max_val) //daca e mai mare de 255, o fac 255
				nblue = max_val;
			else
				nblue = round(nblue);
			a[i][j].red = nred;
			a[i][j].green = ngreen;
			a[i][j].blue = nblue;
		}
	}
	printf("Sepia filter applied\n");
}

void save(char *command, char *tip, int max_val, int **a, int width,
		  int height)
{
	FILE *image;
	char *p = strtok(command, " ");
	char *file_name = alloc_string(COM_LEN);
	int   pos, allocated = 0;
	p = strtok(NULL, " ");
	strcpy(file_name, p);
	p = strtok(NULL, " ");
	if (!p) { //daca nu se specifica ascii, se face binary
		p = alloc_string(7 * sizeof(char));
		allocated = 1;
		strcpy(p, "binary");
	}

	image = fopen(file_name, "wt");
	if (!strcmp(p, "ascii")) { //printare imagine ascii
		if (!strcmp(tip, "P1"))
			fprintf(image, "P1\n%d %d\n", width, height);
		else if (!strcmp(tip, "P2"))
			fprintf(image, "P2\n%d %d\n%d\n", width, height, max_val);
		else if (!strcmp(tip, "P4"))
			fprintf(image, "P1\n%d %d\n", width, height);
		else if (!strcmp(tip, "P5"))
			fprintf(image, "P2\n%d %d\n%d\n", width, height, max_val);
		print_matrix_int(image, a, height, width);
	} else if (!strcmp(p, "binary")) { //printare imagine binary
		if (!strcmp(tip, "P1"))
			fprintf(image, "P4\n%d %d\n", width, height);
		else if (!strcmp(tip, "P2"))
			fprintf(image, "P5\n%d %d\n%d\n", width, height, max_val);
		else if (!strcmp(tip, "P4"))
			fprintf(image, "P4\n%d %d\n", width, height);
		else if (!strcmp(tip, "P5"))
			fprintf(image, "P5\n%d %d\n%d\n", width, height, max_val);
		pos = (int)ftell(image);
		fclose(image);
		image = fopen(file_name, "ab");
		fseek(image, pos + 1, SEEK_SET);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				fwrite(&a[i][j], sizeof(unsigned char), 1, image);
		if (allocated)
			free(p);
	} else {
		printf("Unsupported format\n"); //daca se introduce un fomrat gresit
	}
	printf("Saved %s\n", file_name);
	fclose(image);
	free(file_name);
}

void save_pixel(char *command, char *tip, int max_val, pixel **a, int width,
				int height)
{
	FILE *image;
	char *p = strtok(command, " ");
	char *file_name = alloc_string(COM_LEN);
	int   pos, allocated = 0;
	p = strtok(NULL, " ");
	strcpy(file_name, p);
	p = strtok(NULL, " ");

	if (!p) {
		p = alloc_string(7);
		allocated = 1;
		strcpy(p, "binary");
	}

	image = fopen(file_name, "wt");
	if (!strcmp(p, "ascii")) {
		if (!strcmp(tip, "P3"))
			fprintf(image, "P3\n%d %d\n%d\n", width, height, max_val);
		else if (!strcmp(tip, "P6"))
			fprintf(image, "P3\n%d %d\n%d\n", width, height, max_val);
		print_matrix_pixel(image, a, height, width);
	} else if (!strcmp(p, "binary")) {
		if (!strcmp(tip, "P3"))
			fprintf(image, "P6\n%d %d\n%d\n", width, height, max_val);
		else if (!strcmp(tip, "P6"))
			fprintf(image, "P6\n%d %d\n%d\n", width, height, max_val);
		pos = (int)ftell(image);
		fclose(image);
		image = fopen(file_name, "ab");
		fseek(image, pos + 1, SEEK_SET);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				fwrite(&a[i][j].red, sizeof(unsigned char), 1, image);
				fwrite(&a[i][j].green, sizeof(unsigned char), 1, image);
				fwrite(&a[i][j].blue, sizeof(unsigned char), 1, image);
			}
		if (allocated)
			free(p);
	} else {
		printf("Unsupported format\n");
	}
	printf("Saved %s\n", file_name);
	fclose(image);
	free(file_name);
}
