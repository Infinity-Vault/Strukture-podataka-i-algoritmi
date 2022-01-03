#include <iostream>
#include "BinarySearchTree.h"//Kako bi imali dostupnu klasu BinarySearchTree (ona vec sadrzi BTCvor stoga ne moramo ukljucivati zasebno taj header);
using namespace std;

//Funkcija koja generise random broj:
int GetRandom()
{
	return rand() % 100 + 1;//Vratimo broj izmedju 0 i 100;
}
void main() 
{
	srand(time(NULL));//Ceed za rand metodu;

	//Kreiramo drvo:
	BinarySearchTree Drvo;

	//Dodamo 10 nasumicnih brojeva:
	for (int i = 0; i < 10; i++) 
	{
		int temp = GetRandom();//Generisemo nasumican broj;
		cout << "Dodan broj: " << temp << endl;
		Drvo.Dodaj(temp);
	}

	//Pretraga u drvu:
	int broj;
	cout << "Unesite broj za pretragu: " << endl;
	cin >> broj;
	BTCvor<int>* roditelj = Drvo.Trazi(broj);//Dobijemo roditelja koji odgovara trazenoj vrijednosti;

	if (roditelj != nullptr)//Roditelj je pronadjen;
	{
		cout << "Roditelj postoji: " <<*roditelj<< endl;//Ispisemo roditelja;
		if (roditelj->_desnoDijete != nullptr)//Desno dijete postoji;
			cout << "Desno dijete: " << *roditelj->_desnoDijete << endl;
		else
			cout << "Desno dijete ne postoji!" << endl;
		if (roditelj->_lijevoDijete != nullptr)//Lijevo dijete postoji;
			cout << "Lijevo dijete: " << *roditelj->_lijevoDijete << endl;
		else
			cout << "Lijevo dijete ne postoji!" << endl;
	}
	else//Roditelj nije pronadjen;
		cout << "Roditelj sa  zadanom vrjednoscu ne postoji u datom drvu!";

	Drvo.~BinarySearchTree();//Destruktor;//Reciklira (dealocira) se citavo drvo;

	//Dodamo 10 nasumicnih brojeva:
	for (int i = 0; i < 10; i++)
	{
		int temp = GetRandom();//Generisemo nasumican broj;
		cout << "Dodan broj: " << temp << endl;
		Drvo.Dodaj(temp);
	}
}