#include <iostream>
using namespace std;
void  main ()
{
	int size=10;

	int* niz=new int [size]{10,5,6,2,8,7,4,3,1,9};

	//Insertion sort radi na principu da se prvi element postavi kao sortiran, te da se onda prodje kroz sve ostale
	// "ne sortirane" elemente i provjeri da li je trenutni manji od prijasnjeg i ako jeste zamjene se;

	//Prvi nacin: Time complexity: O(n^2);
	//int trenutniElement,j;
	//for (int i = 1; i < size; i++)//Krecemo od 1 jer to je prvi "ne sortirani" element;
	//{
	//	trenutniElement=niz[i];//Uzmemo trenutni "ne sortirani" clan (element);
	//	j=i-1;//Brojac j postane ustvari prijasnji clan;
	//
	//	while(j>=0 && niz[j]>trenutniElement)//Sve dok je j>=0 i prijasnji clan veci od trenutnog;
	//	{
	//		niz[j+1]=niz[j];//Zamjeni mjesta (veci pomjeri naprijed);
	//		j--;//Brojac j umanjuj za 1 tj uzimaj prethodne elemente ako ih ima (zato imamo uslov j>= 0 za onda kada on postane negativan);
	//	}
	//	niz[j+1]=trenutniElement;///Na poziciju j+1 (prvi element) stavi trenutni element (tj onaj koji je najmanji ili najveci u zavisnosti od poredjenja < ili >);
	//}
	//Ispis niza:
	for (int i = 0; i < size; i++)
		cout<<niz[i]<<",";
	cout<<endl;


	//Drugi nacin: Time complexity: O(n^2);
	for (int i = 1; i < size; i++)//Krecemo od 1 jer je to prvi "ne sortirani" element;
	{
		int j=i;//J je na istoj poziciji kao i;
		while(j>0 && niz[j-1]>niz[j])//Sve dok je j>0 i prijasnji element veci od trenutnog;
		{
			//Zamjeni elemente;
			int temp=niz[j];//Spasimo trenutni;
			niz[j]=niz[j-1];//trenutni (manji) postanje prijasnji;
			niz[j-1]=temp;//Prijasnji (veci) postane trenutni;
			j--;//Umanjimo brojac kako bi se kretali unazad po nizu;
		}
	}
	//Ispis niza:
	for (int i = 0; i < size; i++)
		cout<<niz[i]<<",";
	cout<<endl;

	cin.get();
}