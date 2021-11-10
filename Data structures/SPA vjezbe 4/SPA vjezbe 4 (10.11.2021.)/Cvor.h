#pragma once

typedef int Tip;//Definisemo int typedef;

//Kreiramo klasu Cvor:
class Cvor
{
public:
	Cvor* _next;
	Tip _vrijednost;

	Cvor()//Dflt ctor;
	{
		_next=nullptr;
		_vrijednost=0;
	}

	Cvor(Tip vrijednost,Cvor* next)//User-def ctor;
	{
		_next=next;
		_vrijednost=vrijednost;
	}

	~Cvor()=default;//Dtor;	
};
