#pragma once//Sluzi da kaze kompajleru da je okej ako se ovaj header pojavi vise puta u istom fajlu;Inace to nije moguce;
#include "Red.h"//Ukljucimo header file red jer cemo koristiti Red klasu kao baznu;
#include <iostream>//Radi exceptiona;
using namespace std;//Radi exceptiona;
typedef int Tip;

//Kreiranje klase sekvencijalnog Reda (Queue-a), koji ce koristiti niz;
class RedSekvencijalno:public Red//Bazna klasa postaje Red;
{
private:
	//Clanovi (atributi) ove klase:

	int _max=5;//Max  broj clanova reda;
	int* _array=new  int [_max];//Red (Queue);
	int _brojac=0;//Brojac trenutnih elemenata u redu;
	int _pocetak=0;//Brojac gdje se nalazi pocetak;//Uklanjamo sa pocetka;
	int _kraj=0;//Brojac gdje se nalazi kraj;//Dodajemo na kraj;

	//Metoda koja ce prosiriti red:
	void prosiriRed()
	{
		int * noviRed=new int[_max+10];//Alociramo novi red;
		_max+=10;//Povecamo vrijednost max;

		//Prekopiramo vrijednosti:

		int pozicija=_pocetak;//Indeks starog reda postavimo na _pocetak;
		for (int i = 0; i < _brojac; i++)//Vrtimo for petlju onoliko koliko imamo trenutnih elemenata;
		{
			noviRed[i]=_array[pozicija];
			pozicija++;//Povecamo indeks;
			if(pozicija==_max)//Ako se dostigne max velicina reda
				pozicija=0;//stavi indeks starog na 0,da pocne sa pocetka opet (0);
		}
		delete[]_array;//Pobrisemo stari red;
		_array=noviRed;//Stari red sada postaje novi (prosireni);
		_kraj=_brojac;//Kraj je sada na trenutnom broju elemenata, kako bi se dodavanje moglo nastaviti;
	}


public:
	//Kako ova klasa ne bi postala abstraktna moramo implementirati sve ciste virtualne metode iz klase Red:

	//Kljucnu rijec virtual mozemo a i ne moramo stavljati, jer se podrazumijeva iz bazne da smo to naslijedili;
	//Override takodjer, mozemo a i ne moramo stavljati;

	void Dodaj(Tip v) override
	{
		if(_brojac==_max)//Ne mozemo koristiti isEmpty() jer nam ona pokazuje kad je red prazan, a ovako znamo kad je red pun;
			prosiriRed();//Prosirimo red kako bi stalo vise clanova;//Takojer se moze baciti npr exception ukoliko ne zelimo siriti red;
		_array[_kraj]=v;//Na kraj se dodaje novi element;
		_kraj++;//Povecavamo kraj jer je sada za jedan vise elemenata u redu;

		if(_kraj==_max)//Ako se dodje do kraja reda
			_kraj=0;//Pocni ispocetka;
		_brojac++;//Jer smo dodali jedan element;
	}
	Tip Ukloni()override
	{
		if(isEmpty())
			throw  exception("Doslo je do greske! Red je PRAZAN");

		const auto v=_array[_pocetak];//Uzmemo vrijednost elementa koji uklanjamo;//Moze biti const jer se ne mjenja nigdje;
		_pocetak++;//Pocetak se pomjera za jedan;//Jer je jedan element upravo uklonjen;
		if(_pocetak==_max)//Ako pocetak postane jednak max granici reda:
			_pocetak=0;//Stavi pocetak da je na nuli,i neka se odatle pocnu uklanjati;
		_brojac--;//Smanjimo overall brojac elemenata jer smo uklonili jedan element iz reda;

		return v;//Vratimo vrijednost elementa koji smo uklonili;
	}
	bool isEmpty()override
	{
		return (_brojac==0);
		//Ili:
		//return (_pocetak==_kraj);
	}

	//Konvencije radi:
	RedSekvencijalno()=default;
	virtual~RedSekvencijalno()override=default;

	//Metoda za ispis:
	void Print()const
	{
		int pozicija=_pocetak;//Napravimo indeks koji pocinje od pocetka;
		for (int i = 0; i < _brojac; i++)//Izvrsava se onoliko puta koliko imamo trenutno elemenata u redu;
		{
			cout<<_array[pozicija]<<endl;//Ispisemo clan;
			pozicija++;//Povecamo indeks;
			if(pozicija==_max)//Ako se dostigne max velicina reda
				pozicija=0;//stavi indeks  na 0, u sustini kreni sa nule da ispisujes ostatke clanova;
		}
	}
};