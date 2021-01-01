#include "Autor.h"

Autor::Autor(string _imie, string _nazwisko)
{
	imie = _imie;
	nazwisko = _nazwisko;
}

string Autor::getImie()
{
	return imie;
}

string Autor::getNazwisko()
{
	return nazwisko;
}
