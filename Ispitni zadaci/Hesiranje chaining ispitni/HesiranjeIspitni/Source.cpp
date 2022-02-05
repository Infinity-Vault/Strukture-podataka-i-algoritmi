#include <iostream>
using namespace std;

template <class T>
struct Cvor
{
	Cvor* next;
	T info;

	Cvor(T info, Cvor<T>* next) : info(info)
	{
		this->next = next;
	}
};


//Struktura Tacka2D:

struct Tacka2D
{
	int x;
	int y;
	Tacka2D(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	~Tacka2D() = default;

	friend ostream& operator <<(ostream& out, const Tacka2D& tacka)
	{
		return out << "-->" << "x:" << tacka.x << " " << " y:" << tacka.y << endl;
	}
};

template <class T>
class ListaPov
{
private:
	int brojac;
	Cvor<T>* prvi;
public:
	ListaPov()
	{
		brojac = 0;
		prvi = nullptr;
	}

	void dodaj(T v)
	{
		Cvor<T>* t = new Cvor<T>(v, prvi);
		prvi = t;
		brojac++;
	}

	void ukloni()
	{
		if (isPrazan())
			throw std::exception("Greska. Nije moguce ukloniti elemenat iz prazne liste");

		brojac--;
		Cvor<T>* t = prvi;
		prvi = prvi->next;
		T x = t->info;
		delete t;
		//return x;
	}
	bool isPrazan()
	{
		return (prvi == nullptr);
	}

	int count()
	{
		return brojac;
	}

	void print(string pre = "", string post = "  ")
	{
		Cvor<T>* t = prvi;
		while (t != nullptr)
		{
			cout << pre << t->info<<post;
			t = t->next;
		}
		cout << endl;
	}

	T& get(int i)
	{
		if (i > brojac)
			throw std::exception("indeks je veæi od brojaca");

		Cvor<T>* t = prvi;
		for (int j = 0; j < (brojac - i - 1); j++)
		{
			t = t->next;
		}
		return t->info;
	}

	T& operator[](int i)
	{
		return get(i);
	}

	void set(int i, T v)
	{
		get(i) = v;
	}

	bool sadrzi(T v)
	{
		Cvor<T>* t = prvi;
		while (t != nullptr)
		{
			if (t->info == v)
				return true;
			t = t->next;
		}
		return false;
	}

	T* formirajNiz()
	{
		T* niz = new T[this->brojac];

		int b = 0;
		Cvor<T>* t = prvi;
		while (t != nullptr)
		{
			niz[b++] = t->info;
			t = t->next;
		}
		return niz;
	}
	void UkloniByKey(Tacka2D tacka)
	{
		if (brojac == 0)
			throw exception("Nema elemenata za ukloniti!");

		Cvor<Tacka2D>* trenutni = prvi;
		Cvor<Tacka2D>* prijeTrenutnog = nullptr;

		while (trenutni!=nullptr)
		{
			if (trenutni->info.x == tacka.x && trenutni->info.y == tacka.y)
				break;
			prijeTrenutnog = trenutni;
			trenutni = trenutni->next;
		}
		if (trenutni == nullptr)
			return;
		if (prijeTrenutnog == nullptr)
			prvi = prvi->next;
		else
			prijeTrenutnog->next = trenutni->next;
		delete trenutni;
		trenutni = nullptr;
		brojac--;
	}
};

//Klasa za hesiranje:

class Hesh
{
private:
	int _brojac;
	int _size = 10;
	ListaPov<Tacka2D>* _niz;
	int HeshFunkcija(Tacka2D tacka)
	{
		return  (int)sqrt(pow(tacka.x + tacka.y, 2) / 2) % _size;
	}
public:
	Hesh()
	{
		_brojac = 0;
		_niz = new ListaPov<Tacka2D>[_size];
	}
	~Hesh() = default;

	void Dodaj (Tacka2D tacka)
	{
		if (_brojac == _size)
			throw exception("Nema mjesta za dodavanje, Hesh tabela je puna!");
		auto indeks = HeshFunkcija(tacka);
		_niz[indeks].dodaj(tacka);
		_brojac++;
	}
	void Ukloni(Tacka2D tacka)
	{
		if (_brojac == 0)
			throw exception("Hesh tabela je prazna!");
		auto indeks = HeshFunkcija(tacka);
		_niz[indeks].UkloniByKey(tacka);
	}
	void Print()
	{
		for (int i = 0; i < _size; i++)
			_niz[i].print();
	}
};
void main()
{
	try
	{
		Tacka2D t1 (1, 4);
		Tacka2D t2 (8, 42);
		Tacka2D t3 (18, 41);
		Tacka2D t4 (12, 4);
		Tacka2D t5 (9, 12);
		Tacka2D t6 (7, 3);
		Tacka2D t7 (5, 4);
		Tacka2D t8 (1, 4);
		Tacka2D t9 (4, 8);
		Tacka2D t10(0, 7);
		cout << "----------------------------------------Prije uklanjanja-----------------------" << endl;
		Hesh HeshTabela;
		HeshTabela.Dodaj(t1);
		HeshTabela.Dodaj(t2);
		HeshTabela.Dodaj(t3);
		HeshTabela.Dodaj(t4);
		HeshTabela.Dodaj(t5);
		HeshTabela.Dodaj(t6);
		HeshTabela.Dodaj(t7);
		HeshTabela.Dodaj(t8);
		HeshTabela.Dodaj(t9);
		HeshTabela.Dodaj(t10);
		HeshTabela.Print();
		cout << "----------------------------------------Nakon uklanjanja-----------------------" << endl;
		HeshTabela.Ukloni(t1);
		HeshTabela.Ukloni(t2);
		HeshTabela.Ukloni(t3);
		HeshTabela.Ukloni(t4);
		HeshTabela.Ukloni(t5);
		HeshTabela.Ukloni(t6);
		HeshTabela.Ukloni(t7);
		HeshTabela.Ukloni(t8);
		HeshTabela.Ukloni(t9);
		HeshTabela.Ukloni(t10);
		HeshTabela.Print();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	cout << endl;
	cin.get();
}