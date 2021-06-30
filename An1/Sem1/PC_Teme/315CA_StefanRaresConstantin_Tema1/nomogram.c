#include <stdio.h>
#define NMAX 300

void citire_matrice(int a[][NMAX], int n, int m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			scanf("%d", &a[i][j]);
	}
}

// calculeaza sumele CORESPUNZATOARE fiecarei linii si coloane
// Si le retine intr-un vector
void calcul_sume(int v[], int linii, int coloane)
{
	int nr_elem, dim_grup;
	for (int i = 0; i < linii; ++i) {
		scanf("%d", &nr_elem);
		for (int j = 0; j < nr_elem; ++j) {
			scanf("%d", &dim_grup);
			v[i] += dim_grup;
		}
	}
	for (int i = linii; i < linii + coloane; ++i) {
		scanf("%d", &nr_elem);
		for (int j = 0; j < nr_elem; ++j) {
			scanf("%d", &dim_grup);
			v[i] += dim_grup;
		}
	}
}

// Calculeaza suma elementelor de pe fiecare linie si coloane ale matricii
// Si le retine intr-un vector
void calcul_sum_lin_col(int a[][NMAX], int N, int M, int linii_coloane[])
{
	int p = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			linii_coloane[p] += a[i][j];
		p++;
	}
	for (int j = 0; j < M; ++j) {
		for (int i = 0; i < N; ++i)
			linii_coloane[p] += a[i][j];
		p++;
	}
}

int main(void)
{
	int T, N, M, puzzle[NMAX][NMAX], corect = 1;
	int sume[NMAX] = {}, linii_coloane[NMAX] = {};
	scanf("%d", &T);
	// Calculeaza valorile dimensiunilor grupurilor de pe
	// Linii respectiv coloane si le memoreaza in vectorul sume
	for (int contor_mare = 0; contor_mare < T; contor_mare++) {
		scanf("%d %d", &N, &M);
		corect = 1;
		calcul_sume(sume, N, M);
		citire_matrice(puzzle, N, M);
		calcul_sum_lin_col(puzzle, N, M, linii_coloane);
		// Veridic daca cei doi vectori calculati sunt egali;
		for (int i = 0; i < N + M; ++i) {
			if (sume[i] != linii_coloane[i])
				corect = 0;
		}
		// Daca sunt egali, inseamna ca matricea e corecta, altfel da eroare
		if (corect)
			printf("Corect\n");
		else
			printf("Eroare\n");

		// "Golesc" matricea actuala ca sa poata fi verificata corect la
		// Urmatoarea iteratie
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j)
				puzzle[i][j] = 0;
		}
		// La fel si pentru vectorul sau
		for (int i = 0; i < N + M; i++) {
			sume[i] = 0;
			linii_coloane[i] = 0;
		}
	}
	return 0;
}
