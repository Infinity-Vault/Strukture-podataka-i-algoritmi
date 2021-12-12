#include <iostream>
using namespace std;


//Funkcija koja ce da radi rekonstrukciju heap-a prema dole:
void RekonstruisiPremaDole(int array[], int n, int indeks)
{
	int najveci = indeks;//Onaj sa kojim se mijenja node (korijen);
	int lijevoDijete = 2 * indeks + 1;//Posto indeksiranje pocinje sada od nula  za razliku od prijasnjeg Heap gdje je bilo jedan;
	int desnoDijete = 2 * indeks + 2;

	//lijevoDijete<n je uslov da ne prekoracimo granice Heap-a;
	if (lijevoDijete<n && array[lijevoDijete] > array[najveci])//Poredimo korijen i lijevi node;
		najveci = lijevoDijete;
	//desnoDijete<n je uslov da ne prekoracimo granice Heap-a;
	if (desnoDijete<n && array[desnoDijete] > array[najveci])//Poredimo korijen i desni node;
		najveci = desnoDijete;
	//Samo ako je najveci != od indeks (pocetnog korijena), onda vrsi zamjenu i rekurzivni poziv;
	//Nema smisla da rotiramo korijen sa samim sobom;
	if (najveci != indeks) 
	{
		swap(array[indeks], array[najveci]);
		RekonstruisiPremaDole(array, n, najveci);
	}
	
}
//Funkcija koja ce da izvrsi sami heap sort:
void HeapSort(int array[], int n)
{
	for (int i = n/2-1; i >=0; i--)//Pocinjemo od n/2-1 kako bi dobili root krajnjeg desnog stabla;
	{
		RekonstruisiPremaDole(array, n, i);//Radimo rekonstrukciju heap-a;
	}

	for (int i = n-1; i >=0; i--)//Krenemo sa desna na lijevo;
	{
		swap(array[0], array[i]);//Zamjeni prvi i zadnji;Prvi je sada najveci stoga ide na zadnju poziciju;
		n--;//Smanjimo velicinu niza (heap-a) jer se zadnji element sada vise ne dira, stoga gledamo niz kao da je smanjen;
		RekonstruisiPremaDole(array, n, 0);//Pozovemo rekonstrukciju sa smanjenom velicinom, i indeksom 0 jer opet zelimo da napravimo da je na vrhu (korijenu) heap-a najveci el;
	}
}
void main() 
{
	int n = 6;
	int* array = new int[]{12, 11, 13, 5, 6, 7};//Inicijalizujemo array;
	
	HeapSort(array, n);
	for (int i = 0; i < n; i++)
		cout << array[i] << endl;	
}
