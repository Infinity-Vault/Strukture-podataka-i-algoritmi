#pragma once

#include  <iostream>
using namespace  std;

class Lista
{
public:
	virtual void dodaj_na_pocetak(int x) = 0;

	virtual void dodaj_na_kraj(int x) = 0;

	virtual int ukloni_sa_pocetka() = 0;

	virtual int ukloni_sa_kraja() = 0;

	virtual bool jel_prazna() = 0;

	virtual int operator[](int index) = 0;

	virtual int get_brojac() = 0;
};