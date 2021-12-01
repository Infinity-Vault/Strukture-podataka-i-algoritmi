#include  <iostream>
struct Cvor;
using namespace  std;

//Klasa osoba koja ce poslije sluziti samo za testiranje:
class Osoba
{
public:
	int Id;
	string ime;
	Osoba()
	{
		Id=0;
		ime="NOT_SET";
	}
	Osoba(int id, string ime)
	{
		this->ime = ime;
		this->Id = id;
	}
	virtual void info()
	{
		cout << "Ja sam osoba " << ime << endl;
	}
	virtual ~Osoba()//Mora biti virtual dtor jer je klasa bazna;
	{

	}
};
//Klasa student koja nasljedjuje klasu osoba koja ce se takodjer koristiti za testiranje:
class Student : public Osoba
{
public:
	int brojIndeksa;

	Student()
		: Osoba()//Dflt ctor od osobe;
	{
		brojIndeksa=20000;
	}
	Student(int id, string ime, int brojIndeksa) : Osoba(id, ime)
	{
		this->brojIndeksa = brojIndeksa;
	}
	void info() override //Jer override-amo info metodu klase Osoba;
	{
		cout << "Ja sam student " << ime << ". Broj indeksa = " << brojIndeksa << endl;
	}
};
//Definisanje tipa;
typedef int Tip;//typdef moze biti bilo koji primitivni tip podatka (int,char,float itd);
//Isto tako moze biti user def tip podatka ali ide sintaksa:
//typedef Osoba Tip;//typedef imeKlase/Strukture imeTipa (Tip);


//Kreiranje strukture cvor;
struct Cvor
{
	Cvor* next;//Pokazivac koji pokazuje na naredni clan niza;
	Tip info;//Tip podatka (npr int) koji se cuva u tom cvoru;

	//User-def ctor;
	Cvor(Tip info, Cvor* next)
	{
		this->info = info;
		this->next = next;
	}
};



//Ovdje kreiramo apstraktnu klasu Lista. Apstraktna klasa ne moze imati svoju instancu ili objekat,
//medjutim moze imati reference i pokazivace. Cilj ove klase jeste da ona bude bazna klasa klasama
//SeqList i LinkedList; Apstrakcija se nastavlja sve dok se u child klasama ne overrid-aju sve metode koje su
//ciste virtuelne u baznoj klasi List;
class Lista
{
public:

	//Ctor reda radi da imamo;
	Lista() = default;//default kljucna rijec sluzi da okarakterisemo ctor koji nema body;

	virtual void dodaj_na_pocetak(int x) = 0;

	virtual void dodaj_na_kraj(int x) = 0;

	virtual int ukloni_sa_pocetka() = 0;

	virtual int ukloni_sa_kraja() = 0;

	virtual bool jel_prazna() = 0;

	virtual int operator[](int index) = 0;

	virtual int get_trenutno() = 0;

	//Dtor reda radi da imamo;
	virtual ~Lista() =default;////default kljucna rijec sluzi da okarakterisemo dtor koji nema body;
};

//Pravljenje ciste virtualne klase stek:
class Stek
{
public:
	Stek()=default;
	virtual ~Stek()=default;
	virtual void push(int x)=0;
	virtual int  pop()=0;
	virtual bool is_Empty()=0;
};


//Kreiranje sekvencijalnog steka, sve ide jedno iza drugog, sekventno;
class SeqStack:public Stek
{
private:
	int _trenutno=0;
	int _max=5;
	int* _array= new int [_max];
public:
	SeqStack()=default;
	void prosiriStek()
	{
		int size=_max+10;
		int * novi=new int [size];
		for (int i = 0; i < _max; i++)
		{
			novi[i]=_array[i];
		}
		delete[]_array;
		_array=novi;
		_max+=10;
		cout<<"Stari stek velicine: "<< _max-10<<" se prosirio za: "<<_max<<endl;
	}
	virtual void push(int x) override
	{
		if(_trenutno==_max)
			prosiriStek();
		_array[_trenutno]=x;//Stek arhitektura dozvoljava samo da dodajemo na kraj;
		_trenutno++;//Dodali smo jedan el.;
	}
	int pop()override
	{
		if(_trenutno<0 || _trenutno>_max)
			throw exception("Ne validne granice steka  !");
		if(_trenutno==0)
			throw exception("Stek je prazan nema se sta pop-ati !");
		_trenutno--;//Oduzeli smo jedan element;
		return _array[_trenutno];//Stek arhitektura dozvoljava izbacivanje samo sa kraja;
	}
	bool is_Empty() override
	{
		return _trenutno==0;//Vrati true ili false shodno tome da li je stek pun ili prazan;
	}
	virtual ~SeqStack()=default;
};

//Kreiranje linkovanog steka:
class LinkedStack:public Stek
{
private:
	Cvor* _head=nullptr;//Pocetni pokazivac (glava);
    int _trenutno=0;
public:
	void push(int x)override
	{
		Cvor* prvi=new Cvor(x,_head);//Kreiramo novi cvor sa proslijedjenom vrijednoscu  x i pokazivacem na pocetni cvor;s
		_head=prvi;//Pocetni pokazuje na prvi;
		_trenutno++;//Uvecamo brojac;
	}
	int pop()override
	{
		int x=_head->info;//Spasimo vrijednost prijasnjeg clana;
		Cvor* temp=_head;//Napravimo pomocni pokazivac na pocetni cvor;
		_head=_head->next;//Pocetni pokazuje na sljedeci u nizu;
		delete temp;//Unistimo temp jer je to prvi element (onaj koji smo uklonili);
		_trenutno--;//Smanjimo brojac jer smo uklonili element;
		return x;//Vratimo vrijednost;
	}
	bool is_Empty()override
	{
		return _trenutno==0;
	}
};

//Kreiranje sekvencijalne liste;Sve ide jedno iza drugog, sekventno;
class SeqList : public Lista
{
private:
	int _trenutno=0;//Brojac za brojanje trenutnih clanova u nizu;
	int _max=5;//Max za maksimalnu velicinu niza;
	int * _array=new int [_max];

	void prosiriArray()
	{
		int size=_max+10;//Povecamo za 10 mjesta;

		int* novi=new int [size];//Deklarisemo pomocni niz;

		for (int i = 0; i < _max; i++)
		{
			novi[i]=_array[i];//Prekopiramo vrijednosti iz starog u novi;
		}
		delete[] _array;//Pobrisemo stari niz;
		_array=novi;//Stari niz preusmjerimo na novi;

		cout<<"Stari niz velicine "<<_max<<"  sada ima:"<<_max+10<<endl;
		_max+=size;//Povecamo max vel niza;
		//delete[]novi;//Ne smijemo brisati ovaj niz jer _array jos uvijek pokazuje na njega!
	}
public:
	virtual void dodaj_na_pocetak(int x)override//Kljucnu rijec override stavljamo jer prepisujemo baznu metodu;
	//Kljucnu rijec virtual mozemo ali i ne moramo koristiti;Vec se u baznoj zna da je metoda proglasena virtual;
	{
		if(_trenutno==_max)//Ako je dostignuta trenutna max velicina niza, prosiri ga;
			prosiriArray();
		for (int i = _trenutno; i >=1; i--)//Idemo od trenutne pozicije zadnjeg el. pa sve do indeksa 1 (ukljucujuci njega). Brojac smanjujemo;
		{
			_array[i]=_array[i-1];//namjesto[10]=namjesto[9] i tako sve elemente;
		}

		//Drugi nacin:
		//for (int i = _trenutno-1; i >=0; i--)//Idemo for  od trenutnog el. -1 pa sve do 0, brojac opada;
		//{
		//	_array[i+1]=_array[i];//Npr namjesto[10]=namjesto[9] i tako svaki; Uporedo opadaju;
		//}
		_array[0]=x;//Postavimo x da je na prvom mjestu;
		_trenutno++;//Uvecamo jer je dodan jedan element dodan;
	}

	void dodaj_na_kraj(int x)override
	{
		if(_trenutno==_max)//Ako je dostignuta trenuta max velicina niza, prosiri ga;
			prosiriArray();
		_array[_trenutno]=x;//Na zadnju poziciju dodaj clan;
		_trenutno++;//Uvecaj brojac;
	}

	int ukloni_sa_pocetka()override
	{
		if(_trenutno==0)//Ako je lista prazna, nemamo sta vratiti;
			throw exception("Trenutno nema elemenata za izbaciti !");
		int temp=_array[0];//Uzmemo element na pocetku (prvoj poziciji);
		for (int i = 0; i < _trenutno-1; i++)//Za jedan uklanjamo stoga je _trenutno-1 kako bi imali okej pozicije a ne npr junk vrijednost;
		{
			_array[i]=_array[i+1];//Unazad pomjerimo svaki clan niza;
		}
		_trenutno--;//Smanjimo brojac, jer je jedan element uklonjen;
		return temp;//Vratimo prvi element (onaj koji smo uklonili);
	}

	int ukloni_sa_kraja()override
	{
		if(_trenutno==0)//Ako nema elemenata, nemamo sta vratiti sa kraja;
			throw exception("Trenutno nema elemenata u nizu !");

		_trenutno--;//Umanjimo trenutno jer smo  zadnji element izbacili;
		int temp=_array[_trenutno];//Vratimo trenutno zadnji element niza;
		return temp;
	}

	bool jel_prazna()override
	{
		return _trenutno==0;//Vrati true ili false, shodno tome jel lista prazna ili ne;
	}

	int operator[](int index) override
	{
		if(index<0 || index>=_trenutno)//Ako je ne validan indeks. (Ne moze biti negativan niti veci od trenutno);
			throw exception("Index is out of range ");
		if(_trenutno==0)//Slucaj ako nema elemenata u nizu;
			throw exception("Nema elemenata u nizu !");
		return _array[index];//Vrati element na trenutnoj poziciji;
	}

	int get_trenutno() override 
	{
		return _trenutno;//Vrati koliko trenutno elemenata ima u listi;
	}
};


//Kreiranje linkovane liste;
class LinkedList : public Lista
{
	//Potrebno je da imamo inicijalni (pocetni) pokazivac, koji ce daljnje pokazivati na ostale;
	Cvor* _head=nullptr;
	int _trenutno=0;//Brojac elemenata linkovanih u listu;

public:
	void dodaj_na_pocetak(int x) override
	{
		Cvor* noviElement=new Cvor(x,_head);//Kreiramo novi el, i stavimo da njegov pokazivac pokazuje na prvi;
		_head=noviElement;//Pokazivac next od _head (glave) sada pokazuje na novi prvi element;
		_trenutno++;//Povecamo brojac jer je dodat element;
	}

	void dodaj_na_kraj(int x)override
	{
		Cvor* noviZaDodati=new Cvor(x,nullptr);//Kreiramo novi clan za dodati, sa nullptr za next;

		if(_head==nullptr)//Ako je ovo prvi clan za dodati
			_head=noviZaDodati;//Dodaj ga odmah;
		else
		{
			Cvor* trenutni=_head;
			while(trenutni->next!=nullptr)//Sve dok trenutni element pokazuje na neki naredni
				 trenutni=trenutni->next;//Zamjeni trenutni za taj naredni;
			//Kada naidjes na prazni element (koji ne pokazuje ni na jedan naredni),
			//Dodaj da on pokazuje na novi:
			trenutni->next=noviZaDodati;
			_trenutno++;//Jer smo dodali element;
		}
	}

	int ukloni_sa_pocetka()override
	{
		int x=_head->info;//Pohranimo vrijednost prvog;
		Cvor* temp=_head;//Napravimo pomocni cvor koji pokazuje na prvi el (glavu);
		_head=_head->next;//Preusmjerimo da prvi (glava) pokazuje na naredni;
		delete temp;//Unistimo temp jer je to prvi element (onaj koji smo uklonili);
		_trenutno--;//Umanjimo brojac jer je uklonjen jedan element;
		return x;//Vratimo vrijednost uklonjenog clana;
	}

	int ukloni_sa_kraja() override
	{
		if(_trenutno==0)
			throw exception("Nema elemenata za ukloniti !");
		else
		{
			Cvor* trenutni=_head;//Pocnemo od glave;
			Cvor* prijeTrenutnog=nullptr;
			while(trenutni->next!=nullptr)//Sve dok trenutni element pokazuje na neki naredni
			{
				prijeTrenutnog=trenutni;//Ovdje pamtimo predzadnji clan;
				trenutni=trenutni->next;//Trenutni zamjeni sa narednim;
			}
			if(prijeTrenutnog!=nullptr)//Ako novi zadnji element nije nullptr znaci da on nije zadnji te
				prijeTrenutnog->next=nullptr;//Da se zadnji nalazi poslije njega;//Tj ima vise el u listi,stoga njegov next postavi na nullptr jer je on (next) sada zadnji i treba bit null;
			else
				_head=nullptr;//Ako je samo jedan element u listi ostao, nulira se;
			int x=trenutni->info;//Uzmemo vrijednost zadnjeg clana;
			delete trenutni;//Obrisemo zadnji clan;
			_trenutno--;//Smanjimo brojac jer smo uklonili jedan clan;
			return x;
		}
	}

	bool jel_prazna() override
	{
		return _trenutno==0;
	}

	int operator[](int index) override
	{
		return -1;//Samo kako ne bi morali implementirati ovaj operator;
	}

	int get_trenutno()override
	{
		return _trenutno;
	}
};

//Testna funkcija koja prima referencu objekta tipa Lista, stoga  ce se radi virtualnosti u baznoj klasi
//aktivirati polimorfizam, te ce se kroz navedenu fiju moci slati i povezana lista i sekvencijalna;
void funkcija(Lista& L)
{
	for (int i = 0; i < 10; ++i)
	{
		L.dodaj_na_pocetak(i);
	}
	for (int i = 0; i < 10; ++i)
	{
		L.dodaj_na_kraj(i);
	}
	for (int i = 0; i < 3; ++i)
	{
		cout << "uklonjeno sa sa pocetka: " << L.ukloni_sa_pocetka() << endl;
	}

	for (int i = 0; i < 12; ++i)
	{
		cout << "uklonjeno sa kraja: " << L.ukloni_sa_kraja() << endl;
	}

	while (!L.jel_prazna())
	{
		cout << "uklonjeno sa pocetka: " << L.ukloni_sa_pocetka() << endl;
	}
}


//Testna funkcija za stek;Vazi isto kao i za funkciju iznad, aktivan je polimorfizam;
void funkcija(Stek& s)
{
	for (int i = 0; i < 10; ++i)
	{
		s.push(i);
	}

	while (!s.is_Empty())
	{
		cout << "uklonjeno sa pocetka: " << s.pop() << endl;
	}
}
void main()
{
	SeqList x1;
	LinkedList x2;
	SeqStack s1;
	LinkedStack s2;
	
	//funkcija(x1);
	funkcija(x2);
	//funkcija(s1);
	//funkcija(s2);
}
