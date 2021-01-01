#pragma once
#include <iostream>
#include <list>
#include "Autor.h"
using namespace std;

class Ksiazka {
	string tytul;
	int rok;
	string ISBN;
	string wydawnictwo;
	int liczba_stron;
	list<Autor> autorzy;
public:
	Ksiazka();
	Ksiazka(string _tytul);
	Ksiazka(string _tytul,list<Autor> _autorzy, int _rok, string _ISBN, string _wydawnictwo, int _liczba_stron);
	string getTytul();
	string getAutorzy();
	int getRok();
	string getISBN();
	string getWydawnictwo();
	int getLiczba_stron();
};