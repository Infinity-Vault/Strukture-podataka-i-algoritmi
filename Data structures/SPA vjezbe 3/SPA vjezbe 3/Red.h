#pragma once//Sluzi da kaze kompajleru da je okej ako se ovaj header pojavi vise puta u istom fajlu;Inace to nije moguce;

typedef int Tip;//Mozemo ili definisati tip ovdje ili ga naslijediti iz klase Cvor (tako sto ukljucimo header Cvor);

//Kreiranje klase Red, treba da ima funkcionalnosti Queue-a:
class Red
{
public:
	//Kreiracemo tri ciste virtualne metode koje ce ovu klasu napraviti abstraktnom;
	//U redu se dodaje na kraj a uzima (uklanja) sa pocetka;
	virtual void Dodaj(Tip x )=0;//Metoda za dodaj na kraj;
	virtual Tip Ukloni()=0;//Metoda za ukloni sa pocetka;
	virtual bool isEmpty()=0;//Metoda za provjeru jel prazan red;


	//Konvencije radi:
	Red()=default;
	virtual ~Red()=default;
};