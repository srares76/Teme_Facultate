#include <stdio.h>
#define NCIFMAX 10

//Functia care imi calculeaza valoarea numarului format din cifrele
//lui N in ordine crescatoare
int crescator(int n)
{
	int cresc = 0, v[NCIFMAX] = {};
	while (n) {
		v[n % 10]++;
		n /= 10;
	}
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < v[i]; j++)
			cresc = cresc * 10 + i;
	}
	return cresc;
}

//Functia care imi calculeaza valoarea numarului format din cifrele
//lui N in ordine descrescatoare
int descrescator(int n)
{
	int descresc = 0, v[NCIFMAX] = {};
	while (n) {
		v[n % 10]++;
		n /= 10;
	}
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < v[i]; j++)
			descresc = descresc * 10 + i;
	}
	return descresc;
}

// Functia care returneaza diferenta dintre n_desc si n_cresc
int diff(int n)
{
	return descrescator(n) - crescator(n);
}

// Functia care returneaza numarul de aparitii ale unui numar intr-un vector
int cautare_in_vector(int v[], int n, int nr)
{
	int aparitii = 0;
	for (int i = 0; i <= n; i++) {
		if (v[i] == nr)
			aparitii++;
	}
	if (aparitii == 1)
		return 1;
	if (aparitii == 2)
		return 2;
	return 0;
}

int main(void)
{
	// Declararea variabilelor si atribuirea de valori
	int N, vnr_intalnite[100];
	int contorv = -1, contor_nerepetate = 0;
	scanf("%d", &N);

	// Formarea vectorului care retine diferitele valori ale diferentei
	while (cautare_in_vector(vnr_intalnite, contorv, diff(N)) == 0) {
		vnr_intalnite[++contorv] = diff(N);
		N = diff(N);
	}

	vnr_intalnite[++contorv] = diff(N);

	// Cautarea primului element din vector care se repeta, de la care
	// se incepe afisarea elementelor, pana la intalnirea elementului
	// care se repeta
	for (int i = 0; i <= contorv; i++) {
		if (cautare_in_vector(vnr_intalnite, contorv, vnr_intalnite[i]) == 1)
			contor_nerepetate++;
		if (cautare_in_vector(vnr_intalnite, contorv, vnr_intalnite[i]) == 2) {
			printf("%d\n", contor_nerepetate);
			printf("%d ", vnr_intalnite[i]);
			for (int j = i + 1; vnr_intalnite[i] != vnr_intalnite[j]; j++)
				printf("%d ", vnr_intalnite[j]);
			printf("\n");
			break;
		}
	}

	return 0;
}
