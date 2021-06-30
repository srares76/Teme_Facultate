#include <stdio.h>
#define NMAX 999999

void citire_vect(int v[], int n)
{
	for (int i = 0; i < n; ++i)
		scanf("%d", &v[i]);
}

void afisare_vect(int v[], int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", v[i]);
	printf("\n");
}

void sortare_vector(int v[], int n)
{
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (v[i] > v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

int main(void)
{
	int N, suma_credite = 0, p_min, m = 0;
	scanf("%d", &N);
	int vect_cn[NMAX], vect_diferente[NMAX], contor = -1;

	citire_vect(vect_cn, 2 * N); //Citirea vectorului de note/credite

	scanf("%d", &p_min); // citirea punctajului minim dorit
	// calculul punctelor obtinute
	for (int i = 0; i < N; i++)
		suma_credite += vect_cn[i] * vect_cn[i + N];

	if (suma_credite < p_min) {
		for (int i = 0; i < N; ++i)
			if (vect_cn[i] == 10)
				continue;
			else
				vect_diferente[++contor] = (10 - vect_cn[i]) * vect_cn[i + N];
	} else {
		printf("%d", m);
		return 0;
	}
	sortare_vector(vect_diferente, contor + 1);
	// afisare_vect(vect_diferente, contor + 1);

	while (suma_credite < p_min && contor >= 0) {
		suma_credite += vect_diferente[contor--];
		m++;
	}

	if (suma_credite < p_min)
		m = -1;

	printf("%d\n", m);

	return 0;
}
