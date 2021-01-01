#pragma once
#include <iostream>
#include <list>
#include "Wypozyczenie.h"
#include "Ksiazka.h"
#include "Uzytkownik.h"
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

class Wypozyczenia {
	list<Wypozyczenie> wypozyczenia;
	bool zaladuj_dane_z_pliku();
	bool zaladuj_dane_do_pliku();
public:
	Wypozyczenia();
	~Wypozyczenia();
	void wypozycz_ksiazke(Ksiazka _ksiazka, Uzytkownik _user, Wypozyczenie::data _data_wyp, Wypozyczenie::data _data_od);
	void oddaj_ksiazke(Ksiazka _ksiazka, Uzytkownik _user);
	void pokaz_wyp();
};