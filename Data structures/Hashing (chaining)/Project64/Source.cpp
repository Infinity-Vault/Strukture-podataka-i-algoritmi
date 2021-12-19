#include <iostream>

#include "Lista.h"
#include "ListaPov.h"
using namespace  std;

class HesiranjeUlancavanje
{
	int size = 10;//Velicina niza;
	ListaPov* Niz = new ListaPov[size];//Kreiramo niz Listi,velicine size;
	int brojac = 0;//Brojac elemenata;

	int heshFunkcija(int broj)
	{
		return broj % size;//Ulazni broj koji posaljemo ovoj metodi cemo da moduliramo sa 10 te dobijemo njegovu zadnju cifru;
	}
public:
	void dodaj(int broj)
	{
		if (brojac == size)//Nema slobodnih pozicija u nizu;
			throw exception("Nema slobodnih mjesta na koje se moze dodati!");
		int indeksPozicija = heshFunkcija(broj);//Ideja je da zadnja cifra broja kojeg dodajemo jeste indeks pozicija na kojoj on treba biti u  kreiranom nizu listi;
		brojac++;//Uvecamo brojac jer smo dodali jedan element;
		Niz[indeksPozicija].dodaj_na_pocetak(broj);//Na poziciju koju smo izracunali dodamo novi broj (radi se o nizu listi, tako da je indeksPozicija ustvari zasebna lista u koju se dodaje trenutni broj);
	}

	bool ukloni(int broj)
	{
		if (brojac == 0)//Niz je prazan te nema elemenata za uklanjanje;
			throw exception("Nema elemenata za ukloniti!");

		int indeksPozicija = heshFunkcija(broj);//Dobijemo indeks poziciju elementa koji zelimo ukloniti,tj. saznamo u kojoj listi se nalazi;
		return Niz[indeksPozicija].ukloniByKey(broj);//U adekvatnoj listi (koju znamo preko indeksPozicije) uklonimo  element sa vrijednoscu 'broj';
	}
};


void main()
{
	
	try
	{
		HesiranjeUlancavanje* heshTabela = new HesiranjeUlancavanje;
		for (int i = 0; i < 5; ++i)
		{
			cout << "Unesite broj: " << endl;
			int broj;
			cin >> broj;
			heshTabela->dodaj(broj);
		}

		cout << "Unesite broj za ukloniti: " << endl;
		int broj;
		cin >> broj;
		if (heshTabela->ukloni(broj))
		{
			cout << "Broj je uklonjen" << endl;
		}
		else
		{
			cout << "Broj se ne nalazi u hesh tabeli" << endl;
		}
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}	
}