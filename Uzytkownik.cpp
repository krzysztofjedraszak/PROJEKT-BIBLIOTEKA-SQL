#include "Uzytkownik.h"

Uzytkownik::Uzytkownik()
{
	imie = "";
	nazwisko = "";
	PESEL = "";
}

Uzytkownik::Uzytkownik(string _PESEL)
{
	PESEL = _PESEL;
}

Uzytkownik::Uzytkownik(string _imie, string _nazwisko, string _PESEL)
{
	imie = _imie;
	nazwisko = _nazwisko;
	PESEL = _PESEL;
}

string Uzytkownik::getImie()
{
	return imie;
}

string Uzytkownik::getNazwisko()
{
	return nazwisko;
}

string Uzytkownik::getPESEL()
{
	return PESEL;
}
