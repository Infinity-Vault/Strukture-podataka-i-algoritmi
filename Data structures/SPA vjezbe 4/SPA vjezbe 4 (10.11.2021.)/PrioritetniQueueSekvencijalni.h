#pragma once
#include "PrioritetniQueue.h"//Ukljucimo header file od bazne klase koji nam treba, jer cemo je ovdje naslijediti;
#include <iostream>//Radi exception klase;
using namespace std;//Radi exception klase;
//Postoje opcije da se:
//					1.Sortira pri dodavanju, ne sortira pri uklanjanju (U ovom sluc. se brze ukloni nego sto se doda);
//					2.Sortira pri uklanjanju, ne sortira pri dodavanju (U ovom sluc. se brze doda nego sto se ukloni);

//Kreiramo klasu koja ce sortirati pri uklanjaju jer ona ima bolje izvrsno vrijeme;

class PrioritetniQueueSekvencijalni:public PrioritetniQueue//naslijedimo baznu klasu;
{

private:
	int _max=5;//Max elemenata u nizu;
	int _brojac=0;//Brojac trenutno elemenata;
	Tip* _array=new Tip[_max];//Niz (red) elemenata tipa Tip (Tip smo vec definisali u baznoj klasi);

//Metoda koja ce da prosiri niz:
    void ProsiriNiz()
    {
	    Tip* temp=new Tip[_max+10];//Alociramo novi niz sa deset mjesta vise nego stari;
		_max+=10;//Povecamo max broj elemenata;
		for (int i = 0; i < _brojac; i++)
		{
			temp[i]=_array[i];//Prekopiramo iz starog u novi;
		}
		delete [] _array;//Pobrisemo stari niz;
		_array=temp;//Preusmjerimo stari niz da pokazuje na novi;
    }
public:
	//Metode koje moramo implentirati kako ne bi i ova klasa postala abstraktna:

	//Metoda koja doda novi clan na kraj niza;
	void Dodaj(Tip x) override
	{
		if(_brojac==_max)//Ako je dostignut trenutno max br elemenata
			ProsiriNiz();//Prosiri niz za 10 mjesta;
		_array[_brojac]=x;//Dodamo novi element na kraj;
		_brojac++;//Uvecamo brojac jer je dodan jedan element;
	}
	//Metoda koja treba da ukloni najveci clan (onaj sa najvecim prioritetom);
	Tip Ukloni() override
	{
		if(IsEmpty())
			throw exception("Red je prazan, nema se sta za ukloniti!");
		int najveciElement=_array[0];//Postavimo da je najveci el prvi u nizu;
		int indeksNajvecegElementa=0;//Stavimo da je indeks (pozicija) tog elementa 0;

		for (int i = 1; i < _brojac; i++)//Mozemo staviti za i da pocinje od 1 jer prvi element ne moramo provjeravati, ako se if u petlji nikada ne izvrsi znamo da je najveci el upravo ovaj nas prvi;
		{
			if(_array[i]>najveciElement)//Ispitujemo da li je trenutni clan niza na poziciji i veci od varijable najveciElement;
			{
				najveciElement=_array[i];//Novi najveci el je ovaj trenutni u nizu na poziciji i;
				indeksNajvecegElementa=i;//Uzmemo indeks (poziciju) najveceg el;
			}
		}
		_brojac--;//Smanjimo brojac jer je jedan element uklonjen;
		_array[indeksNajvecegElementa]=_array[_brojac];//Na mjestu najveceg elementa prepisemo preko i stavimo vrijednost od zadnjeg clana;Ovime se najlakse rijesi problem i ne moramo prebacivati elemente za jednu poziciju (svakako se izbacuju sortiranjem);
		return najveciElement;//Vratimo vrijednost najveceg clana;

		//NOTE:
		//Red inace radi po FIFO principu, medjutim ovo je prioritetni red, stoga se ne izbacuje element koji je prvi usao vec onaj koji ima najveci prioritet;
	}
	//Metoda koja provjerava da li je red prazan:
	bool IsEmpty() override
	{
		return _brojac==0;
	}

		

	//Konvencije radi:
	PrioritetniQueueSekvencijalni()=default;//Dflt ctor;
	virtual~PrioritetniQueueSekvencijalni()override=default;//Dflt dtor;
};