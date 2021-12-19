#pragma once

#include  <iostream>
using namespace  std;

typedef int Tip;

struct Cvor
{
	Cvor* next;
	Tip info;
	Cvor(Tip info, Cvor* next)
	{
		this->info = info;
		this->next = next;
	}
};

