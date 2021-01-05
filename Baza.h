#pragma once
#include "Autor.h"
#include "Ksiazka.h"
#include "Uzytkownik.h"
#include "Wypozyczenie.h"
#include "Wypozyczenia.h"
#include <iostream>
#include <string>
#include <list>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "sqlite3.h"
using namespace std;
class Baza {
	sqlite3* baza;
	char* blad;
	int kod_bledu = 0;
	void stworz_tabele();
	void petla();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	void dodaj_wypozyczenie();
	bool czy_plik_istnieje();
public:
	Baza();
	void odpal();
};