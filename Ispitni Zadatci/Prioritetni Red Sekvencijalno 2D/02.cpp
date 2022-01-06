#include<iostream> 
#include<cmath> // treba nam da računamo formulu koja nam je zadata postavkom
using namespace std;
struct Vektor2D //kreiramo strukturu vektor koja je zauprave naša tačka u prostoru
{
	int x; //ima dvije vrijednosti x i y
	int y;
	Vektor2D() //defaultni konstruktor
	{
		x = 0;
		y = 0;
	}
	Vektor2D(int x, int y) //naš konstruktor gdje prosljeđivamo vrijednosti koordinata
	{
		this->x = x;
		this->y = y;
	}
	friend ostream& operator<< (ostream& COUT, Vektor2D vektor) //pravimo ispis za naš vektor
	{
		COUT << "(" << vektor.x << " : " << vektor.y << ")" << endl;
		return COUT;
	}
};
class PrioitetniRedSeq //pišemo klasu Prioritetni Red Sekvencijalno
{
  private: //u privatnom djelu klase stvaramo atribude trenutno, naš niz i veličina niza
	int trenutno;
	Vektor2D* niz;
	int velNiza;
	void ProsiriNiz() //ako je niz u potpunosti popunjen potrebno ga je proširiti
	{
		velNiza += velNiza;
		Vektor2D* temp = new Vektor2D[velNiza]; //stvaramo privremeni niz
		for (size_t i = 0; i < trenutno; i++)
		{
			temp[i] = niz[i]; //elemente starog niza prebacujemo u privremeni niz
		}
		delete niz; //brisemo stari niz
		niz = temp; //niz postaje privremeni niz
	}
	bool isEmpty() //provjeravamo da li je niz prazan
	{
		return trenutno == 0;
	}
	bool isFull() //provjeravamo da li je niz pun
	{
		return trenutno == velNiza;
	}
	float Distanca(int index) //racunamo udaljenost tačaka pomocu formule koja nam je data
	{
		return sqrtf(powf(5 - niz[index].x, 2) + powf(5 - niz[index].y, 2)); //u zavisnosti od toga koja se tacka trazi ova se forula mjenja.
	}
public:
	PrioitetniRedSeq() //inicijalizujemo vrijednosti u defaultnom konstruktoru
	{
		trenutno = 0;
		velNiza = 10;
		niz = new Vektor2D[velNiza];
	}
	void Dodaj(Vektor2D x) //dodajemo novi elemenat u niz
	{
		if (isFull()) //ako je niz pun onda ga prosirujemo
			ProsiriNiz();
		niz[trenutno] = x;
		trenutno++; //povecavamo trenutno posto smo dodali novi elemenat
	}
	void Ukloni()
	{
		float MinEl = Distanca(0); //pravimo pomocnu varijablu minimalni elemenat kojoj dajemo vrijednost distance prvog elementa u nizu
		int minIndex = 0; //pratimo koji indeks nam je dao tu vrijednost
		if (isEmpty()) //ako je red prazan onda nista ne radimo
		{
			cout << "Red je prazan !" << endl;
			return;
		}
		for (size_t i = 1; i < trenutno; i++) //provjeravamo za svaki elemenat u redu
		{
			if (MinEl > Distanca(i)) //ako je minimalna distanca veca od distance nekog drugog elementa u nizu onda to vise nije minimalna distanca pa je moramo zamjeniti
			{
				MinEl = Distanca(i); //sada postaje minimalna distanca
				minIndex = i; //pamtimo index na kojoj je pohranjena najmanja distanca
			}
		}
		trenutno--; //posto cemo izbaciti jedan elemenat iz niza smanjivamo vrijednost od trenutno
		niz[minIndex] = niz[trenutno]; //elemenat koji "izbacujemo" postaje zadnji dodati elemenat u nizu i tako prestaje da postoji
	}
	void Ispis() //ispisujemo niz
	{
		for (size_t i = 0; i < trenutno; i++)
		{
			cout << niz[i];
		}
	}
	~PrioitetniRedSeq()
	{
		delete[] niz; //brisemo niz 
	}
};

int main()
{
  //kreiramo testne tacke
	Vektor2D tacka1(1, 2);
	Vektor2D tacka2(2, 3);
	Vektor2D tacka3(3, 4);
	Vektor2D tacka4(4, 5);
	Vektor2D tacka5(5, 6);
	Vektor2D tacka6(11, 4);
  //kreiramo red
	PrioitetniRedSeq red;
  //dodajemo tacke u red
	red.Dodaj(tacka1);
	red.Dodaj(tacka2);
	red.Dodaj(tacka3);
	red.Dodaj(tacka4);
	red.Dodaj(tacka5);
	red.Dodaj(tacka6);
  //radimo ispis
	red.Ispis();
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
  //uklanjamo tacke iz reda
	red.Ukloni();
	red.Ispis();
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	red.Ukloni();
	red.Ispis();
	return 0;
}
