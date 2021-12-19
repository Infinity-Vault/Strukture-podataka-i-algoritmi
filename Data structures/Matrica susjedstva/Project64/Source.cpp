#include <iostream>
#include <fstream>//Ukljucimo fstream biblioteku kako bi mogli manipulisati input i output-om fajla;
#include "Lista.h"
#include "ListaPov.h"
using namespace  std;


//Klasa MatricaSusjedstva:
class MatricaSusjedstva
{
private:
	int** Matrica;//2D matrica;
	int matricaSize;
	void AlocirajMatricu(int size)//Metoda koja ce da alocira matricu;
	{
		//Posto se radi o 2D matrici, prvo napravimo niz pokazivaca;
		Matrica = new int* [size];//Niz pokazivaca;
		for (int i = 0; i < size; i++)
			Matrica[i] = new int[size];//Pa onda svaki pokazivac individualno pokazuje na jednodim. niz;
	}
public:
	//User-def ctor:
	MatricaSusjedstva(string putanjaDoFajla, int size)//Primimo velicinu matrice i putanju do fajla u kojem se nalazi;
	{
		matricaSize = size;//Pokupimo ulaznu velicinu poslane matrice;
		ifstream fajl(putanjaDoFajla);//Kreiramo ifstream objekat koji nam omogucava citanje iz fajla;
		AlocirajMatricu(size);//Izvrsimo alokaciju matrice;
		
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int trenutniBr;//Kreiramo var;
				fajl >> trenutniBr;//U varijablu ucitamo broj iz fajla koji je trenutno na redu;
				Matrica[i][j] = trenutniBr;//Pohranimo taj broj u nasu matricu;
			}
		}
		fajl.close();//Otvoreni fajl uvijek moramo zatvoriti;
	}

	//Metoda za ispis elemenata matrice:
	void ispis()
	{
		for (int i = 0; i < matricaSize; ++i)
		{
			for (int j = 0; j < matricaSize; ++j)
			{
				cout << Matrica[i][j] << " | ";
			}
			cout << endl;//Nakon svakog reda predjemo u novi red konzole;
		}
	}

	int izlazniStepen(int red)
	{
		//Izlazni stepen predstavlja broj jedinica (1) u jednom redu matrice;

		int brojPonavljanja = 0;
		for (int j = 0; j < matricaSize; ++j)
		{
			brojPonavljanja += Matrica[red][j];//Kretanjem po samo jednom redu mozemo izkalkulisati broj jedinica tako sto ih sve saberemo;
		}
		return brojPonavljanja;
	}

	int ulazniStepen(int kolona)
	{
		//Ulazni stepen predstavlja broj ponavljanja jedinica (1) u jednoj koloni;
		int brojPonavljanja = 0;
		for (int i = 0; i < matricaSize; ++i)
		{
			brojPonavljanja += Matrica[i][kolona];//Na ovaj nacin krecemo se samo po jednom koloni i iz nje saberemo sve jedinice;
		}
		return brojPonavljanja;
	}

	Lista* susjediTo(int red)
	{
		//Susjede prema mozemo predstaviti tako sto gledamo samo ulazni red te  sve elemente u njemu koji su != 0 dodamo u kreiranu listu susjeda;
		Lista* susjedi = new ListaPov;//Kreiramo empty listu;
		for (int j = 0; j < matricaSize; j++)
		{
			if (Matrica[red][j] != 0)//Ako je element razlicit od nule (jer gledamo samo jedinice);
				susjedi->dodaj_na_pocetak(j);//Dodaj taj element;
		}
		return susjedi;//Vratimo listu;
	}

	Lista* susjediFrom(int kolona)
	{
		//Susjede from racunamo na nacin da se krecemo po ulaznoj koloni koja je poslata,te ako su elementi != 0 dodamo ih u listu;
		Lista* susjedi = new ListaPov;
		for (int i = 0; i < matricaSize; ++i)
		{
			if (Matrica[i][kolona] != 0)//Samo ako je element razlicit od nule (tj. ako je 1);
				susjedi->dodaj_na_pocetak(i);//Dodaj ga;
		}
		return susjedi;//Vrati listu;
	}
};



void main()
{
	//NOTE:
	//Promjenite putanju do svog fajla jer nece biti ista;
	MatricaSusjedstva Matrica("C:\\Users\\haris\\Desktop\\matrica susjedstva\\MatricaSusjedstva\\Project64\\matrica.txt", 8);//Kreiramo objekat sa putanjom i velicinom u ctoru;

	cout << "Izlazni stepen za 0: " << Matrica.izlazniStepen(0) << endl;
	cout << "Ulazni stepen za 0: " << Matrica.ulazniStepen(0) << endl;

	cout << "Susjedi reda 0: " << Matrica.susjediTo(0)->get_brojac() << endl;//Dobijemo broj susjeda reda 0;
	cout << "Susjedi kolone 0: " << Matrica.susjediFrom(0)->get_brojac() << endl;//Dobijemo broj susjeda kolone 0;

	Matrica.ispis();
}