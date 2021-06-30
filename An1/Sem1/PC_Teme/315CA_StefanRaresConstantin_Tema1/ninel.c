#include <stdio.h>

int minim(long n, long m)
{
	if (n < m)
		return n;
	return m;
}

int maxim(long n, long m)
{
	if (n > m)
		return n;
	return m;
}

void atribuire_zero(long *sum, double *avg, long *min, long *max)
{
	*sum = 0; *avg = 0; *min = 0; *max = 0;
	printf("%ld\n%.7lf\n%ld\n%ld\n", *sum, *avg, *max, *min);
}

int main(void)
{
	long N, copac_i, copac_iminus, copac_iplus, nr_speciali = 0;
	long S = 0, xmax_impar, xmin_par;
	double m_a;
	scanf("%ld", &N); // Citeste numarul de copaci
	if (N == 1) {
		scanf("%ld", &copac_iminus);
		atribuire_zero(&S, &m_a, &xmax_impar, &xmin_par);
		//afiseaza datele cerute
		return 0;
	}
	if (N == 2) {
		scanf("%ld%ld", &copac_iminus, &copac_i);
		atribuire_zero(&S, &m_a, &xmax_impar, &xmin_par);
		//afiseaza datele cerute
		return 0;
	}
	// Afiseaza ca nu exista copaci speciali daca nu sunt cel putin 3
	// si incheie executia programului

	//citeste inaltimile primilor 3 copaci
	scanf("%ld %ld %ld", &copac_iminus, &copac_i, &copac_iplus);
	if (N == 3) {
		if (copac_i > copac_iminus && copac_i > copac_iplus) {
			S = copac_i;
			m_a = copac_i;
			xmin_par = copac_i;
			xmax_impar = copac_i;
			//afiseaza datele cerute
			printf("%ld\n%.7lf\n%ld\n%ld\n", S, m_a, xmax_impar, xmin_par);
		} else {
			atribuire_zero(&S, &m_a, &xmax_impar, &xmin_par);
			//afiseaza datele cerute
		}
		return 0;
	}
	//initializez maximul si minimul val primului copac
	xmax_impar = 0; xmin_par = 1e9;
	for (int i = 1; i <= N - 2; i++) {
		// Verific daca un copac de indice i este special
		if (copac_i > copac_iminus && copac_i > copac_iplus) {
			S += copac_i;
			nr_speciali += 1;
			if (i % 2 == 0)
				xmin_par = minim(xmin_par, copac_i);
			else
				xmax_impar = maxim(xmax_impar, copac_i);
		}
		//Continutul acestui if nu mai trebuie parcurs la ultimul pas al
		//for-ului pt ca nu mai conteaza valoarea ultimului
		//copac: sigur nu e special
		if (i <= N - 3) {
			long aux1, aux2;
			aux1 = copac_iplus;
			aux2 = copac_i;
			scanf("%ld", &copac_iplus);
			copac_i = aux1;
			copac_iminus = aux2;
		}
	}
	//Verific daca am sau nu copaci speciali
	//Daca am, afisez valorile calculate
	//Daca nu am, afisez 0 0 0 0
	if (nr_speciali) {
		m_a = (S * 1.0) / nr_speciali;
		if (xmax_impar > 0 && xmin_par == 1e9)
			xmin_par = -1;
		if (xmax_impar == 0 && xmin_par < 1e9)
			xmax_impar = -1;
		printf("%ld\n%.7lf\n%ld\n%ld\n", S, m_a, xmax_impar, xmin_par);
	} else {
		atribuire_zero(&S, &m_a, &xmax_impar, &xmin_par);
		//afiseaza datele cerute
	}
	return 0;
}
