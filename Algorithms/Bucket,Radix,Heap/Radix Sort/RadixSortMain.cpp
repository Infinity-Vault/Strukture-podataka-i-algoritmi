#include <iostream>
using namespace std;

//RADIX SORT:
//Ovaj algoritam radi na principu da ima tri niza:
//												 -Input array
//												 -Counting array
//											     -Output  array 
//Iz input array-a se uzima broj po broj, kida se zadnja cifra (jedinica),pravi se counting array velicine najvece cifre jedinica,
//te se za svaki broj inkrementuje vrijednost za jedan u counting array-u.
//Potom se radi prefix sum a to jeste da se u counting array-u sabiraju prethodni i naredni clan, samim time zadnji clan uvijek mora biti jednak velicini samog input niza;
//Nakon toga se uzima s desna na lijevo pojedinacni element iz input array-a, pronalazi se indeks njegove jedinice u counting array-u
//i onda se on umanji za jedan (jer je counting array zero based a input one based) i na tu poziciju u output array-u se stavi taj element.
//Rezultat je sortirani niz po cifri jedinica.
//Prekopira  se output u input array, resetuje se output i counting array te se ponovi isto za svaku narednu	 cifru;


//Funkcija koja ce da kreira counting array,uradi prefix sum i da sortira po trenutnoj cifri, te na kraju stavi taj output u input array:
void Sortiraj(int* inputArray, int size, int indexCifre) 
{
	//Counting array je size 10 jer nema vece pojedinacne cifre;
	int* countingArray=new int[10]{0};//Kreiramo counting array inicijalizovan na nule;
	int* outputArray = new int[size];//Lokalni output array koji drzi trenutno sortirane elemente po odredjenoj cifri;

	//Punjenje counting array-a:
	for (int i = 0; i < size; i++)
	{
		int trenutniBroj = inputArray[i];//Pohranimo trenutni broj;
		int trenutnaCifra = (trenutniBroj / indexCifre) % 10;//Uzmemo zadnju cifru broja npr. 123 uzmemo 3;Ali nece uvijek biti zadnja jer indexCifre koji je jedinica desetica ili stotica diktira da li uzimamo prvu,drugu,trecu itd cifru;

		countingArray[trenutnaCifra]++;//Povecamo vrijednost brojaca na poziciji te trenutne cifre;
	}

	//Prefix sum:
	for (int i = 1; i <=9; i++)//Krecemo od jedan jer prvi ostaje isti (sabira se sa 0 pa je uvijek isti,ne mijenja se);
	{
		countingArray[i] += countingArray[i - 1];//Trenutni saberemo sa prethodnim i dodamo ga trenutnom;
	}

	for (int i = size-1; i >=0; i--)//Obrnuta for petlja jer idemo sa kraja;
	{
		int trenutniBroj = inputArray[i];//Zadnji broj jer krecemo s desna na lijevo;
		int trenutnaCifra = (trenutniBroj / indexCifre) % 10;//Uzmemo odgovarajucu cifru (jedinica,desetica,stotica);

		int& pozicijaElementaUOutputArray = countingArray[trenutnaCifra];//Uzmemo poziciju te cifre iz counting array-a;Ova pozicija mora biti referenca na odgovarajuci element u counting array-u, jer kada god se smanji, ta promjena mora biti primjenjiva i u nizu radi daljnih kalkulacija (u suprotnom ne bi radilo korektno sortiranje);
		pozicijaElementaUOutputArray--;//Smanjimo za jedan jer je razlika u bazama nizova;

		outputArray[pozicijaElementaUOutputArray] = trenutniBroj;//Na tu poziciju u output array-u stavimo trenutni broj;
	}

	//Prekopiramo vrijednosti iz ouput array-a u input array:
	for (int i = 0; i < size; i++)
	{
		inputArray[i] = outputArray[i];
	}
}

//Funkcija koja vraca najveci element u nizu:
int GetNajveciELementNiza(int* inputArray, int size) 
{
	int najveciEl = inputArray[0];//Po defaultu uzmemo da je prvi el niza najveci;

	for (int i = 1; i < size; i++)//Prvi el ne poredimo sa samim sobom stoga idemo od i=1;
	{
		if (inputArray[i] > najveciEl)//Ako je trenutni veci od najveceg
			najveciEl = inputArray[i];//Promjeni najveci na trenutni;
	}
	return najveciEl;//Vratimo najveci el niza;
}

//Funkcija koja ce da izvrsi pozive funkcije Sortiraj za sve moguce cifre:
void RadixSort(int* inputArray, int size) 
{
	int najveciELement = GetNajveciELementNiza(inputArray, size);//Dobijemo najveci el niza;
	//Najveci element  u nizu nam je potreban jer sa njime znamo koliko ce cifri najvise biti;

	int indexCifre = 1;//Jer krecemo od jedinica;

	while (najveciELement > 0) 
	{
		Sortiraj(inputArray, size, indexCifre);//Poziv funkcije za prvu cifru;
		indexCifre = indexCifre * 10;//Da bi dobili deseticu,stoticu itd;
		najveciELement /= 10;//Otkinemo zadnju cifru elementu, te time kidamo jednu po jednu cifru, sve dok ne dodjemo do zadnje, odnosno 0;
	}
}
void main() 
{
	int size = 18;
	int* inputArray = new int[size] {5, 9, 4, 8, 353, 2, 5, 9, 7, 55, 10, 98, 44, 11, 87, 98, 14, 66};//Inicijalizujemo array;

	//Poziv Radix sort-a:
	RadixSort(inputArray,size);
	//Ispis:
	for (int i = 0; i < size; i++)
		cout << inputArray[i] << endl;
}