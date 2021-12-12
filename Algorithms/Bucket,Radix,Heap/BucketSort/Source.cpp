#include <iostream>
using namespace std;
//Klasa Cvor:
class Cvor
{
public:
	Cvor* _next;
	int _vrijednost;

	Cvor()//Dflt ctor;
	{
		_next = nullptr;
		_vrijednost = 0;
	}

	Cvor(int vrijednost, Cvor* next)//User-def ctor;
	{
		_next = next;
		_vrijednost = vrijednost;
	}

	~Cvor() = default;//Dtor;	
};


//Pravljenje prioritetnog reda povezana varijanta:
class PrioritetniRedPovezani 
{
	Cvor* _head;
	int _brojac = 0;
public:
	PrioritetniRedPovezani()//Dflt ctor;
	{
		_head = nullptr;
		_brojac = 0;
	}
	void Dodaj(int x) 
	{
		Cvor* noviElement = new Cvor(x, nullptr);//Kreiramo novi element sa vrjednoscu x i nullptr za _next, jer ne pokazuje za pocetak ni na koji naredni el;

		if (_head == nullptr)//Znaci da nema nijednog elementa te da je ujedno ovaj koji treba dodati najveci stoga ce biti prvi;
		{
			_head = noviElement;//Dodamo na pocetak el;
			_brojac++;//Povecamo brojac jer smo dodali element;
			return;//Odmah zavrsimo izvrsavanje metode jer je dodan prvi clan;
		}

		Cvor* trenutni = _head;//Za pocetak stavljamo ga na prvi el u redu;
		Cvor* prijeTrenutnog = nullptr;//Za pocetak nullptr;

		//Prvo provjeravamo da li je trenutni !=nullptr kako ne bi doslo do nullptr dereferenciranja i pada programa;
		while (trenutni != nullptr && trenutni->_vrijednost > x)//Sve dok trenutni nije nullptr (zadnji clan niza) i dok je njegova vrijednost veca od x;
		{
			prijeTrenutnog = trenutni;//Clan prije postane trenutni;
			trenutni = trenutni->_next;//Trenutni postane naredni;
		}

		if (prijeTrenutnog == nullptr)//Ukoliko je slucaj da se while nijednom ne izvrsi,moguce je da je novi element, veci od svih te da ga odmah treba dodati na pocetak;
		{
			_head = noviElement;//Prvi element postaje novi;
			noviElement->_next = trenutni;//Ptr _next novog elementa postaje trenutni, tj naredni u redu;
			_brojac++;//Povecamo brojac jer smo dodali element;
		}
		else//Ako se while izvrsi bar jednom;
		{
			prijeTrenutnog->_next = noviElement;//Prije trenutnog umetnemo novi element jer je veci od trenutnog;
			noviElement->_next = trenutni;//Ptr _next od novog elementa stavimo na trenutni jer je trenutni manji od njega pa dolazi iza njega u redu;
			_brojac++;//Povecamo brojac jer smo dodali element;
		}
	}
	int Ukloni() 
	{
		if (_brojac == 0)
			throw exception("Nema elemenata za ukloniti!");
		Cvor* temp = _head;
		_head = _head->_next;
		int x = temp->_vrijednost;
		delete temp;
		_brojac--;
		return x;
	}
	bool IsEmpty() 
	{
		return _brojac == 0;
	}
};

//Funkcija koja vraca najveci element niza:
int GetNajveciElement(int* array, int size) 
{
	int najveci = array[0];
	for (int i = 1; i < size; i++)//Krecemo od jedan jer prvi nema potrebe da poredimo sa samim sobom;
	{
		if (array[i] > najveci)//Ako je trenutni veci;
			najveci = array[i];//Najveci postavi na trenutni;
	}
	return najveci;
}

void BucketSort(int* array, int size) 
{
	PrioritetniRedPovezani* Buckets = new PrioritetniRedPovezani[size];//Kreiramo niz Bucket-a;

	int najveciEl = GetNajveciElement(array, size);//Nadjemo najveci element niza;

	for (int i = 0; i < size; i++)
	{
		int trenutniBroj = array[i];//Uzmemo trenutni broj;
		int indexBrojaUNizu = trenutniBroj * size / (najveciEl + 1);//Formula pomocu koje dobijemo index poziciju u nizu za trenutni broj;
		Buckets[indexBrojaUNizu].Dodaj(trenutniBroj);//Dodamo trenutni broj u bucket;
	}
	int brojac = size - 1;//Krenemo brojati od predzadnjeg clana;
	for (int i = size-1; i >=0; i--)//Idemo do prvog clana, sa kraja;
	{
		PrioritetniRedPovezani& sortiranaLista = Buckets[i];//Pojedinacna lista sortiranih clanova;
		while (!sortiranaLista.IsEmpty())//Sve dok lista nije prazna;
		{
			int clan = sortiranaLista.Ukloni();
			array[brojac] = clan;
			brojac--;
		}
	}
}
void main() 
{
	int size = 18;
	int * array=new int [size] { 5, 9, 4, 8, 353, 2, 5, 9, 7, 55, 10, 98, 44, 11, 87, 98, 14, 66 };

	BucketSort(array, size);

	for (int i = 0; i < size; i++)
		cout << array[i] << "|";
	cout << endl;
}