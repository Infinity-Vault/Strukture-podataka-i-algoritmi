#pragma once

#include  "Lista.h"


class ListaSekv : public Lista
{
	int brojac = 0;
	int max = 5;
	int* N = new int[max];
public:
	void dodaj_na_pocetak(int x)
	{
		if (brojac == max)
			prosiri_niz();

		for (int i = brojac; i >= 1; i--)
			N[i] = N[i - 1];

		brojac++;
		N[0] = x;
	}

	void prosiri_niz() {
		int* novi = new int[max + 10];

		for (int i = 0; i < max; ++i)
		{
			novi[i] = N[i];
		}
		delete[] N;
		N = novi;
		max += 10;
		cout << "niz je prosiren sa " << max - 10 << " na " << max << endl;
	}

	int ukloni_sa_pocetka() {
		if (brojac == 0)
			throw exception("greska... lista je prazna");

		int x = N[0];

		for (int i = 0; i < brojac - 1; i++)
			N[i] = N[i + 1];

		brojac--;
		return x;

	}

	void dodaj_na_kraj(int x) {
		if (brojac == max)
			prosiri_niz();

		N[brojac] = x;
		brojac++;
	}

	int ukloni_sa_kraja() {

		if (brojac == 0) throw exception("greska... lista je prazna");

		brojac--;
		int x = N[brojac];

		return x;
	}

	bool jel_prazna()
	{
		return brojac == 0;
	}

	int operator[](int index) {
		if (index<0 || index>max)
			throw exception("greska... indeks je neispravan");
		return N[index];
	}

	int get_brojac() {
		return brojac;
	}
};