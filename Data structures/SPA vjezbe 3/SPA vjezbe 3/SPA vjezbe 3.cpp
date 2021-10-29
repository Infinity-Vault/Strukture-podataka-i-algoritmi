#include <iostream>
#include "RedSekvencijalno.h"//Nema potrebe da ukljucujemo header Red, jer je on bazna klasa ovoj, stoga je vec ukljucena tamo gdje je definisana ova klasa;
#include "RedLinked.h"//Nema potrebe da ukljucujemo header Red, jer je on bazna klasa ovoj, stoga je vec ukljucen tamo gdje je definisana ova klasa;
using namespace std;


//Testna fija:
void test(Red& r)
{
	for (int i = 0; i <20; i++)
	{
		r.Dodaj(i);//Dodamo na kraj 20;
	}
	for (int i = 0; i < 5; i++)
	{
		r.Ukloni();//Uklonimo sa pocetka 5;
	}

	const auto ispis= dynamic_cast <RedSekvencijalno*>(&r);//Polimorfizmom castamo varijablu r u ptr tipa RedSekvencijalno kako bi imali metodu Print();
	if(ispis!=nullptr)
		ispis->Print();
	else
	{
	    const auto ispis= dynamic_cast <RedLinked*>(&r);//Polimorfizmom castamo varijablu r u ptr tipa RedLinked kako bi imali metodu Print();
		ispis->Print();
	}
}

void main ()
{
	
	try
	{
		RedSekvencijalno sekvencijalniRed;//Kreiramo sekv. red;
		cout<<"SEKVENCIJALNI RED:"<<endl;
	    test(sekvencijalniRed);//Poziv testa za sekvencijalni red;
	}catch(exception& err)
	{
		cout<<err.what()<<endl;
	}

	try
	{
		RedLinked linkovaniRed;//Kreiramo linkovani red;
		cout<<"LINKOVANI RED:"<<endl;
		test(linkovaniRed);//Poziv testa za linkovani red;
	}catch(exception& err)
	{
		cout<<err.what()<<endl;
	}


	cin.get();
}