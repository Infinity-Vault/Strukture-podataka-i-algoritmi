#pragma once//Oznacimo da je moguce da se vise puta ovaj header file negdje importa i to nece predstavljati problem;

//Kreiramo klasu PrioritetniQueue koja ce imati ulogu bazne klase svim ostalim klasama te ce biti sastojana
//od tri ciste virtualne metode, cime se forsira njihova implementacija u izvedenim klasama;


typedef int Tip;//Kreiramo typedef tipa int;

class PrioritetniQueue
{
private:
	

public:
	//Metoda za dodavanje:
	virtual void Dodaj(Tip x)=0;
	//Metoda za uklanjanje:
	virtual Tip Ukloni()=0;
	//Metoda za provjeru jel Queue (Red) prazan:
	virtual bool IsEmpty()=0;

	//Nemamo nista, medjutim radi konvencije mozemo kreirati default ctor i dtor:
	PrioritetniQueue()=default;
	virtual ~PrioritetniQueue()=default;//Mora biti virtual jer je klasa abstraktna;
};
