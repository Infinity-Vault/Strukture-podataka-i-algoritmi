#pragma once

typedef int Tip;//Definisanja tipa int;
//Kreiranje abstraktne klase  Heap:
class Heap
{
public:

	//Ciste virtualne metode:
	virtual void Dodaj(Tip x)=0;
	virtual Tip Ukloni()=0;
	virtual bool IsEmpty()=0;



	//Konvecnije radi:
	Heap()=default;
	virtual ~Heap()=default;//Mora biti virtual jer klasa ima minimalno jednu virtualnu metodu;
};