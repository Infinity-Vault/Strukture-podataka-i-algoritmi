#pragma once //Sluzi da kaze kompajleru da je okej ako se ovaj header pojavi vise puta u istom fajlu;Inace to nije moguce;

//Kreiranje typdef tipa:
typedef int Tip;

//Kreiranje klase Cvor:
class Cvor
{
public:
	Cvor* _next=nullptr;
	Tip _vrijednost;

	Cvor()//Dflt ctor;
	{
		_next=nullptr;
		_vrijednost=0;
	}
	~Cvor()=default;//Dflt dtor;

	Cvor(Tip v,Cvor* next)//User-def ctor;
	{
		_vrijednost=v;
		_next=next;
	}
};