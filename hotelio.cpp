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
#include <vector>
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

//struktura datum
struct Datum {
    int dan,mjesec,godina;
};
//struktura rezervacija
struct Rezervacija{
	string ime;
	string prezime;
	Datum datumPrijave;
	Datum datumOdjave;
	
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
	int brojRadnika;
};
//-------------------- >>> SPISAK FUNKCIJA <<< ---------------------
void splashscreen();
void poruka(int);
//-------------------- >>> MAIN FUNKCIJA <<< ---------------------

int main()
{
	splashscreen();
	
	return 0;
}

//-------------------- >>> FUNKCIJE <<< ---------------------
void splashscreen(){
	cout<<"\t     __     __    ___________    ______________    ____________    __            __    ___________ "<<endl;
	cout<<"\t    |  |   |  |  |   _____   |  |_____    _____|  |   _________|  |  |          |  |  |   _____   |"<<endl;
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |  |___|  |  |  |     |  |        |  |        |  |_____       |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |   ___   |  |  |     |  |        |  |        |   _____|      |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	cout<<"\t    |  |   |  |  |  |_____|  |        |  |        |  |_________   |  |_______   |  |  |  |_____|  |"<<endl;
	cout<<"\t    |__|   |__|  |___________|        |__|        |____________|  |__________|  |__|  |___________|"<<endl;
	Sleep(3000); 
	system("cls");
}
void poruka(int broj){
	switch(broj){
		case 1:
			cout<<"=========================================================\n";
			break;
		case 2:
			cout<<"Za nastavak pritisnite bilo koju tipku...\n";
			break;
		case 3:
			cout<<"[GRESKA]: Pogresan unos, pokusajte ponovo!\n";
			break;
		case 4:
			cout<<"[GRESKA]: Nema pronadjenih rezultata pretrage!\n";
			break;
		case 5:
			cout<<"[GRESKA]: Nemoguce ucitati fajl!\n";
			break;
		default:
			cout<<"Greska!\n";
			break;
	}
}
