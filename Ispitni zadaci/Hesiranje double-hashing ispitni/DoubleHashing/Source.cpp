#include <iostream>
using namespace std;
/*
  Funkcija za rjesavanje kolizije = (HeshFunkcija1() + i * HeshFunkcija2()) % TABLE_SIZE
 */

struct Vektor3D
{
	int x, y, z;

	Vektor3D()
		: x(INT_MIN), y(INT_MIN), z(INT_MIN)
	{

	}

	Vektor3D(int x, int y, int z)
		: x(x), y(y), z(z)
	{

	}

	friend bool operator!= (const Vektor3D& first, const Vektor3D& second)
	{
		return first.x != second.x && first.y != second.y && first.z != second.z;
	}

	friend ostream& operator<< (ostream& COUT, const Vektor3D& vector)
	{
		if (vector.x != INT_MIN)
			cout << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
		else
			cout << "";
		return COUT;
	}
};

template<typename T>
class HashTable
{
private:
	T* _niz;
	bool* _zauzeti;
	int _brojac;
	int _size;

	int HeshFunkcija1(const T& key)
	{
		return sqrt(pow(key.x + key.y + key.z, 2));
	}

	int HeshFunkcija2(const T& key)
	{
		return sqrt(pow(key.x, 2) / 3 + pow(key.y, 2) / 3 + pow(key.z, 2) / 3);
	}
public:
	HashTable(int size = 15)
		: _brojac(0), _size(size)
	{
		_niz = new T[size];
		_zauzeti = new bool[size] {false};
	}

	~HashTable()
	{
		delete[] _niz;
		delete[] _zauzeti;
	}

	void Add(const T& element)
	{
		if (_brojac == _size)
		{
			cout << "Tabela je puna!" <<endl;
			return;
		}

		auto index = HeshFunkcija1(element);

		if (_zauzeti[index])
		{
			auto index2 = HeshFunkcija2(element);
			auto i = 1;

			while (true)
			{
				int newIndex = (index + i * index2) % _size;

				if (!_zauzeti[newIndex])
				{
					_niz[newIndex] = element;
					_zauzeti[newIndex] = true;
					break;
				}
				i++;
			}
		}

		else
		{
			_niz[index] = element;
			_zauzeti[index] = true;
		}
		_brojac++;
	}

	bool Remove(const T& element)
	{
		auto index = HeshFunkcija1(element);
		auto index2 = HeshFunkcija2(element);
		auto i = 1;

		while (_niz[index] != element)
		{
			if (i > _size)
			{
				cout << "Element nije pronadjen!" << endl;
				return false;
			}
			index += i * index2;
			index %= _size;
			i++;
		}

		_zauzeti[index] = false;
		return true;
	}

	void Print() const
	{
		for (int i = 0; i < _size; i++)
		{
			if (_zauzeti[i])
				cout << i << " --> " << _niz[i] << endl;
			else
				cout << i << " --> " << endl;
		}
	}
};

int main()
{
	HashTable<Vektor3D> table;

	table.Add(Vektor3D(2, 2, 2));
	table.Add(Vektor3D(5, 4, 2));
	table.Add(Vektor3D(7, 3, 1));
	table.Add(Vektor3D(8, 8, 8));
	cout << "----------------Prije uklanjanja---------------------\n";
	table.Print();

	table.Remove(Vektor3D(2, 2, 2));
	table.Remove(Vektor3D(5, 4, 2));
	table.Remove(Vektor3D(7, 3, 1));
	table.Remove(Vektor3D(8, 8, 8));

	cout << "----------------Nakon uklanjanja---------------------\n";
	table.Print();
}