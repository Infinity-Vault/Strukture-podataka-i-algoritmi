#pragma once
#include "BTCvor.h"

//Binary tree:
//Binarno drvo radi na principu da svako lijevo dijete je manje od roditelja, a isto tako svako desno dijete
//je vece od roditelja.Prilikom dodavanja, dodaje se tako sto se prodje kroz citavo binarno drvo, i poredi se gdje
//trenutnu novu vrijednost treba smjestiti.


//Kreiramo klasu Binary Search Tree koja treba imati funkcionalnosti dodavanja, uklanjanja, trazenja i 
//recikliranja (dealokacije) citavog drva;

class BinarySearchTree 
{
private :
	BTCvor<int>* _korijen;//Kreiramo pokazivac tipa BTCvor koji ce imati ulogu korijena i pokazivati na sve ostale node-ove (djecu);

	//Procese dodavanja, uklanjanja,trazenja i recikliranja je najlakse implementirati rekurzivno, a 
	//radi enkapsulacije sve cemo drzati kao privatne metode nase klase;

	//Rekurzija za dodavanje:
	bool RekurzijaDodaj(BTCvor<int>*& ulazniNode, int x)//Proslijedjeni node primamo po referenci kako bi promjene bile vidljive i nakon izvresnja ove metode;
	{
		if (ulazniNode == nullptr)//Ukoliko je ulazni node prazan;
		{
			ulazniNode = new BTCvor<int>(x);//Odmah dodaj na njega novi cvor, nema potrebe da gledamo djecu (jer ona ne postoje);
			return true;
		}
		if (ulazniNode->_info == x)//Ako je info polje trenutnog node-a jednako nasem koji trenutno dodajemo;
			return false;//Vrati false, zato sto ne mozemo dodavati duplikate;
		if (x > ulazniNode->_info)//Ako je x vece od info, krecemo se desno;
			RekurzijaDodaj(ulazniNode->_desnoDijete, x);//Rekurzivni poziv za desno dijete;
		else//Ako je x manje od info, krecemo se lijevo;
			RekurzijaDodaj(ulazniNode->_lijevoDijete, x);//Rekurzivni poziv za lijevo dijete;
	}

	//Rekurzija za trazenje:
	BTCvor<int>* RekurzijaTrazi(BTCvor<int>* ulazniNode, int x) 
	{
		if (ulazniNode == nullptr)//Bazni slucaj, ukoliko je node nepostojeci;
			return nullptr;//Nemamo sta vratiti,node ne postoji;

		if (ulazniNode->_info == x)//Ako je x == info;
			return ulazniNode;//Vrati ulazni node;

		if (x > ulazniNode->_info)//Ako je x vece od info, radi se o desnom djetetu;
			return RekurzijaTrazi(ulazniNode->_desnoDijete, x);//Pozovemo rekurziju za desno dijete;

		else//Ako je x manje od info,radi se o lijevom djetetu;
			return RekurzijaTrazi(ulazniNode->_lijevoDijete, x);//Pozovemo rekurziju za lijevo dijete;
	}

	//Rekurzija za recikliranje (dealokaciju) drva:
	void RekurzijaRecikliraj(BTCvor<int>*& ulazniNode)//Saljemo referencu na pocetni node kako bi dealokacija bila zaista vidljiva i nakon zavrsetka ove metode;
	{
		if (ulazniNode != nullptr)//Bazni slucaj, sve dok ulazni node nije nullptr (node koji nema nijedno dijete);
		{
			RekurzijaRecikliraj(ulazniNode->_desnoDijete);//Rekurzija za desno dijete;
			RekurzijaRecikliraj(ulazniNode->_lijevoDijete);//Rekurzija za lijevo dijete;
			delete ulazniNode;//Obrisemo krajnji node;
			ulazniNode = nullptr;//Postavimo node na nullptr;
		}
	}
public:
	BinarySearchTree()//Dflt ctor;
	{
		_korijen = nullptr;
	}

	//Metoda za dodavanje nove vrijednosti:
	bool Dodaj(int x)
	{
		return RekurzijaDodaj(_korijen, x);//Pozovemo rekurziju za dodavanje od  pocetnog korijena, te vratimo true ili false shodno tome da li je uspjesno dodano ili ne;
	}

	//Metoda koja uklanja vrijednost iz drva:
	bool Ukloni() 
	{
		return true;
		//Metoda jos nije implementirana jer ne radimo sa nizom vec sa pokazivacima u memoriji;
	}

	//Metoda koja trazi po proslijedjenoj vrijednosti:
	BTCvor<int>* Trazi(int x) 
	{
		return RekurzijaTrazi(_korijen, x);//Trazimo od korijena prema dole;
	}
		
	~BinarySearchTree()//Destruktor;
	{
		RekurzijaRecikliraj(_korijen);//Dealociramo od korijena, ali zapravo idemo rekurzivno odozdo prema gore, kako bi se node-ovi bez djece (listovi) prvi dealocirali;
	}
};