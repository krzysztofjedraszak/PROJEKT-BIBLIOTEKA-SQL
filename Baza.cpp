#include "Baza.h"

Baza::Baza()
{
	baza = nullptr;
	blad = nullptr;
}

void Baza::stworz_tabele()
{
	if (przelacznik == 0) {
		string stworz_tabele_autor = "CREATE TABLE Autor \
				(ID INTEGER PRIMARY KEY AUTOINCREMENT, \
				imie text, \
				nazwisko text);";

		string stworz_tabele_uzytkownik = "CREATE TABLE Uzytkownik \
				(imie text, \
				nazwisko text, \
				PESEL text PRIMARY KEY);";

		string stworz_tabele_ksiazka = "CREATE TABLE Ksiazka \
				(ID INTEGER PRIMARY KEY AUTOINCREMENT, \
				tytul text, \
				ID_autora text, \
				rok INTEGER, \
				ISBN text, \
				wydawnictwo text, \
				liczba_stron INTEGER,\
				FOREIGN KEY(ID_autora) REFERENCES Autor(ID));";

		string stworz_tabele_wypozyczenie = "CREATE TABLE Wypozyczenie \
				(ID INTEGER PRIMARY KEY AUTOINCREMENT, \
				ID_ksiazki text, \
				PESEL text,\
				FOREIGN KEY(ID_ksiazki) REFERENCES Ksiazka(ID) \
				FOREIGN KEY(PESEL) REFERENCES Uzytkownik(PESEL));";

		kod_bledu = sqlite3_exec(baza, stworz_tabele_autor.c_str(), callback, 0, &blad);
		if (kod_bledu != SQLITE_OK) {
			cout << "problem ze stworzeniem tabeli autor" << endl;
		}

		kod_bledu = sqlite3_exec(baza, stworz_tabele_ksiazka.c_str(), callback, 0, &blad);
		if (kod_bledu != SQLITE_OK) {
			cout << "problem ze stworzeniem tabeli ksiazka" << endl;
		}

		kod_bledu = sqlite3_exec(baza, stworz_tabele_uzytkownik.c_str(), callback, 0, &blad);
		if (kod_bledu != SQLITE_OK) {
			cout << "problem ze stworzeniem tabeli uzytkownik" << endl;
		}

		kod_bledu = sqlite3_exec(baza, stworz_tabele_wypozyczenie.c_str(), callback, 0, &blad);
		if (kod_bledu != SQLITE_OK) {
			cout << "problem ze stworzeniem tabeli wypozyczenie" << endl;
		}
	}
}

int Baza::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int Baza::czy_plik_istnieje()
{
	const string s = "database.db";
	fstream plik;
	plik.open(s.c_str(), ios::in | ios::_Nocreate);
	if (plik.is_open())
	{
		plik.close();
		return przelacznik = 1;
	}
	plik.close();
	return przelacznik = 0;
}

void Baza::zobacz_wypozyczenie()
{
	string zobacz = "SELECT * FROM Wypozyczenie";
	kod_bledu = sqlite3_exec(baza, zobacz.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z wyswietleniem calej zawartosci wypozyczenia" << endl;
	}
}

void Baza::zobacz_autor()
{
	string sql = "SELECT * FROM Autor";
	kod_bledu = sqlite3_exec(baza, sql.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z case 4" << endl;
	}
}

void Baza::zobacz_ksiazka()
{
	string zobacz = "SELECT * FROM Ksiazka";
	kod_bledu = sqlite3_exec(baza, zobacz.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z case 5" << endl;
	}
}

void Baza::zobacz_uzytkownik()
{
	string zobacz = "SELECT * FROM Uzytkownik";
	kod_bledu = sqlite3_exec(baza, zobacz.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z case 6" << endl;
	}
}

void Baza::odpal()
{
	czy_plik_istnieje();
	kod_bledu = sqlite3_open("database.db", &baza);
	if (kod_bledu) {
		cerr << "Nie udalo sie otworzyc bazy!!!" << endl;
		exit(0);
	}
	else {
		stworz_tabele();
		petla();
	}
	sqlite3_close(baza);
}

void Baza::petla()
{
	char wybor = 0;

	while (true) {
		cout << "Wcisnij 1 aby zobaczyc aktualna liste wyporzyczen" << endl;
		cout << "Wcisnij 2 aby wyporzyczyc ksiazke" << endl;
		cout << "Wcisnij 3 aby oddac ksiazke" << endl;
		cout << "Wcisnij 4 aby zobaczyc autora" << endl;
		cout << "Wcisnij 5 aby zobaczyc ksiazke" << endl;
		cout << "Wcisnij 6 aby zobaczyc uzytkownika" << endl;
		cout << "Wcisnij q aby wyjsc z programu" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case '1': {
			zobacz_wypozyczenie();
			break;
		}
		case '2': {
			dodaj_wypozyczenie();
			break;
		}
		case '3': {
			string tytul;
			string PESEL;

			cout << "Tytul ksiazki: ";
			cin >> tytul;
			cout << endl;

			cout << "PESEL oddajacego: ";
			cin >> PESEL;
			cout << endl;

			string sql1= "SELECT Ksiazka.tytul FROM Ksiazka WHERE (Ksiazka.tytul='"+tytul+"');";
			string sql2 = "SELECT PESEL FROM Uzytkownik WHERE (Uzytkownik.PESEL='"+PESEL+"');";
			string sql3="DELETE FROM Ksiazka WHERE tytul LIKE'%" + tytul + "%');";

			kod_bledu = sqlite3_exec(baza, sql3.c_str(), callback, 0, &blad);
			if (kod_bledu != SQLITE_OK) {
				cout << "problem z case 3" << endl;
			}

			break;
		}
		case '4': {
			zobacz_autor();
			break;
		}
		case '5': {
			zobacz_ksiazka();
			break;
		}
		case '6': {
			zobacz_uzytkownik();
			break;
		}
		//case '7': {
		//	string zapytanie = "SELECT * FROM (Wypozyczenie INNER JOIN Ksiazka \
		//			ON Wypozyczenie.ID_ksiazki = Ksiazka.ID) INNER JOIN Uzytkownik ON \
		//			Wypozyczenie.PESEL = Uzytkownik.PESEL";
		//	kod_bledu = sqlite3_exec(baza, zapytanie.c_str(), callback, 0, &blad);
		//	if (kod_bledu != SQLITE_OK) {
		//		cout << "problem z case 7" << endl;
		//	}
		//	break;
		//}
		case 'q': {
			exit(0);
		}
		default:
			break;
		}
		getchar();
		getchar();
		system("cls");
	}
}

void Baza::dodaj_wypozyczenie()
{
	string tytul;
	int rok_wydania = 0;
	string ISBN;
	string wydawnictwo;
	int liczba_stron = 0;
	list<Autor> autorzy;
	string autorzy_string;
	int ile_autorow = 0;
	string imie_aut, nazwisko_aut;
	string imie_wyp, nazwisko_wyp;
	string PESEL;
	int dzien = 0, miesiac = 0, rok = 0, godzina = 0, minuta = 0, sekunda = 0;
	string dzien_tyg;

	Wypozyczenie::data data_wyp;
	Wypozyczenie::data data_od;


	cout << "Tytul ksiazki: ";
	cin >> tytul;
	cout << endl;

	//cout << "Ilosc autorow ksiazki: ";
	//cin >> ile_autorow;
	//cout << endl;

	//for (int i = 0; i < ile_autorow; i++) {
	//	cout << "Imie autora " << i + 1 << ":";
	//	cin >> imie_aut;
	//	cout << endl;
	//	cout << "Nazwisko autora " << i + 1 << ":";
	//	cin >> nazwisko_aut;
	//	cout << endl;
	//	autorzy.emplace_back(imie_aut, nazwisko_aut);
	//}

	cout << "Imie autora ksiazki: ";
	cin >> imie_aut;
	cout << endl;

	cout << "Nazwisko autora ksiazki: ";
	cin >> nazwisko_aut;
	cout << endl;

	cout << "Rok wydania ksiazki: ";
	cin >> rok_wydania;
	cout << endl;

	cout << "ISBN ksiazki: ";
	cin >> ISBN;
	cout << endl;

	cout << "Wydawnictwo ksiazki: ";
	cin >> wydawnictwo;
	cout << endl;

	cout << "Liczba stron ksiazki: ";
	cin >> liczba_stron;
	cout << endl;

	cout << "Imie wypozyczajacego: ";
	cin >> imie_wyp;
	cout << endl;

	cout << "Nazwisko wypozyczajacego: ";
	cin >> nazwisko_wyp;
	cout << endl;

	cout << "PESEL wypozyczajacego: ";
	cin >> PESEL;
	cout << endl;

	//cout << "Dzien miesiaca: ";
	//cin >> data_wyp.dzien;
	//cout << endl;

	//cout << "Dzien wypozyczenia: ";
	//cin >> data_wyp.dzien_tyg;
	//cout << endl;

	//cout << "Miesiac wypozyczenia: ";
	//cin >> data_wyp.miesiac;
	//cout << endl;

	//cout << "Rok wypozyczenia: ";
	//cin >> data_wyp.rok;
	//cout << endl;

	//cout << "Godzina wypozyczenia: ";
	//cin >> data_wyp.godzina;
	//cout << endl;

	//cout << "Minuta wypozyczenia: ";
	//cin >> data_wyp.minuta;
	//cout << endl;

	//cout << "Sekunda wypozyczenia: ";
	//cin >> data_wyp.sekunda;
	//cout << endl;

	string chujwiecotubedzie = "1";

	string dodaj_dane_do_autor = "INSERT INTO Autor \
				(ID, imie, nazwisko)\
				VALUES (NULL,'" + imie_aut + "','" + nazwisko_aut + "');";

	kod_bledu = sqlite3_exec(baza, dodaj_dane_do_autor.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z dodaniem do autor" << endl;
	}

	string rok_wydania_string = to_string(rok_wydania);
	auto liczba_stron_string = to_string(liczba_stron);

	string dodaj_dane_do_ksiazka = "INSERT INTO Ksiazka \
				(ID,tytul,ID_autora,rok,ISBN,wydawnictwo,liczba_stron)\
				VALUES (NULL,'" + tytul + "',NULL," + rok_wydania_string + ",'" + ISBN + "','" + wydawnictwo + "'," + liczba_stron_string + ");";

	kod_bledu = sqlite3_exec(baza, dodaj_dane_do_ksiazka.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z dodaniem do ksiazka" << endl;
	}

	string dodaj_dane_do_uzytkownik = "INSERT INTO Uzytkownik \
				VALUES('" + imie_wyp + "','" + nazwisko_wyp + "','" + PESEL + "')";

	kod_bledu = sqlite3_exec(baza, dodaj_dane_do_uzytkownik.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z dodaniem do uzytkownik" << endl;
	}

	string dodaj_dane_do_wypozyczenie = "INSERT INTO Wypozyczenie \
				VALUES(NULL,'" + tytul + "','" + PESEL + "')";

	kod_bledu = sqlite3_exec(baza, dodaj_dane_do_wypozyczenie.c_str(), callback, 0, &blad);
	if (kod_bledu != SQLITE_OK) {
		cout << "problem z dodaniem do wypozyczenie" << endl;
	}



	//data_od.dzien = data_wyp.dzien;
	//if (data_wyp.miesiac >= 10) {
	//	data_od.rok = data_wyp.rok + 1;
	//	data_od.miesiac = data_wyp.miesiac - 9;
	//}
	//else {
	//	data_od.miesiac = data_wyp.miesiac + 3;
	//}
	//data_od.rok = data_wyp.rok;
	//data_od.godzina = data_wyp.godzina;
	//data_od.minuta = data_wyp.minuta;
	//data_od.sekunda = data_wyp.sekunda;
	//data_od.dzien_tyg = data_wyp.dzien_tyg;
	//Ksiazka k(tytul, autorzy, rok, ISBN, wydawnictwo, liczba_stron);
	//Uzytkownik u(imie_wyp, nazwisko_wyp, PESEL);
	//wypozyczalnia.wypozycz_ksiazke(k, u, data_wyp, data_od);

}
