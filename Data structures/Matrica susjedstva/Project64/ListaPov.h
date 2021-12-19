
#include "Cvor.h"
#include "Lista.h"

class ListaPov : public Lista
{
	Cvor* prvi = nullptr;
	int brojac = 0;
public:
	void dodaj_na_pocetak(int x)
	{
		Cvor* n = new Cvor(x, prvi);
		prvi = n;
		brojac++;
	}

	int ukloni_sa_pocetka() {
		int x = prvi->info;
		Cvor* t = prvi;
		prvi = prvi->next;
		delete t;
		brojac--;
		return x;
	}

	void dodaj_na_kraj(int x) {

		if (prvi == nullptr)
		{
			//ako je lista prazna
			//...
			prvi = new Cvor(x, nullptr);
			return;
		}
		Cvor* t = prvi;

		while (t->next != nullptr)
		{
			t = t->next;
		}

		t->next = new Cvor(x, nullptr);
	}

	int ukloni_sa_kraja() {

		if (jel_prazna())
		{
			throw exception("greska... lista je prezna");
		}

		Cvor* pt = nullptr;
		Cvor* t = prvi;

		while (t->next != nullptr)
		{
			pt = t;
			t = t->next;
		}
		int x = t->info;
		delete t;

		if (pt != nullptr)
		{
			pt->next = nullptr;
		}
		else
		{
			prvi = nullptr;
		}
		return x;
	}

	bool jel_prazna()
	{
		return prvi == nullptr;
	}

	int operator[](int index) {
		Cvor* t = prvi;
		for (int i = 0; i < index; i++)
		{
			t = t->next;
		}

		return t->info;
	}

	int get_brojac() {
		return brojac;
	}

	bool ukloniByKey(int i)
	{
		//radni zadatak
	}
};
