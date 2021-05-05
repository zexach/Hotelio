/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||							    	||
||		Naziv projekta: Hotelio			    	||
||		Zavrsni projekat iz predmeta:	       	    	||
||		Napredne tehnike programiranja              	||
||		Mentor: v. as. mr. Edin Tabak		    	||
||			Autori:		 		    	||
||				Muamer Alickovic            	||
||				Ajdin Bukvic	            	||
||				Emir Zambakovic             	||
||							    	||
|| 			Â© 2021                              	||
||							    	||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

//-------------------- >>> BIBLIOTEKE <<< ---------------------

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

//-------------------- >>> KONSTANTE <<< ---------------------

//-------------------- >>> GLOBALNE VARIJABLE <<< ---------------------
char *linija = "\n=========================================================\n";
char *greska = "[GRESKA]: Pogresan unos, pokusajte ponovo!\n";
//-------------------- >>> ENUMERACIJE <<< ---------------------
//enumeracija za velicinu sobe
enum velicinaSobe {
    jednokrevetna=1,
    dvokrevetna,
    trokrevetna,
	predsjednickiApartman
};

//enumeracija za poziciju radnika
enum pozicijaRadnika {
    recepcioner=1,
    cistac,
    konobar,
    menadzer,
    trener
};

//-------------------- >>> STRUKTURE <<< ---------------------
//struktura soba
struct Soba{
    velicinaSobe velicina;
    float cijena;
    int brojSobe;
    bool slobodna;
};

//struktura rezervacija
struct Rezervacija{
	string ime;
	string prezime;
	Datum datumPrijave;
	Darum datumOdjave;
	
};
//struktura datum
struct Datum {
    int dan,mjesec,godina;
};

//struktura radnik
struct Radnik{
    int id;
    string ime;
    string prezime;
    pozicijaRadnika pozicija;
    double plata;
};

//struktura korisnik
struct Korisnik{
	string ime;
	string prezime;
	string spol;
	string username;
	string password;
};

//struktura hotel
struct Hotel{
	string nazivHotela;
	double stanjeKase;
	int brojSoba;
	int brojDostupnihSoba;
	int brojZauzetihSoba;
	int broj radnika;
};
//-------------------- >>> SPISAK FUNKCIJA <<< ---------------------

//-------------------- >>> MAIN FUNKCIJA <<< ---------------------

int main()
{
	
	return 0;
}

//-------------------- >>> FUNKCIJE <<< ---------------------
