#include "Wypozyczenia.h"
using namespace std;

bool Wypozyczenia::zaladuj_dane_z_pliku()
{
	ifstream plik("baza_danych.txt");
	if (plik.is_open()) {
		string line;
		while (getline(plik, line))
		{
			stringstream str(line);
			string imie_autora;
			string nazwisko_autora;
			string tytul;
			string rok_string;
			string liczba_stron_string;
			int rok_ = 0;
			string ISBN;
			string wydawnictwo;
			int liczba_stron = 0;
			string imie_uzyt;
			string nazwisko_uzyt;
			string PESEL;
			string dzien_s, miesiac_s, rok_s, godzina_s, minuta_s, sekunda_s;
			list<Autor> lista_autorow;


			getline(str, tytul, ',');
			//getline(str, imie_autora, ',');
			//getline(str, nazwisko_autora, ',');
			string aut;

			getline(str, aut, ',');
			int licznik = 0;
			for (unsigned int i = 0; i < aut.size(); i++) {
				if (aut[i] == ';') {
					licznik++;
				}
			}
			stringstream str2(aut);
			for (int i = 0; i < licznik; i++) {
				getline(str2, imie_autora, ' ');
				getline(str2, nazwisko_autora, ';');
				lista_autorow.emplace_back(imie_autora, nazwisko_autora);
			}

			getline(str, rok_string, ',');
			rok_ = stoi(rok_string);
			getline(str, ISBN, ',');
			getline(str, wydawnictwo, ',');
			getline(str, liczba_stron_string, ',');
			liczba_stron = stoi(liczba_stron_string);
			getline(str, imie_uzyt, ',');
			getline(str, nazwisko_uzyt, ',');
			getline(str, PESEL, ',');

			Wypozyczenie::data data_wyp;
			Wypozyczenie::data data_od;

			getline(str, dzien_s, '.');
			data_wyp.dzien = stoi(dzien_s);
			getline(str, miesiac_s, '.');
			data_wyp.miesiac = stoi(miesiac_s);
			getline(str, rok_s, ' ');
			data_wyp.rok = stoi(rok_s);
			getline(str, godzina_s, ':');
			data_wyp.godzina = stoi(godzina_s);
			getline(str, minuta_s, ':');
			data_wyp.minuta = stoi(minuta_s);
			getline(str, sekunda_s, ' ');
			data_wyp.sekunda = stoi(sekunda_s);
			getline(str, data_wyp.dzien_tyg, ',');


			getline(str, dzien_s, '.');
			data_od.dzien = stoi(dzien_s);
			getline(str, miesiac_s, '.');
			data_od.miesiac = stoi(miesiac_s);
			getline(str, rok_s, ' ');
			data_od.rok = stoi(rok_s);
			getline(str, godzina_s, ':');
			data_od.godzina = stoi(godzina_s);
			getline(str, minuta_s, ':');
			data_od.minuta = stoi(minuta_s);
			getline(str, sekunda_s, ' ');
			data_od.sekunda = stoi(sekunda_s);
			getline(str, data_od.dzien_tyg, ',');


			Ksiazka ks(tytul, lista_autorow, rok_, ISBN, wydawnictwo, liczba_stron);
			Uzytkownik u(imie_uzyt, nazwisko_uzyt, PESEL);
			Wypozyczenie wyp(ks, u, data_wyp, data_od);
			wypozyczenia.emplace_back(wyp);
		}
		plik.close();
		return true;
	}
	else {
		throw "Could not open file";
		return false;
	}
}

bool Wypozyczenia::zaladuj_dane_do_pliku()
{
	ofstream plik("baza_danych.txt");
	if (plik.is_open()) {
		for (auto& s : wypozyczenia) {
			plik << s.getKsiazka().getTytul() << ","
				<< s.getKsiazka().getAutorzy() << ","
				<< s.getKsiazka().getRok() << ","
				<< s.getKsiazka().getISBN() << ","
				<< s.getKsiazka().getWydawnictwo() << ","
				<< s.getKsiazka().getLiczba_stron() << ","

				<< s.getUser().getImie() << ","
				<< s.getUser().getNazwisko() << ","
				<< s.getUser().getPESEL() << ","

				<< s.getData_wyp().dzien << "."
				<< s.getData_wyp().miesiac << "."
				<< s.getData_wyp().rok << " "
				<< s.getData_wyp().godzina << ":"
				<< s.getData_wyp().minuta << ":"
				<< s.getData_wyp().sekunda << " "
				<< s.getData_wyp().dzien_tyg << ","

				<< s.getData_od().dzien << "."
				<< s.getData_od().miesiac << "."
				<< s.getData_od().rok << " "
				<< s.getData_od().godzina << ":"
				<< s.getData_od().minuta << ":"
				<< s.getData_od().sekunda << " "
				<< s.getData_od().dzien_tyg << ","
				<< "\n";

		}
	}
	return false;
}

Wypozyczenia::Wypozyczenia()
{
	zaladuj_dane_z_pliku();
}

Wypozyczenia::~Wypozyczenia()
{
	zaladuj_dane_do_pliku();
}

void Wypozyczenia::wypozycz_ksiazke(Ksiazka _ksiazka, Uzytkownik _user, Wypozyczenie::data _data_wyp, Wypozyczenie::data _data_od)
{
	Wypozyczenie w(_ksiazka, _user, _data_wyp, _data_od);
	wypozyczenia.emplace_back(w);
	cout << "Wypozyczenie powiodlo sie!" << endl;
	return;
}

void Wypozyczenia::oddaj_ksiazke(Ksiazka _ksiazka, Uzytkownik _user)
{
	for (list <Wypozyczenie>::iterator it = wypozyczenia.begin(); it != wypozyczenia.end(); it++) {
		if (it->getKsiazka().getTytul() == _ksiazka.getTytul() && it->getUser().getPESEL() == _user.getPESEL()) {
			wypozyczenia.erase(it);
			cout << "Oddanie powiodlo sie!" << endl;
			return;
		}
	}
}

void Wypozyczenia::pokaz_wyp()
{
	for (auto& p : wypozyczenia) {
		cout << endl << "Autorzy: " << p.getKsiazka().getAutorzy() << endl
			<< "Osoba wypozyczajaca PESEL: " << p.getUser().getPESEL() << endl
			<< "Czas: " << p.getData_wyp();
	}
	cout << endl;
}
