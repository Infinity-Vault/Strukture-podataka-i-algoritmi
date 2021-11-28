#include <iostream>
using namespace std;

int velicina=10;//Konstanta jer se ne mjenja tokom programa;
//Globalni pocetni niz koji nije sortiran:
int * NeSortiraniNiz=new int [velicina]{4,6,2,8,12,23,34,6,8,90};
//Globalni niz koji ce na kraju biti sortiran:
int* SortiraniNiz=new int [velicina];

void PrepoloviNizove(int, int);
void main ()
{
	//Logika kod Merge sort algoritma je sljedeca:
	//Dati niz se podijeli na najmanje komadice moguce (nizove od po jedan element) te
	//se onda sortira odozdo prema gore spajanjem dva niza;

	PrepoloviNizove(0,velicina);

	//Ispis:
	for (int i = 0; i < velicina; i++)
		cout<<SortiraniNiz[i]<<",";
	cout<<endl;

	cin.get();
}

//Funkcija koja ce da Sortira dva prepolovljena niza te da time kreira jedan cijeli sortirani (finalni) niz:
void MergeSort(int pocetakPrvogNiza,int PocetakDrugogNiza,int vPrvogNiza,int vDrugogNiza)
{
	int i=pocetakPrvogNiza,j=PocetakDrugogNiza;//Kreiramo brojace i postavimo ih na pocetne pozicije;
	int k=pocetakPrvogNiza;//Brojac k koristimo za indeksiranje novog Sortiranog niza,i postavimo ga na pocetak prvog niza;

	//Kada saberemo velicinu prvog niza sa njegovim pocetkom dobicemo duzinu tog niza;
	//Isto vazi i za drugi niz;
	while(i<pocetakPrvogNiza+vPrvogNiza && j<PocetakDrugogNiza+vDrugogNiza)//Logika ista kao i u for petlji, izvrsava se sve do kraja niza;
	{
		if(NeSortiraniNiz[i]<NeSortiraniNiz[j])//Ako je element prvog niza manji (ili veci) od elementa drugog niza;
		{
			SortiraniNiz[k]=NeSortiraniNiz[i];//U sortirani niz stavi manji tj. el. prvog niza;
			i++;//Povecaj brojac radi iteriranja;
		}
		else//Ako se if ne izvrsi, znaci da je element drugog niza manji (ili veci) od prvog;
		{
			SortiraniNiz[k]=NeSortiraniNiz[j];//U sortirani niz stavi manji tj. el. drugog niza;
			j++;//Povecaj brojac radi iteriranja;
		}
		k++;//Brojac k uvecavamo u oba slucaja, radi iteriranja sortiranog niza;
	}
	//Nakon sto se ova petlja gore izvrsila, postoji mogucnost da je jedan ili drugi niz duzi pa moramo
	//i te elemente prebaciti u novi sortirani niz;

	//Slucaj da je prvi niz duzi:
	while(i<pocetakPrvogNiza+vPrvogNiza)//Isto kao i for petlja;
	{
		SortiraniNiz[k]=NeSortiraniNiz[i];//Stavimo elemente iz prvog niza;
		i++;//Povecamo brojace;
		k++;
	}
	//Slucaj da je drugi niz duzi:
	while(j<PocetakDrugogNiza+vDrugogNiza)//Isto kao i for petlja;
	{
		SortiraniNiz[k]=NeSortiraniNiz[j];//Stavimo elemente iz drugog niza;
		j++;//Povecamo brojace;
		k++;
	}

	//U obje petlje gore apsolutno nije potrebno da provjeravamo koji element je veci (manji)
	//Jer su oni vec u prvoj while sortirani kako treba, zato sto ona ide do duzina oba niza i sortira ih;

	//Ostaje jos samo da se novi niz spoji:
	for (int z = pocetakPrvogNiza; z < pocetakPrvogNiza+vPrvogNiza+vDrugogNiza; z++)//Velicina sortiranog niza je pocetak prvog niza sabran sa velicinama prvog i drugog niza;
	{
		SortiraniNiz[z]=NeSortiraniNiz[z];//Niz je ovdje konacno sortiran;Oba niza su spojena u jedan;
	}
}

//Rekurzivna funkcija koja ce da od izvornog niza napravi dva:
void PrepoloviNizove(int pocetakNiza,int velicinaNiza)
{
	//Bazni slucaj rekurzije jeste ako je velicina niza 1, jer onda se ne moze dijeliti na manje pod nizove;	
	if(velicinaNiza==1)
		return;

	//Kada se prica o tome da se jedan niz prepolovi, mi ne kreiramo dva zasebna nova niza,niti ih negdje premjestamo ili alociramo;
	//Mi samo od postojeceg niza varijablama napravimo dva nova pocetka i kraja;

	//Kreiranje lijevog podniza:
	int pocetakPrvogNiza=pocetakNiza;//Pocetak lijevog niza je ulazni param pocetak niza;
	int vPrvogNiza=velicinaNiza/2;//Ako je niz pocetni velicine 10, v lijevog ce biti 10/2=5;

	//Kreiranje desnog  podniza;
	int pocetakDrugogNiza=pocetakPrvogNiza+vPrvogNiza;//Pocetak drugog niza je kraj prvog;
	int vDrugogNiza=velicinaNiza-vPrvogNiza;//Velicina drugog niza jeste velicina pocetnog - velicina prvog;

	//Rekurzivni pozivi za sljedece pod nizove:
	PrepoloviNizove(pocetakPrvogNiza,vPrvogNiza);
	PrepoloviNizove(pocetakDrugogNiza,vDrugogNiza);
	//Poziv spajanja pod nizova:
	MergeSort(pocetakPrvogNiza,pocetakDrugogNiza,vPrvogNiza,vDrugogNiza);
}