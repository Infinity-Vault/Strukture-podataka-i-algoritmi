#pragma once
#include <iostream>
using namespace std;

//Kreiramo klasu BTCvor (Binary Tree cvor):
template<class T>//Klasu kreiramo kao genericku, da bi _info polje moglo biti tipa T;
class BTCvor 
{
public:
	BTCvor* _desnoDijete;//Pokazivac na desno dijete;
	BTCvor* _lijevoDijete;//Pokazivac na lijevo dijete;
	T _info;//Varijabla koja cuva vrijednost tipa T;

	BTCvor()//Dflt ctor;
	{
		_desnoDijete = nullptr;
		_lijevoDijete = nullptr;
	}
	BTCvor(T info)//User-def ctor;
	{
		_desnoDijete = nullptr;
		_lijevoDijete = nullptr;
		_info = info;
	}
	~BTCvor() = default;//Defaultni destruktor;
};
//Operator ispisa:
ostream& operator << (ostream& out, const BTCvor<int>& node) 
{
	out << node._info;//Ispisemo info polje (vrijednost);
	return out;//Vratimo napunjen ostream objekat;
}