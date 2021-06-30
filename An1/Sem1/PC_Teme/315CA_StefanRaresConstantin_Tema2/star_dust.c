// Stefan Rares Constantin - 315CA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void swap_values(char *a, char *b)
{
	char aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int **alloc_matrix(int n, int *m)
{
	// Alocarea si citirea matricei de elemente int in baza 16
	int **matrix = (int **)malloc(n * sizeof(int *));
	if (!matrix) {
		free(matrix);
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &m[i]);
		matrix[i] = (int *)malloc(m[i] * sizeof(int));
		if (!matrix[i]) {
			for (int j = 0; j < i; j++)
				free(matrix[j]);
			free(matrix);
			return NULL;
		}
		for (int j = 0; j < m[i]; ++j)
			scanf("%X", &matrix[i][j]);
	}
	return matrix;
}

char **alloc_matchar(int **a, int n, int *m)
{
	// Generearea matricii de bytes, in format char, pe baza
	// celei citite de la tastatura, in format int
	char **ch = (char **)malloc(n * sizeof(char *));
	if (!ch) {
		free(ch);
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		ch[i] = (char *)malloc(m[i] * 4 * sizeof(char));
		if (!ch[i]) {
			for (int j = 0; j < i; j++)
				free(ch[j]);
			free(ch);
			return NULL;
		}
		int p = 0;
		m[i] *= 4;
		for (int j = 0; j < m[i]; j += 4) {
			ch[i][j] = a[i][p] & 0xFF; // ultimul byte al nr
			ch[i][j + 1] = (a[i][p] >> 8) & 0xFF; //penultimul byte al nr
			ch[i][j + 2] = (a[i][p] >> 16) & 0xFF; //al doilea byte al nr
			ch[i][j + 3] = (a[i][p] >> 24) & 0xFF; //primul byte al nr
			p++;
		}
	}
	return ch;
}

void print_matrix(char **ch, int n, int *m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m[i]; ++j)
			printf("%d ", ch[i][j]);
		printf("\n");
	}
}

double shield(char **ch, int n, int *m)
{
	int sum = 0, nr = 0;
	for (int i = 0; i < m[0]; ++i) { //suma de pe prima linie
		sum += ch[0][i];
		nr++;
	}
	for (int i = 0; i < m[n - 1]; ++i) { //suma de pe ultima linie
		sum += ch[n - 1][i];
		nr++;
	}
	for (int i = 1; i < n - 1; ++i) { //suma de pe prima coloana
		sum += ch[i][0];
		nr++;
	}
	for (int i = 1; i < n - 1; ++i) { //suma de pe ultima coloana
		sum += ch[i][m[i] - 1];
		nr += 1;
	}
	return (1.0 * sum) / nr;
}

void delete_char(char **ch, int lin, int col)
{
	ch[lin][col - 1] = 0;
}

void modify_char(char **ch, int lin, int col, int *m, char num)
{
	while (col > m[lin]) { //Genereaza cate alte elemente sunt necesare
		m[lin] += 4;
		char *aux;
		aux = (char *)realloc(ch[lin], m[lin] * sizeof(char));
		if (aux)
			ch[lin] = aux;
		ch[lin][m[lin] - 1] = 0;
		ch[lin][m[lin] - 2] = 0;
		ch[lin][m[lin] - 3] = 0;
		ch[lin][m[lin] - 4] = 0;
	}
	ch[lin][col - 1] = num;
}

void delete_short(char **ch, int lin, int col)
{
	ch[lin][2 * (col - 1)] = 0;
	ch[lin][2 * col - 1] = 0;
}

void modify_short(char **ch, int lin, int col, int *m, short num)
{
	while (2 * col > m[lin]) { //Genereaza cate alte elemente sunt necesare
		m[lin] += 4;
		char *aux;
		aux = (char *)realloc(ch[lin], m[lin] * sizeof(char));
		if (aux)
			ch[lin] = aux;
		ch[lin][m[lin] - 1] = 0;
		ch[lin][m[lin] - 2] = 0;
		ch[lin][m[lin] - 3] = 0;
		ch[lin][m[lin] - 4] = 0;
	}
	ch[lin][2 * (col - 1)] = num & 0xFF;
	ch[lin][2 * col - 1] = (num >> 8) & 0xFF;
}

void swap_short(char **ch, int lin, int col)
{
	swap_values(&ch[lin][2 * col - 1], &ch[lin][2 * (col - 1)]);
}

void delete_int(char **ch, int lin, int col)
{
	ch[lin][4 * col - 1] = 0;
	ch[lin][4 * col - 2] = 0;
	ch[lin][4 * col - 3] = 0;
	ch[lin][4 * (col - 1)] = 0;
}

void modify_int(char **ch, int lin, int col, int *m, int num)
{
	while (4 * col > m[lin]) { //Genereaza cate alte elemente sunt necesare
		m[lin] += 4;
		char *aux;
		aux = (char *)realloc(ch[lin], m[lin] * sizeof(char));
		if (aux)
			ch[lin] = aux;
		ch[lin][m[lin] - 1] = 0;
		ch[lin][m[lin] - 2] = 0;
		ch[lin][m[lin] - 3] = 0;
		ch[lin][m[lin] - 4] = 0;
	}
	ch[lin][4 * (col - 1)] = num & 0xFF;
	ch[lin][4 * col - 3] = (num >> 8) & 0xFF;
	ch[lin][4 * col - 2] = (num >> 16) & 0xFF;
	ch[lin][4 * col - 1] = (num >> 24) & 0xFF;
}

void swap_int(char **ch, int lin, int col)
{
	swap_values(&ch[lin][4 * (col - 1)], &ch[lin][4 * col - 1]);
	swap_values(&ch[lin][4 * col - 3], &ch[lin][4 * col - 2]);
}

int *alloc_vect(int *n)
{
	// Alocarea unui vector
	scanf("%d", n);
	int *vect = (int *)malloc(*n * sizeof(int));
	if (!vect)
		return NULL;
	return vect;
}

void task2(char **ch, int n, int *m, int k)
{
	//Citeste modificarile introduse si le executa
	char mds, ics;
	int lin, col;
	for (int i = 0; i < k; ++i) {
		scanf(" %c", &mds);
		scanf(" %c", &ics);
		scanf("%d", &lin);
		scanf("%d", &col);
		if (mds == 'M') {
			int num;
			scanf("%x", &num);
			if (ics == 'I')
				modify_int(ch, lin, col, m, num);
			if (ics == 'S')
				modify_short(ch, lin, col, m, num);
			if (ics == 'C')
				modify_char(ch, lin, col, m, num);
		}
		if (mds == 'D') {
			if (ics == 'I')
				delete_int(ch, lin, col);
			if (ics == 'S')
				delete_short(ch, lin, col);
			if (ics == 'C')
				delete_char(ch, lin, col);
		}
		if (mds == 'S') {
			if (ics == 'I')
				swap_int(ch, lin, col + 1);
			if (ics == 'S')
				swap_short(ch, lin, col + 1);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m[i]; j += 4) { // afisarea matricii finale
			printf("%02X%02X", ch[i][j + 3] & 0xFF, ch[i][j + 2] & 0xFF);
			printf("%02X%02X ", ch[i][j + 1] & 0xFF, ch[i][j] & 0xFF);
		}

		printf("\n");
	}
}

void free_memory(int **map, char **ch, int *col, int n)
{
	// Elibereaza memoria atribuita dinamic
	for (int i = 0; i < n; ++i) {
		free(map[i]);
		free(ch[i]);
	}
	free(map);
	free(ch);
	free(col);
}

// Calculeaza recursiv numarul de 0-ori adiacente dintr-o hole neagra
int bhole_size(char **ch, int n, int *m, int lin, int col)
{
	int size = 0;
	if (ch[lin][col]) // Caut doar pentru elemente NULE
		return 0;
	size++;
	ch[lin][col] = -1;
	// Verific daca exista un element sub cel la care ma aflu
	if (lin + 1 <= n - 1 && m[lin + 1] > col)
		size += bhole_size(ch, n, m, lin + 1, col);
	// Verific daca exita un element deasupra celui la care ma aflu
	if (lin - 1 >= 0 && m[lin - 1] > col)
		size += bhole_size(ch, n, m, lin - 1, col);
	// Verific daca exita un element in stanga celui la care ma aflu
	if (col > 0)
		size += bhole_size(ch, n, m, lin, col - 1);
	// Verific daca exita un element in dreapta celui la care ma aflu
	if (col < m[lin] - 1)
		size += bhole_size(ch, n, m, lin, col + 1);
	return size;
}

// Tip de data care sa retina atributele care ma
// intereseaza ale unei gauri negre
typedef struct bhole {
	int pos_lin;
	int pos_col;
	int dimension;
} bhole;

void task3(char **ch, int n, int *m)
{
	bhole hole;
	int dim;
	hole.pos_lin = 0;
	hole.pos_col = 0;
	hole.dimension = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m[i]; j++) {
			dim = bhole_size(ch, n, m, i, j);
			if (hole.dimension < dim) {
				hole.dimension = dim;
				hole.pos_lin = i;
				hole.pos_col = j;
			}
		}
	printf("%d %d %d\n", hole.pos_lin, hole.pos_col, hole.dimension);
}

int main(void)
{
	int **map, n, *col, k;
	char **ch; //harta si dimensiunile sale
	double m_a;
	col = alloc_vect(&n); //aloc vectorul de dimensiuni
	map = alloc_matrix(n, col); // aloc matricea hartii
	ch = alloc_matchar(map, n, col); //aloc matricea bytes-ilor
	m_a = shield(ch, n, col);
	printf("task 1\n");
	printf("%0.8lf\n", m_a);
	printf("task 2\n");
	scanf("%d", &k); //Citeste numarul de operatii
	task2(ch, n, col, k); //Efectueaza operatiile asupra matricii
	printf("task 3\n");
	task3(ch, n, col);
	free_memory(map, ch, col, n); //Elibereaza memoria atrubuita dinamic
	return 0;
}
