#include <iostream>
#include "PrioritetniQueueSekvencijalni.h"//Kako bi mogli koristiti klasu;
#include "PrioritetniQueue.h"//Kako bi imali baznu klasu;
#include "PrioritetniQueuePovezani.h"//Kako bi mogli koristiti klasu;
using namespace std;



//Funkcija koja ce generisati random br:
int GetRandomBroj()
{
	return rand()%100+1;
}
void Testiranje(PrioritetniQueue& R)
{
	srand(time(0));//Ceed-amo rand kako ne bi imali slicne vrijednosti;
	for (int i = 0; i < 20; i++)
	{
	   int x=GetRandomBroj();
	   cout<<"Dodavanje elementa "<<x<<" u niz"<<endl;
	   R.Dodaj(x);
	}

	for (int i = 0; i < 21; i++)
	{
		cout<<"Uklanjanje elementa "<<R.Ukloni()<<endl;
	}
}
void main ()
{
	//Testiranje sekvencijalnog nacina:
	cout<<"------------------------PRIORITETNI RED SEKVENCIJALNO:------------------------"<<endl;
	try
	{
		PrioritetniQueueSekvencijalni red;
		Testiranje(red);
	}
	catch (const exception& err)
	{
		cout<<err.what()<<endl;
	}
	//Testiranje povezanog nacina:
	cout<<"------------------------PRIORITETNI RED POVEZANO:------------------------"<<endl;
	try
	{
		PrioritetniQueuePovezani red;
		Testiranje(red);
	}
	catch (const exception& err)
	{
		cout<<err.what()<<endl;
	}
}
