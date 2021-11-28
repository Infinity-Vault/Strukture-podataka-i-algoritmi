#include <iostream>
using namespace std;


void main()
{
	const int size=10;//Konstanta jer se ne mjenja tokom programa;
	int * Array=new int [size]{4,6,2,8,12,23,34,6,8,90};
	 
	//Selection sort funkcionise na nacin da se nadje minimum u datom nizu (ako se sortira uzlazno)
	//ili maximum (ako se sortira silazno) te se onda svi elementi porede sa njim i iteracijom redaju po silaznom/uzlaznom redosljedu;

	int element;//Varijabla koja ce cuvati poziciju (indeks) elementa koji se treba zamijeniti;

	for (int i = 0; i < size-1; i++)
	{
		element=i;//Ulazimo sa predpostavkom da je najmanji/najveci element na indeksu i;

		for (int j = i+1; j < size; j++)//J pocinje  od indeksa i + 1 jer je taj element necemo porediti, on je vec najmanji/najveci;
		{
			if(Array[j]<Array[element])//Pitamo da li je el. na indeksu j manji (ili veci) od elementa na indeksu 'element';
				element=j;//Ako jeste onda je na tom indeksu j najmanji (ili najveci) element, stoga spremimo taj indeks;
		}
		if(element!=i)//Samo onda ako su indeks 'element' i indeks i  razliciti vrsimo zamjenu, jer ako su isti znaci da ne treba mijenjati nista na korektnim su pozicijama vec;
		{
			int temp=Array[element];//Temp postane manji (ili veci) element;
			Array[element]=Array[i];//Manji  (ili veci) element postane naredni (zamjeni se);
			Array[i]=temp;//Naredni postanje manji  (ili veci);
		}
	}

	//Ispis:
	for (int i = 0; i < size; i++)
		cout<<Array[i]<<",";
	cout<<endl;


	cin.get();
}