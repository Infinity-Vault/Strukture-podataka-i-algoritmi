#include <iostream>
using namespace std;
void QuickSort(int*, int, int);//Potpis (deklaracija) funkcije;
void main()
{
	const int size=20;//Konstanta jer se ne mjenja tokom programa;
	int * Array=new int [size]{25,14,7,76,10,64,20,30,9,2,6,77,83,12,56,46,61,51,33,26};

	//Quick sort radi na principu odabira pivota (elementa sa cije desne strane moraju biti svi veci elementi)
	// a sa njegove lijeve manji elementi. Za  pivot je najbolje odabrati pocetni clan niza te onda na osnovu njega sortirati niz silazno ili uzlazno;

	QuickSort(Array,0,size-1);//Radi izvrsavanja rekurzije i for petlje saljemo u pozivu size-1 kako ne bi imali prekoracenje niza za jedan element vise;

	for (int i = 0; i < size; i++)
		cout<<Array[i]<<",";
	cout<<endl;


	cin.get();
}

//Funkcija koja zamjeni dva clana u nizu:
void Zamjeni(int* Array,int prvi, int drugi)
{
	int temp=Array[prvi];
	Array[prvi]=Array[drugi];
	Array[drugi]=temp;
}

//Rekurzivna funkcija koja sortira niz:
void QuickSort(int* Array, int pocetak, int kraj)
{
	//Bazni slucaj rekurzije je upravo da se izvrsava sve dok je pocetak manji od kraja.
	//Prvi put kada oni budu jednaki zaustavljamo se jer to znaci da smo iterirali kroz citav niz;
	if(pocetak<kraj)
	{
		int lokacijaPivota=pocetak;//Pivot je prvi  el. niza stoga indeks je pocetak;
		int vrijednostPivota=Array[pocetak];//Vrijednost  je element na lokaciji pocetak;

		for (int i = pocetak+1; i <=kraj; i++)//For krece od drugog elementa niza jer je prvi pivot sa kojim poredimo ostale;
		{
			if(Array[i]<vrijednostPivota)
			{
				lokacijaPivota++;//Uvecamo lokaciju pivota jer ce se dole zamjeniti pa idemo na naredni element u sljedecoj iteraciji;
				Zamjeni(Array,lokacijaPivota,i);//Izvrsimo zamjenu;
			}
		}
		Zamjeni(Array,pocetak,lokacijaPivota);//Sada prije poziva rekurzije i uzimanja novog pivota moramo stari dovesti na njegovu finalnu poziciju;

		//Pozivi rekurzije za desni niz od pivota i lijevi niz od pivota:

		QuickSort(Array,pocetak,lokacijaPivota-1);//Lijevi pod niz;
		QuickSort(Array,lokacijaPivota+1,kraj);//Desni pod niz;
	}
}