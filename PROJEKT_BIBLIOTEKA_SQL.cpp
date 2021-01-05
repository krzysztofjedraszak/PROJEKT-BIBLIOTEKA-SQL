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
#include "sqlite3.h"
#include "Baza.h"
using namespace std;

int main()
{
	Baza baza;
	baza.odpal();
	return 0;
}

