#include <iostream>
using namespace std;
void main ()
{
	int size=10;
	int* niz=new int[size]{10,5,6,2,8,7,4,3,1,9};//Kreiramo niz;

	//Prvi nacin: Time complexity: O(n^2);
	//for (int i = 0; i < size-1; i++)//Sortiranje radi kako treba i sa uslovom i<size  medjutim size-1 nam da optimizaciju kako bi se petlja jednom ranije zavrsila jer je zadnjim prolazom sve vec sortirano;
	//{
	//	for (int j = 0; j < size-i-1; j++)//Unutarnja petlja moze ici uvijek za -i-1 jer je element u prijasnjem prolazu kroz petlje sigurno na svom mjestu;
	//	{
	//		if(niz[j]>niz[j+1])//Provjeravamo da li je element na poziciji j veci od narednog;
	//		{
	//			//Uslovom nalazemo da li ce biti sortirano uzlazno > ili silazno <;
	//			//Ako jeste vrsimo zamjenu:
	//			int temp=niz[j];//Stavimo prvi u temp;
	//			niz[j]=niz[j+1];//Prvi postane drugi;
	//			niz[j+1]=temp;//Drugi postane prvi;
	//		}
	//	}
	//}
	//Ispis niza:
	for (int i = 0; i < size; i++)
		cout<<niz[i]<<",";
	cout<<endl;

	//Drugi nacin: Time complexity: O(n^2);
	bool zamjena=true;//Postavimo inicijalno na true kako bi se while prvi put izvrsio;
	while(zamjena)
	{
		zamjena=false;//Prije petlje postavimo na false, jer prvi put kad se ne izvrsi zamjena treba se stati;
		for (int i = 0; i < size-1; i++)//Idemo do velicina-1 jer je zadnji prolaz vec sortiran;
		{
			if(niz[i]>niz[i+1])//Provjeravamo da li je element na poziciji i veci od narednog;
			{
				//Ako jeste zamjeni ih;
				int temp=niz[i];
				niz[i]=niz[i+1];
				niz[i+1]=temp;
				zamjena=true;//Postavi na true kako bi se indiciralo da je zamjena uradjena te da while treba opet da se izvrsi;
			}
		}
	}
	//Ispis niza:
	for (int i = 0; i < size; i++)
		cout<<niz[i]<<",";
	cout<<endl;
	cin.get();
}