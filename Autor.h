#pragma once
#include <iostream>
using namespace std;

class Autor {
	string imie;
	string nazwisko;
public:
	Autor(string _imie, string _nazwisko);
	string getImie();
	string getNazwisko();
};