#include "Wypozyczenie.h"

Wypozyczenie::Wypozyczenie(Ksiazka _ksiazka, Uzytkownik _user, Wypozyczenie::data _data_wyp, Wypozyczenie::data _data_od)
{
	ksiazka = _ksiazka;
	user = _user;

	data_wyp.dzien = _data_wyp.dzien;
	data_wyp.miesiac = _data_wyp.miesiac;
	data_wyp.rok = _data_wyp.rok;
	data_wyp.godzina = _data_wyp.godzina;
	data_wyp.minuta = _data_wyp.minuta;
	data_wyp.sekunda = _data_wyp.sekunda;
	data_wyp.dzien_tyg = _data_wyp.dzien_tyg;

	data_od.dzien = _data_od.dzien;
	data_od.miesiac = _data_od.miesiac;
	data_od.rok = _data_od.rok;
	data_od.godzina = _data_od.godzina;
	data_od.minuta = _data_od.minuta;
	data_od.sekunda = _data_od.sekunda;
	data_od.dzien_tyg = _data_od.dzien_tyg;
}

Ksiazka Wypozyczenie::getKsiazka()
{
	return ksiazka;
}

Uzytkownik Wypozyczenie::getUser()
{
	return user;
}

Wypozyczenie::data Wypozyczenie::getData_wyp()
{
	return data_wyp;
}

Wypozyczenie::data Wypozyczenie::getData_od()
{
	return data_od;
}

ostream& operator<<(ostream& os, const Wypozyczenie::data& dt)
{
	ostream& operator<<(ostream & os, const Wypozyczenie::data & dt);
	{
		os << dt.dzien << '.' 
			<< dt.miesiac << '.' 
			<< dt.rok << ' ' 
			<< dt.godzina << ':' 
			<< dt.minuta << ':' 
			<< dt.sekunda << ' '
			<< dt.dzien_tyg ;
		return os;
	}
}
