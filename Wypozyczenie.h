#pragma once
#include <iostream>
#include "Ksiazka.h"
#include "Uzytkownik.h"
using namespace std;

class Wypozyczenie {
public:
	struct data {
		int dzien=0, miesiac=0, rok=0, godzina=0, minuta=0, sekunda=0;
		string dzien_tyg="";
		friend ostream& operator<<(ostream& os, const data& dt);
	};
private:
	Ksiazka ksiazka;
	Uzytkownik user;
	data data_wyp;
	data data_od;
public:
	Wypozyczenie(Ksiazka _ksiazka, Uzytkownik _user, data _data_wyp, data _data_od);
	Ksiazka getKsiazka();
	Uzytkownik getUser();
	data getData_wyp();
	data getData_od();
	
};