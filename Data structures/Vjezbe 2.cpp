#include <iostream>
using namespace std;

//Kreiranje typedef Tipa:
//poslije kljucne rijeci typedef stavimo tip podatka koji zelimo da taj identifikator bude;
//mogu biti primitivni  tipovi (int, char,float etc.) ili user-def tipovi;
typedef int Tip;

//Kreiranje strukture Cvor:
struct Cvor
{
	Cvor* next=nullptr;//Pokazivac na naredni element u nizu/listi;
	Tip   vrijednost;//Vrijednost clana tog niza/liste;
	Cvor()//Dflt ctor;
	{
		next=nullptr;
		vrijednost=0;
	}
	Cvor(Tip x, Cvor* _next)//User def ctor;
	{
		vrijednost=x;
		next=_next;
	}
};

//Kreiranje apstraktne klase Queue:
class  Queue
{
	//Kako bi dobili kao rezultat abstraktnu klasu, sve njene metode cemo potpisati kao ciste virtualne:
public:
	virtual void dodaj(Tip x)=0;
	virtual Tip  ukloni ()=0;
	virtual bool isEmpty()=0;

	//Konvencije radi:
	//Prazne ctor i dtor oznacimo sa default;
	Queue()=default;
	virtual ~Queue()=default;
};

//Kreiranje klase sekvencijalnog reda (Queue-a):
class SeqQueue:Queue//Nasljedimo baznu klasu Queue;
{
	int max=20;//Max velicina reda;
	int pocetak=0;//Pocetni brojac;
	int kraj=0;//Krajnji brojac;
public:
	int brojac=0;//Regularni brojac koji prati svako dodavanje;
	Tip* _array=new Tip [max];//Niz od max elemenata;Niz je tipa Tip(u nasem slucaju obicni int);


	virtual void dodaj(Tip x) override //override oznacava da se prepisuje default implementacija iz bazne klase;
	{
		//virtual mozemo koristiti ali nije neophodno jer se iz naslijedjene bazne klase zna da je data metoda virtual;

		if(brojac==max)//ili pocetak==kraj;Isto je znacenje;
			throw exception("Dostignut MAXIMUM Queue-a !");

		_array[kraj]=x;//Na trenutnu slobodnu lokaciju dodaj novi element;
		kraj++;//Inkrementuj (pomjeri) kraj za jedan;
		brojac++;//Inkrementuj (povecaj) brojac trenutnih elemenata u Queue-u;

		if(kraj==max)//Kada dostignemo max
			kraj=0;//kraj se "rotira", postaje nula;Pocinje se dodavati  na pocetak;
	}
	virtual Tip ukloni() override
	{
		if(brojac==0)
			throw exception("Nema elemenata za ukloniti !");
		//ili
		//if(pocetak==kraj)
		//	throw exception("Nema elemenata za ukloniti !");

		Tip temp=_array[pocetak];//Uzimamo el sa pocetka, onaj koji je prvi dodan;
		_array[pocetak]=0;//Simuliranje da je ta vrijednost 'obrisana';
		if(pocetak==max)//Ako je dostignut max, zadnji clan niza
			pocetak=0;//Stavi pocetak na nula,kako bi nastavio izbacivati elemente redosljedom kojim su i usli;Ista rotacija kao za kraj;

		pocetak++;//Inkrementujemo (pomjerimo) pocetak, jer je jedan element sa pocetka uklonjen;
		brojac--;//Dekrementujemo (smanjimo) opci brojac elemenata, jer je jedan element uklonjen;
		return temp;//Vratimo vrijednost zadnjeg elementa;
	}
	virtual bool isEmpty()override
	{
		if(pocetak==kraj)
			return true;
		//Ili:
		//if(brojac==0)
		//	return true;
		return false;
	}
};

//Kreiranje klase linkovanog reda (Queue-a):

class LinkedQueue:Queue//Naslijedimo  baznu klasu;
{
public:
	Cvor* head=nullptr;//Pokazivac na prvi;
	Cvor* end=nullptr;//Pokazivac na zadnji;

	void dodaj(Tip x)override
	{
		Cvor* noviElement=new Cvor(x,nullptr);//Kreiramo pokazivac na novi element koji zelimo dodati;Posto koristimo logiku dodavanja na kraj, njegov next pokazivac je nullptr;(jer je on zadnji)

		if(!isEmpty())//Ako Queue nije prazan
		{
			end->next=noviElement;//Pokazivac next predzadnjeg clana pokazuje na novo-dodani;
			end=noviElement;//Zadnji clan postaje novo-dodani;
		}
		if(isEmpty())//Ako je Queue prazan
		{
			//Novo-dodani clan je ujedno i prvi i zadnji:
			head=noviElement;
			end=noviElement;
		}
	}
	Tip ukloni()override
	{
		if(isEmpty())
			throw exception("Nema elemenata za ukloniti !");

		Cvor* temp=head;//Kreiramo pomocni ptr koji pokazuje na prvi clan;
		head=head->next;//Prvi pocne pokazivati na naredni u redu;
		Tip x=temp->vrijednost;//Uzmemo vrijednost prvog;
		delete temp;//Obrisemo prvi clan;

		if(head==nullptr)//Ako je prvi el prazan (nepostojeci)
			end=nullptr;//onda i kraj mora biti prazan
		return x;//Vratimo vrijednost uklonjenog clana;
	}
	bool isEmpty()override
	{
		//if(head==nullptr || end==nullptr)
		//	return true;
		//Gornji izraz se moze pojednostaviti sa:
		if(head==nullptr)//Jer ako je head nullptr i end je sigurno;
			return true;
		return false;
	}
};
int main ()
{
	cout<<"ISPIS SEKVENCIJALNOG QUEUE-A"<<endl;
	SeqQueue Q;
	for (int i = 0; i < 20; i++)
	{
		cout<<"Dodan: "<< i<<endl;
		Q.dodaj(i);
	}
	for (int i = 0; i < 10; i++)
	{
		cout<<"Izbacen:" <<Q.ukloni()<<endl;
	}
	cout<<"Preostali elementi su:"<<endl;
	for (int i = 0; i <20; i++)
	{
		cout<<Q._array[i]<<endl;
	}
	cout<<"-----------------------------------------------------------------------"<<endl;

	cout<<"ISPIS LINKOVANOG QUEUE-A"<<endl;

	LinkedQueue L;
	for (int i = 0; i < 20; i++)
	{
		cout<<"Dodan: "<< i<<endl;
		L.dodaj(i);
	}
	for (int i = 0; i < 10; i++)
	{
		cout<<"Izbacen:" <<L.ukloni()<<endl;
	}
	Cvor* ispis=L.head;
	cout<<"Preostali elementi su:"<<endl;
	while(!L.isEmpty())
	{
		if (ispis!=nullptr)//Bice nullptr samo kada dodjemo do zadnjeg clana ;
		{
			cout<<ispis->vrijednost<<endl;
		    ispis=ispis->next;
		}
		else
			break;//Kada je nullptr, nema vise el za ispis, stoga sa break izadjemo iz while petlje;
	}
	cout<<"-----------------------------------------------------------------------"<<endl;
	
	cin.get();
	return 0;
}