#include "Ksiazka.h"

Ksiazka::Ksiazka()
{
	tytul = "";
	rok = 0;
	ISBN = "";
	wydawnictwo = "";
	liczba_stron = 0;
}

Ksiazka::Ksiazka(string _tytul)
{
	tytul = _tytul;
}

Ksiazka::Ksiazka(string _tytul, list<Autor> _autorzy, int _rok, string _ISBN, string _wydawnictwo, int _liczba_stron)
{
	tytul = _tytul;
	rok = _rok;
	ISBN = _ISBN;
	wydawnictwo = _wydawnictwo;
	liczba_stron = _liczba_stron;
	autorzy = _autorzy;
}

string Ksiazka::getTytul()
{
	return tytul;
}

string Ksiazka::getAutorzy()
{
	string zwroc="";
	for (auto& s : autorzy) {
		zwroc += s.getImie()+" ";
		zwroc += s.getNazwisko()+";";
	}
	return zwroc;
}

int Ksiazka::getRok()
{
	return rok;
}

string Ksiazka::getISBN()
{
	return ISBN;
}

string Ksiazka::getWydawnictwo()
{
	return wydawnictwo;
}

int Ksiazka::getLiczba_stron()
{
	return liczba_stron;
}
