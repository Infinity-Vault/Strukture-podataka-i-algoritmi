
#include "Cvor.h"
#include "Lista.h"

class ListaPov : public Lista
{
	Cvor* _head = nullptr;
	int brojac = 0;
public:
	void dodaj_na_pocetak(int x)
	{
		Cvor* n = new Cvor(x, _head);
		_head = n;
		brojac++;
	}

	int ukloni_sa_pocetka() {
		int x = _head->info;
		Cvor* t = _head;
		_head = _head->next;
		delete t;
		brojac--;
		return x;
	}

	void dodaj_na_kraj(int x) {

		if (_head == nullptr)
		{
			//ako je lista prazna
			//...
			_head = new Cvor(x, nullptr);
			return;
		}
		Cvor* t = _head;

		while (t->next != nullptr)
		{
			t = t->next;
		}

		t->next = new Cvor(x, nullptr);
		brojac++;
	}

	int ukloni_sa_kraja() {

		if (jel_prazna())
		{
			throw exception("greska... lista je prezna");
		}

		Cvor* pt = nullptr;
		Cvor* t = _head;

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
			_head = nullptr;
		}
		brojac--;
		return x;
	}

	bool jel_prazna()
	{
		return _head == nullptr;
	}

	int operator[](int index) {
		Cvor* t = _head;
		for (int i = 0; i < index; i++)
		{
			t = t->next;
		}

		return t->info;
	}

	int get_brojac()
	{
		return brojac;
	}

	bool ukloniByKey(int broj)//Broj koji treba ukloniti;
	{
		if (jel_prazna())
		{
			throw exception("Lista je prazna, te se nema sta ukloniti!");
			return false;//Element ne postoji;//Jer nema liste sa tim indeksom;
		}

		Cvor* trenutni = _head;//Trenutni je prvi to jest _head;
		Cvor* prijeTrenutnog = nullptr;//Prije trenutnog je na pocetku nullptr (ne pokazuje nigdje);

		while (trenutni->next != nullptr)//Iteriramo sve dok trenutni ne bude nullptr (tj. dok se ne dodje  do zadnjeg elementa u listi);
		{
			if (trenutni->info == broj)
				break;//Odmah smo nasli element koji smo trazili stoga iskacemo iz petlje;
			prijeTrenutnog = trenutni;
			trenutni = trenutni->next;
		}
		if (trenutni == nullptr)//Broj ne postoji u listi;
			return false;
		if (prijeTrenutnog == nullptr)//Broj se nalazi na pocetku liste;
			_head = _head->next;//Stoga samo glavu (_head,prvi el.) postavi da pokazuje na naredni;
		else//Broj se nalazi izmedju neka druga dva broja npr: X broj X;
			prijeTrenutnog->next = trenutni->next;//X pokazuje na X, dok smo broj izbacili;

		delete trenutni;//Obrisemo broj koji smo htjeli obrisati;
		brojac--;//Jer smo uklonili jedan element liste;
		return true;//Vratimo true kao signal da je broj uklonjen;
	};
};
