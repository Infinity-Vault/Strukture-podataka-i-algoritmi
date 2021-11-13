#include <iostream>
#include "PrioritetniQueueHeap.h"//Radi klase koju cemo koristiti;//Pomocu ovoga smo vec ukljucili baznu klasu;
using namespace std;


int GenerisiRandomBroj()
{
	return rand()%100+1;//Opseg 0-100;
}

//Testna funkcija:
void Test(Heap& H)
{
	srand(time(0));//Ceed za randomiziranje brojeva;Da nemamo iste brojeve vec zaista razlicite;

	for (int i = 0; i < 20; i++)
	{
		int x=GenerisiRandomBroj();
		cout<<"Dodan broj: "<< x<<endl;
		H.Dodaj(x);
	}

	for (int i = 0; i < 2; i++)
	{
		cout<<"Uklonjen broj: "<<H.Ukloni()<<endl;
	}
}
void main ()
{
	try
	{
		PrioritetniQueueHeap heap;//Kreiramo objekat ove klase;
		Test(heap);//Testiramo za gornji objekat;
	}
	catch (const exception& err)
	{
		cout<<"Doslo je do greske: "<<err.what()<<endl;
	}
	cin.get();
}