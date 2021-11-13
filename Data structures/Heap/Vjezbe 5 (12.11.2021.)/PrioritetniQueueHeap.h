#pragma once
#include <iostream>//Radi exceptiona;
using namespace std;//Radi exceptiona;
#include "Heap.h"//Radi nasljedjivanja bazne klase;

//Kreiranje Queue koji radi pomocu maksimalnog Heap kompletnog binarnog stabla;
//Binarno stablo je kompletno ako ima listove na jednom ili na dva susjedna nivoa i
//ako u posljednom nivou svi listovi su grupisani lijevo onoliko koliko je to  maksimalno moguce;
//Maksimalno Heap stablo je ono stablo cija su djeca uvijek manje od roditelja (po vrijednoscu);

class PrioritetniQueueHeap:public Heap//Naslijedimo baznu klasu;
{
private:
	int _max=100;//Max broj elemenata u redu;
	int _brojac=0;//Brojac trenutnih elemenata reda;
	Tip* _array=new Tip[_max+1];//Niz (red) tipa Tip (Tip je naslijedjen fajlom  Heap.h);
						//_max+1 jer nam treba alociran niz sa jednim viska elementom;Imamo prazninu na pocetku;Heap je one base indeksiran niz a ne zero base;

	//Metoda koja ce da rotira dva noda:
	void RotirajNodove(int prvi,int drugi)
	{
		int temp=_array[prvi];//Kreiramo pomocnu varijablu;
		_array[prvi]=_array[drugi];//Prvi postane drugi;
		_array[drugi]=temp;//Drugi postane prvi;
	}
	//Metoda koja rekonstruise heap odozgo prema dole da ponovno bude maximalni:
	void RekonstrukcijaStablaPremaDole(int indeks)
	{
		//Bazni slucaj:
		if(2*indeks>_brojac)//Sa 2*indeks dobijemo lijevo dijete, ako je ono vece od brojaca znaci da smo prosli kroz citavo stablo te treba rekurziju zaustaviti;
			return;

		//Kreiramo lijevi i desni node (dijete);
		int lijevoDijete=2*indeks;
		int desnoDijete=lijevoDijete+1;//Ili lijevoDijete+1;Isto je;
		//Kreiramo poziciju (roditelja) sa kojim izmjena treba biti izvrsena;
		int zamjeniSa=indeks;
		
		if(_array[lijevoDijete]>_array[zamjeniSa])//Ako je lijevi node (dijete) veci od roditelja zamjeni roditelja sa lijevim djetetom;
		{
			zamjeniSa=lijevoDijete;//Kako bi se zamjenilo lijevo dijete i ulazni node (indeks);
		}
		if(desnoDijete<=_brojac && _array[desnoDijete]>_array[zamjeniSa])//Ako je desno dijete vece od roditelja zamjeni roditelja i desno dijete;
			//Desno dijete mora biti manje od brojaca jer u suprotnom ako je vece izlazimo van ranga stabla;Taj node ne moze postojati;
		{
			zamjeniSa=desnoDijete;//Kako bi se zamjenilo desno dijete i ulazni node (indeks);
		}

		//Samo ako je doslo do promjene node-a sa kojim se treba zamjeniti u jednom od gore dva if-a, samo tada mjenjamo nodove;
		//U suprotnom desni i lijevi node su jednaki;
		if(zamjeniSa!=indeks)
		{
			RotirajNodove(indeks,zamjeniSa);//Swap se desi indeksa (ulaznog nod-a) i onog skim se treba zamjeniti (desni ili lijevi node);
			RekonstrukcijaStablaPremaDole(zamjeniSa);//pozovemo rekurziju za novi node (za onaj trenutno veci node desni ili lijevi);
		}
	}
	//Metoda koja rekonstruise heap odozdo prema gore:
    void RekonstrukcijaStablaPremaGore(int indeks)
	{
		//Bazni slucaj:
		if(indeks==1)//Bazni slucaj jeste ako se dodje do korijena tu se staje sa rekurzijom;
			return;
		//Kreiranje roditelja:
		int roditelj=indeks/2;//Radi se o cjelobrojnom djeljenju pa stoga nema nikada ostatka;

		if(_array[indeks]>_array[roditelj])//Ako je trenutni node na poziciji 'indeks' veci od onog na poziciji 'roditelja' tj. ako je dijete vece od roditelja, zamjeni ih (rotiraj ih);
		{
			RotirajNodove(indeks,roditelj);//Rotiramo dva noda;
			RekonstrukcijaStablaPremaGore(roditelj);//Pozovemo rekurziju za roditelja;
		}
	}
public:
	//Metode koje treba override-ati:

	//Metoda koja ce da doda element u niz:
	void Dodaj(Tip x) override
	{
		_brojac++;//Prvo povecamo brojac jer brojac je pozicija zadnjeg elementa, stoga ne mozemo tu staviti novi element (samo bi prepisali preko njega) vec stavljamo  za jednu poziciju unaprijed;
		_array[_brojac]=x;//Onda na zadnju slobodnu poziciju dodamo novi element;
		//Pozovemo rekonstrukciju koja ce osigurati da je heap maximalni i rekonstrukciju pocinje od pozicije na kojoj je posljedji element upravo dodan prema korijenu;
		RekonstrukcijaStablaPremaGore(_brojac);
	}
	//Metoda koja ce da ukloni element sa vrha (radimo sa maximalnim heapom sto znaci da je najveci element uvijek na vrhu);
	Tip Ukloni() override
	{
		if(IsEmpty())
			throw exception("Nema elemenata u redu!");
		int uklonjeni=_array[1];//Uklanjamo sa vrha (najveci element);
		_array[1]=_array[_brojac];//Prvi postane onaj koji je bio posljedni;
		_brojac--;//Smanjimo brojac jer je uklonjen jedan element;
		RekonstrukcijaStablaPremaDole(1);//Poziv metode koja ce izvrsiri rekonstrukciju na nacin da red opet zadovolji uslov max heap-a;
		return uklonjeni;//Vratimo vrijednost;
	}
	//Metoda koja provjeri da li je red prazan;
	bool IsEmpty() override
	{
		return _brojac==0;
	}


	//Konvencije radi:
	PrioritetniQueueHeap()=default;
	~PrioritetniQueueHeap()override=default;//Override jer override-amo destruktor iz bazne klase;
};