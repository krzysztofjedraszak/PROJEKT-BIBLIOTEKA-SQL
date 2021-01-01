#pragma once
#include <iostream>
using namespace std;

class Uzytkownik {
	string imie;
	string nazwisko;
	string PESEL;
public:
	Uzytkownik();
	Uzytkownik(string _PESEL);
	Uzytkownik(string _imie, string _nazwisko, string _PESEL);
	string getImie();
	string getNazwisko();
	string getPESEL();
};