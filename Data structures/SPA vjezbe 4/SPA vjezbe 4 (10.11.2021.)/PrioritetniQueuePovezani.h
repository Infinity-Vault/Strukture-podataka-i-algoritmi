#pragma once
#include "Cvor.h"//Radi klase Cvor;
#include "PrioritetniQueue.h"//Radi bazne klase;
#include <iostream>//Radi exceptiona;
using namespace std;//Radi exceptiona;

//Kreiranje klase PrioritetniQueuePovezani:
//Za razliku od sekv. nacina povezani nema nikakvih problema da doda bilo gdje novi element (nije vremenski zahtjevno), stoga se ovdje sortira pri dodavanju a ne pri uklanjanju kao sto je to kod sekvencijalnog nacina;
class PrioritetniQueuePovezani:public PrioritetniQueue
{
private:
	Cvor* _head=nullptr;
	int _brojac=0;
public:
	//Metode koje treba implementirati, koje su nasljedjene iz bazne klase, kako ova klasa ne bi postala abstraktna:

	//Metoda koja ce da sortira elemente i doda na pocetak najveci element;
	void Dodaj(Tip x) override
	{
		Cvor* noviElement=new Cvor(x,nullptr);//Kreiramo novi element sa vrjednoscu x i nullptr za _next, jer ne pokazuje za pocetak ni na koji naredni el;

		if(_head==nullptr)//Znaci da nema nijednog elementa te da je ujedno ovaj koji treba dodati najveci stoga ce biti prvi;
		{
			_head=noviElement;//Dodamo na pocetak el;
			_brojac++;//Povecamo brojac jer smo dodali element;
			return;//Odmah zavrsimo izvrsavanje metode jer je dodan prvi clan;
		}

		Cvor* trenutni=_head;//Za pocetak stavljamo ga na prvi el u redu;
		Cvor* prijeTrenutnog=nullptr;//Za pocetak nullptr;

		//Prvo provjeravamo da li je trenutni !=nullptr kako ne bi doslo do nullptr dereferenciranja i pada programa;
		while (trenutni!=nullptr && trenutni->_vrijednost>x)//Sve dok trenutni nije nullptr (zadnji clan niza) i dok je njegova vrijednost veca od x;
		{
			prijeTrenutnog=trenutni;//Clan prije postane trenutni;
			trenutni=trenutni->_next;//Trenutni postane naredni;
		}

		if(prijeTrenutnog==nullptr)//Ukoliko je slucaj da se while nijednom ne izvrsi,moguce je da je novi element, veci od svih te da ga odmah treba dodati na pocetak;
		{
			_head=noviElement;//Prvi element postaje novi;
			noviElement->_next=trenutni;//Ptr _next novog elementa postaje trenutni, tj naredni u redu;
			_brojac++;//Povecamo brojac jer smo dodali element;
		}
		else//Ako se while izvrsi bar jednom;
		{
			prijeTrenutnog->_next=noviElement;//Prije trenutnog umetnemo novi element jer je veci od trenutnog;
			noviElement->_next=trenutni;//Ptr _next od novog elementa stavimo na trenutni jer je trenutni manji od njega pa dolazi iza njega u redu;
			_brojac++;//Povecamo brojac jer smo dodali element;
		}
	}
	//Metoda koja ukloni prvi clan reda:
	Tip Ukloni() override
	{
		if(IsEmpty())//Provjera da li je prazan niz,kako ne bi bilo nullptr dereferenciranja te pada programa;
			throw exception("Niz je prazan stoga se ne moze ukloniti element!");

		Cvor* ukloni=_head;//Prvi clan reda spremimo u pomocnu var;
		_head=_head->_next;//Pomjerimo da je sada novi prvi clan ustvari naredni u redu;
		Tip povratnaVrijednost=ukloni->_vrijednost;//Uzmemo vrijednost povratnog elementa;
		delete ukloni;//Obrisemo prvi element reda;
		_brojac--;//Dekrementujemo brojac elemenata jer smo jedan uklonili;
		return povratnaVrijednost;
	}
	//Metoda koja kaze da li je red prazan:
	bool IsEmpty() override
	{
		//return _brojac==0;
		//Ili:
		return _head==nullptr;
	}



	//Konvencije radi:
	PrioritetniQueuePovezani()=default;
	~PrioritetniQueuePovezani()override=default;
	
};