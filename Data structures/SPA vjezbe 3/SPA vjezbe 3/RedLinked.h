#pragma once//Sluzi da kaze kompajleru da je okej ako se ovaj header pojavi vise puta u istom fajlu;Inace to nije moguce;
#include <iostream>//Radi exception;
#include "Cvor.h"//Radi Cvor i Tip;
#include "Red.h"//Radi bazne klase;
using namespace std;//Radi exception;

//Definisanje klase red linked listom (Linked Queue):
class RedLinked: public Red//Naslijedimo baznu klasu;
{
private:
	//Clanovi (atributi) klase:
	Cvor* _head=nullptr;//Glava (pocetni ptr/element);
	Cvor* _end=nullptr;//Kraj (zadnji ptr/element);
	int _brojac=0;//Overall brojac trenutnih  elemenata u nizu;
	
	
public:
	//Implementacija svih virtualnih metoda kako klasa ne bi postala abstraktna:
	void Dodaj(Tip v)override
	{
		//Kreiranje novog el. za dodat:
		auto noviZaDodati=new Cvor(v,nullptr);//Atribut _next ovog cvora postaje nullptr, jer cemo ga dodati na kraj stoga ce on biti zadnji;

		if(!isEmpty())//Ako red nije  prazan (ima bar jedan element)
		{
			_end->_next=noviZaDodati;//Zadnji clan, prije nego sto se izvrsi linija 27, je ustvari predzadnji.Stoga njegov next stavimo da pokazuje na zadnji (sada dodani);
			_end=noviZaDodati;//Onda zadnji clan stavimo da bude nas ovaj novo-dodani;
		}
		else//U slucaju da je red prazan;
		{
			//Onda i pocetak i kraj su isti element;
			_head=noviZaDodati;
			_end=noviZaDodati;
		}
		_brojac++;//Jer je dodan element;
	}
	Tip Ukloni()override
	{
		if(isEmpty())
			throw exception("Doslo je do greske! Red je PRAZAN");
		//Ili:
		//if (_head==nullptr)
		//	throw exception("Doslo je do greske! Red je PRAZAN");

		//Ili:
		//if(_brojac==0)
		//	throw exception("Doslo je do greske! Red je PRAZAN");

		auto ukloni=_head;//Pomocni ptr koji pokazuje na prvi element reda koji trebamo ukloniti;
		const auto v=_head->_vrijednost;//Pomocna varijabla da cuva njegovu vrijednost koja ce se vratiti;
		_head=_head->_next;//Pomjeranje da head pokazuje sada na prvi ponovno;//Jer smo prvi uklonili;

		if(_head==nullptr)//Ako je head nullptr (tj ako je red prazan)
			_end=nullptr;//onda je i kraj prazan;Nema na sta pokazivati;

		delete ukloni;//Obrisemo clan sa pocetka reda;
		_brojac--;//Smanjimo brojac jer je izbrisan jedan element;
		return v;
	}
	bool isEmpty()override
	{
		return _head==nullptr;
		////Ili:
		//return _end==nullptr;
		////Ili:
		//return _brojac==0;
	}


	//Konvecije radi:
	RedLinked()=default;
	~RedLinked()override=default;

	//Metoda za ispis:
	void Print()const
	{
		auto ispis=_head;//Kreiramo pomocni ptr koji postavimo na prvi clan;
		for (int i = 0; i < _brojac; i++)//Vrti se za _brojac puta;
		{
			if(ispis!=nullptr)//Bice nullptr samo kada dostigne zadnji clan;
			{
			  cout<<ispis->_vrijednost<<endl;
			  ispis=ispis->_next;//Pokazuje na sljedeci;
			}
		}
	}
};