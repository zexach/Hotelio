/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||							    								||
||		Naziv projekta: Hotelio			    					||
||		Zavrsni projekat iz predmeta:	       	    			||
||		Napredne tehnike programiranja              			||
||		Mentor: v. as. mr. Edin Tabak		    				||
||			Autori:		 		    							||
||				Muamer Alickovic            					||
||				Ajdin Bukvic	            					||
||				Emir Zambakovic             					||
||							    								||
|| 			� 2021                                             ||
||							    								||		
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
#include <sstream>
using namespace std;

//-------------------- >>> KONSTANTE <<< ---------------------
const string adminUsername="admin";//postavljamo globalno username za admina
const string adminPassword="admin";//postavljamo globalno sifru za admina 
//-------------------- >>> GLOBALNE VARIJABLE <<< ---------------------

//-------------------- >>> SPISAK FUNKCIJA <<< ---------------------
//kako bi izbjegli preveliko uredjivanje koda, zbog potrebe za koristenjem funkcije u strukturi,ove tri funkcije smo definisali na samom pocetku, jer one ne zahtjevaju nikakve posebne elemente, a potrebene su
//za ralizaciju funkcije dodaj_radnika() u strukturi radnik
int prebroj_clanove(string);
void dodaj_radnika();
void poruka(int);
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

enum stanje_rezervacije {
	cekanje,
	prihvaceno,
	odbijeno
};

enum aktivnosti {
	teretana=1,
	bazen,
	fitness,
	masaza,
	sauna
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
	int kod;
	int broj_sobe;
	string username;
	Datum datumPrijave;
	Datum datumOdjave;
	stanje_rezervacije stanje;
};

//struktura radnik
struct Radnik{
    int id;
    string ime;
    string prezime;
    pozicijaRadnika pozicija;
    double plata;

	//funkcija koja sluzi za dodavanje novih radnika u datoteku
	void dodaj_radnika(){
	Radnik *r = new Radnik;
	int br = prebroj_clanove("radnici.txt");
	int rb = br+1;
	int pozicija_unos;
	ofstream izlaz("radnici.txt", ios::app);
	if(izlaz.is_open()){
		poruka(1);
		cout<<"Dodavanje novog radnika..."<<endl;
		poruka(1);
		cout<<"Unesite ime radnika: ";
		cin>>r->ime;
		cout<<"Unesite prezime radnika: ";
		cin>>r->prezime;
		do{
			cout<<"Pozicija radnika:"<<endl;
			cout<<"Dostupne pozicije: \n1 - Recepcioner\n2 - Cistac\n3 - Konobar\n4 - Menadzer\n5 - Trener\n";
			cout<<"Unesite poziciju radnika: ";
			cin>>pozicija_unos;
			if(pozicija_unos < 1 || pozicija_unos > 5)
			poruka(3);
		}
		while(pozicija_unos < 1 || pozicija_unos > 5);
		r->pozicija = pozicijaRadnika(pozicija_unos);
		do{
			cout<<"Unesite platu radnika: ";
			cin>>r->plata;
			if(r->plata < 100 || r->plata > 2000){
				poruka(3);
				cout<<"Samo u intervalu 100 - 2000 KM"<<endl;
			}
		}
		while(r->plata < 100 || r->plata > 2000);
		izlaz << rb << " " << r->ime << " " << r->prezime << " " << r->pozicija << " " << r->plata << endl;
		poruka(1);
		cout<<"Novi radnik je uspjesno dodan u datoteku radnici.txt..."<<endl;	
		izlaz.close();
		delete r;
	}
	else{
		poruka(5);
		return;
	}
	}
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
struct Racun{
	int id;
	string username;
	float iznos;
	bool placeno;
};

struct dodatneAktivnosti {
	string username;
	aktivnosti aktivnost;
	float cijena;
};
//-------------------- >>> SPISAK FUNKCIJA <<< ---------------------
void splashscreen();
int glavniMenu();
void registracija();
int prebroj_clanove(string);
string skrivena_sifra(string,char);
void prijava(string&,string&,bool&);
void adminPrijava(bool&);
int admin_menu();
void prikazi_rezervacije();
void prihvati_odbij_rezervaciju();
void azuriraj_rezervacije(Rezervacija*,int,int,int);
void promijeni_stanje_sobe(Soba*,int,int);
void pretrazi_sobe();
void uredi_cjenovnik();
void azuriraj_sobe(Soba*,int,int,float);
void izdaj_racun();
int izracunaj_dane(Datum*,Datum*);
float izracunaj_popust(float,int); //REKURZIVNA FUNKCIJA
bool prestupna(int); //-------------
void pregled_racuna();
void stanje_hotela();
void dodaj_radnika();
void isplati_plate();
int korisnikMenu();
void hotelInfo();
void pregledSlobodnihSoba();
void rezervacijaSobe(string);
bool provjera_datuma(Datum*);
bool provjeraDatuma2(Datum*, Datum*);
void rezervacijaDodatnihAktivnosti(string);
void platiRacun(string);
void brisanjeRezervacije(Rezervacija*, int, int);
void aktivnostBrisanje(dodatneAktivnosti*, int, string);
//-------------------- >>> MAIN FUNKCIJA <<< ---------------------

int main() {
	//splashscreen();
	int izbor;
	string korisnickoIme, sifra;
	bool ispravnostKorisnik,ispravnostAdmin;
	while(izbor=glavniMenu()) {
		switch (izbor) {
			case 1: {
				system("cls");
				registracija();
				break;
			}
			case 2: {
				system("cls");
				prijava(korisnickoIme,sifra,ispravnostKorisnik);
				if(ispravnostKorisnik) {//ovaj if sluzi za otvaranje korisnickog menija
						cout<<"Uspjesno ste se prijavili"<<endl;
						Sleep(1000);
						system("cls");
						int odabir;
						while(odabir = korisnikMenu()){
							switch(odabir){
								case 1:{
									system("cls");
									hotelInfo();
									Sleep(5000);
									break;
								}
								case 2:{
									system("cls");
									pregledSlobodnihSoba();
									break;
								}
								case 3:{
									system("cls");
									rezervacijaSobe(korisnickoIme);
									break;
								}
								case 4:{
									system("cls");
									rezervacijaDodatnihAktivnosti(korisnickoIme);
									break;
								}
								case 5:{
									system("cls");
									platiRacun(korisnickoIme);
									break;
								}
							}
							poruka(2);
							getch();
						}
					}
				break;
			}
			case 3: {
				system("cls");
				adminPrijava(ispravnostAdmin);
				if(ispravnostAdmin) {
					cout<<"USPJESNO STE PRIJAVLJENI"<<endl;//OVAJ IF SLUZI ZA OTVARANJE ADMIN MENUA
					Sleep(1000);
					system("cls");
					int odabir;
					while(odabir = admin_menu()) {
						switch (odabir) {
							case 1: {
								system("cls");
								prikazi_rezervacije();
								break;
							}
							case 2: {
								system("cls");
								prihvati_odbij_rezervaciju();
								break;
							}
							case 3: {
								system("cls");
								pretrazi_sobe();
								break;
							}
							case 4: {
								system("cls");
								uredi_cjenovnik();
								break;
							}
							case 5: {
								system("cls");
								izdaj_racun();
								break;
							}
							case 6: {
								system("cls");
								pregled_racuna();
								break;
							}
							case 7: {
								system("cls");
								stanje_hotela();
								break;
							}
							case 8: {
								system("cls");
								Radnik r;
								r.dodaj_radnika();
								break;
							}
							case 9: {
								system("cls");
								isplati_plate();
								break;
							}
						}
						poruka(2);
						getch();
					}
				}
				break;
			}
		}
		poruka(2);
		getch();
	}
	return 0;
}

//-------------------- >>> FUNKCIJE <<< ---------------------
//funkcija koja ispisuje poruku prilikom pokretanja programa
void splashscreen() {
	cout<<"\n\n\n\n\n\n\n\n\n";
	cout<<"\t     __     __    ___________    ______________    ____________    __            __    ___________ "<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |   _____   |  |_____    _____|  |   _________|  |  |          |  |  |   _____   |"<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |  |___|  |  |  |     |  |        |  |        |  |_____       |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |   ___   |  |  |     |  |        |  |        |   _____|      |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |  |     |  |        |  |        |  |            |  |          |  |  |  |     |  |"<<endl;
	Sleep(80);
	cout<<"\t    |  |   |  |  |  |_____|  |        |  |        |  |_________   |  |_______   |  |  |  |_____|  |"<<endl;
	Sleep(80);
	cout<<"\t    |__|   |__|  |___________|        |__|        |____________|  |__________|  |__|  |___________|"<<endl;
	Sleep(3000); 
	system("cls");
}

//funkcija koja pruza odgovarajucu poruku na osnovu greske
void poruka(int broj) {
	switch(broj) {
		case 1:
			cout<<"==============================================================\n";
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
//funkcija za prvi menu
int glavniMenu() {
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\tGLAVNI MENU"<<endl;
	poruka(1);
	cout << "\t\t1. Registracija\n";
	cout << "\t\t2. Prijava\n";
	cout << "\t\t3. Admin prijava\n";
	cout << "\t\t0. Izlaz\n";
	poruka(1);
	int opcija;
	cout<<"\t\tIzaberite opciju: ";
	cin >> opcija;
	if (opcija!=0) return opcija;
	else {
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
}

//funkcija za registraciju novog korisnika
void registracija() {
	int brojac,pomocnaVarijabla=0; //u ovu varijablu spremamo broj clanova u datoteci
	brojac=prebroj_clanove("listaKorisnika.txt");
	Korisnik* korisnici=new Korisnik[brojac];
	//sada cemo kopirati sve elemente u nas dinamicki niz;
	ifstream ulaz1("listaKorisnika.txt");
	if(ulaz1.is_open()){
		Korisnik temp;
		while(ulaz1>>temp.ime>>temp.prezime>>temp.spol>>temp.username>>temp.password){
			korisnici[pomocnaVarijabla++]=temp;
		}
		ulaz1.close();
	}
	else{
		poruka(5);
		return;
	}
	ofstream unos("listaKorisnika.txt", ios::app);
	if(unos.is_open()) {
		bool greska=false;
		int pomDuzina, br=0;;
		Korisnik* k=new Korisnik;
		cout<<"MOLIMO VAS DA ISPRAVNO POPUNITE PODATKE, KAKO BI VAS MOGLI DODATI U SISTEM!"<<endl;
		Sleep(2000);
		system("cls");
		//osigurati cemo da korisnik unese samo slova (velika ili mala) kada je rijec o imenu
		do {
			if(br>0) { //ukoliko je korisnik napravio gresku, ispisujemo poruku, kojom ga obavjestavamo
				cout<<"[GRESKA] Unijeli ste nedozvoljeni karakter!!!"<<endl;
				Sleep(900);
				system("cls");
			}
			cout<<"Unesite ime (dozvoljena su samo velika i mala slova): ";
			cin>>k->ime;
			pomDuzina=k->ime.length();
			for (int i=0; i<pomDuzina; i++) {
				if ((k->ime[i]>64 && k->ime[i]<91) || (k->ime[i]>96 && k->ime[i]<123)) greska=false; //ovako provjeravamo da li je svaki karakter koji je korisnik unio veliko odnosno malo slovo
				else {
					greska=true;
					break;
				}
			}
			br++; //ukoliko se desi greska, povecajemo brojac, da bi mogli ispisati odgovarajucu poruku
		} while(greska);
		k->ime[0]=toupper(k->ime[0]); //ukoliko korisnik unese prvo malo slove prebacujemo ga u veliko jer ime pocinje velikim slovom
		for (int i=1; i<pomDuzina; i++) { //ostala slova prebacujemo u mala
			k->ime[i]=tolower(k->ime[i]);
		}
		unos<<k->ime<<" ";
		br=0; //postavljamo brojac na 0, jer cemo imati jos provjera prilikom unosa gdje ce nam biti potreban brojac, a ne zelimo koristiti nove varijable zbog memorije
		//osiguravamo ispravan unos prezimena
		do {
			if(br>0) { //ukoliko je korisnik napravio gresku, ispisujemo poruku, kojom ga obavjestavamo
				cout<<"[GRESKA] Unijeli ste nedozvoljeni karakter!!!"<<endl;
				Sleep(900);
				system("cls");
				cout<<"Unesite ime (dozvoljena su samo velika i mala slova): ";
				cout<<k->ime<<endl;
			}
			cout<<"Unesite prezime (dozvoljena su samo velika i mala slova): ";
			cin>>k->prezime;
			pomDuzina=k->prezime.length();
			for (int i=0; i<pomDuzina; i++) {
				if ((k->prezime[i]>64 && k->prezime[i]<91) || (k->prezime[i]>96 && k->prezime[i]<123)) greska=false; //ovako provjeravamo da li je svaki karakter koji je korisnik unio veliko odnosno malo slovo
				else {
					greska=true;
					break;
				}
			}
			br++; //ukoliko se desi greska, povecajemo brojac, da bi mogli ispisati odgovarajucu poruku
		} while(greska);
		k->prezime[0]=toupper(k->prezime[0]);
		for (int i=1; i<pomDuzina; i++) {
			k->prezime[i]=tolower(k->prezime[i]);
		}
		unos<<k->prezime<<" ";
		br=0;
		//unos spola
		do {
			if(br>0) {
				cout<<"[GRESKA] Unijeli ste pogresno spol!!!"<<endl;
				Sleep(900);
				system("cls");
				cout<<"Unesite ime (dozvoljena su samo velika i mala slova): ";
				cout<<k->ime<<endl;
				cout<<"Unesite prezime (dozvoljena su samo velika i mala slova): ";
				cout<<k->prezime<<endl;
			}
			cout<<"Unesite spol (muski/zenski): ";
			cin>>k->spol;
			br++;
		} while(k->spol!="muski" && k->spol!="zenski");
		unos<<k->spol<<" ";
		//unos username-a
		do{
			int izlaz=0;
			cout<<"Unesite vase korisnicko ime (mozete koristiti sve karaktere): ";
			cin>>k->username;
			for (int i=0;i<brojac;i++){
				if(k->username==korisnici[i].username || k->username==adminUsername ){
					cout<<"[GRESKA] TO KORISNICKO IME VEC POSTOJI!!!"<<endl;
					Sleep(900);
					izlaz=1;
					system("cls");
					cout<<"Unesite ime (dozvoljena su samo velika i mala slova): ";
					cout<<k->ime<<endl;
					cout<<"Unesite prezime (dozvoljena su samo velika i mala slova): ";
					cout<<k->prezime<<endl;
					cout<<"Unesite spol (muski/zenski): ";
					cout<<k->spol<<endl;
					break;
				}
			}
			if(izlaz==0) break;
		}while(1);
		unos<<k->username<<" ";
		//unos sifre(password-a)
		br=8;
		do {
			if(br<8) {
				cout<<"[GRESKA] Unijeli broj karaktera za sifru nije zadovoljen!!!"<<endl;
				Sleep(900);
				system("cls");
				cout<<"Unesite ime (dozvoljena su samo velika i mala slova): ";
				cout<<k->ime<<endl;
				cout<<"Unesite prezime (dozvoljena su samo velika i mala slova): ";
				cout<<k->prezime<<endl;
				cout<<"Unesite spol (muski/zenski): ";
				cout<<k->spol<<endl;
				cout<<"Unesite vase korisnicko ime (mozete koristiti sve karaktere): ";
				cout<<k->username<<endl;
			}
			cout<<"Unesite sifru (minimalno 8 karaktera): ";
			cin>>k->password;
			br=k->password.length();
		} while(br<8);
		unos<<k->password<<endl;
		unos.close();
		delete k;
	} else {
		poruka(5);
		return;
	}
	delete[] korisnici;
}
//funkcija koja prebrojava clanove u nekoj datoteci
int prebroj_clanove(string naziv_datoteke) {
	//otvaramo datoteku prvi put kako bi izbrojali broj elemenata u datoteci
	string linija;
	int brojac = 0;
	ifstream ulaz(naziv_datoteke);
	if (ulaz.is_open()) {
		while(getline(ulaz, linija)) {
			brojac++;
		}
		ulaz.close();
	} else {
		poruka(5);
		return 0;
	}
	return brojac;
}

//funkcija za prijavu u sistem (prijavu korisnika)
void prijava(string& korisnickoIme, string& sifra, bool& ispravnost) {
	ispravnost=false;
	bool rezultat = false;
	int broj=0, brojElemenata, brojPokusaja=0,brojac=0;
	brojElemenata = prebroj_clanove("listaKorisnika.txt");
	Korisnik* korisnici=new Korisnik[brojElemenata];//kreiramo niz od tacno onoliko elemenata oliko ima u datoteci
	ifstream noviUlaz("listaKorisnika.txt"); //otvaramo datoteku drugi put kako bi kopirali elemenete u niz
	if (noviUlaz.is_open()) {
		Korisnik temp;
		while(noviUlaz>>temp.ime>>temp.prezime>>temp.spol>>temp.username>>temp.password) {
			korisnici[broj]=temp;
			broj++;
		}
		noviUlaz.close();
	} else {
		poruka(5);
		return;
	}
	broj = 0;
	do { //koristimo do - while petlju kako bi omogucili korisniku unos korisnickog imena, te ukoliko napravi odredjeni broj pogresaka vracamo ga na pcetak
		if(broj > 0) {
			cout<<"POGRESNO STE UNIJELI KORISNICKO IME!!!"<<endl;
			Sleep(900);
			brojPokusaja++;
			system("cls");
		}
		if(brojPokusaja == 3) {
			cout<<"PREMASILI STE BROJ DOZVOLJENIH POKUSAJA, MORAMO VAS VRATITI NA POCETAK!!!"<<endl;
			Sleep(900);
			return;
		}
		cout<<"Unesite korisnicko ime: ";
		cin>>korisnickoIme;
		for (int i = 0; i < brojElemenata; i++) {
			if(korisnickoIme == korisnici[i].username) {
				rezultat = true;
				brojac++;
				break;
			}
		}
		broj++;
	} while(!rezultat);
	broj = 0;
	brojPokusaja = 0;
	rezultat = false;
	do { //istu stvar radimo i za sifru
		if(broj > 0) {
			cout<<"POGRESNO STE UNIJELI SIFRU!!!"<<endl;
			Sleep(900);
			brojPokusaja++;
			system("cls");
			cout<<"Unesite korisnicko ime: ";
			cout<<korisnickoIme<<endl;
		}
		if (brojPokusaja == 3) {
			cout<<"PREMASILI STE BROJ DOZVOLJENIH POKUSAJA, MORAMO VAS VRATITI NA POCETAK!!!"<<endl;
			Sleep(900);
			return;
		}
		char znak;
		cout<<"Unesite sifru: ";
		sifra = skrivena_sifra(sifra, znak);
		cout<<endl;
		for (int i = 0; i < brojElemenata; i++) {
			if(sifra == korisnici[i].password) {
				rezultat = true;
				brojac++;
				break;
			}
		}
		broj++;
	} while(!rezultat);
	if(brojac<3) { //ukoliko su username i sifra ispravno uneseni, ispravnost postavljamo na true, to ce nam trebati da mozemo dalje raditi u programu
		ispravnost=true;
	}
	delete[] korisnici;
}

//funckija za prijavu admina
void adminPrijava(bool& ispravnost) {
	int broj=0, brojPokusaja=0, brojac=0;
	bool rezultat=false;
	string korisnickoIme, sifra;
	ispravnost=false;
	do {
		if(broj > 0) {
			cout<<"POGRESNO STE UNIJELI KORISNICKO IME!!!"<<endl;
			Sleep(900);
			brojPokusaja++;
			system("cls");
		}
		if(brojPokusaja == 3) {
			cout<<"PREMASILI STE BROJ DOZVOLJENIH POKUSAJA, MORAMO VAS VRATITI NA POCETAK!!!"<<endl;
			Sleep(900);
			return;
		}
		cout<<"Unesite korisnicko ime: ";
		cin>>korisnickoIme;
		if(korisnickoIme == adminUsername) {
			rezultat = true;
			brojac++;
			break;
		}
		broj++;
	} while(!rezultat);
	broj = 0;
	brojPokusaja = 0;
	rezultat = false;
	do {
		if(broj > 0) {
			cout<<"POGRESNO STE UNIJELI SIFRU!!!"<<endl;
			Sleep(900);
			brojPokusaja++;
			system("cls");
			cout<<"Unesite korisnicko ime: ";
			cout<<korisnickoIme<<endl;
		}
		if (brojPokusaja == 3) {
			cout<<"PREMASILI STE BROJ DOZVOLJENIH POKUSAJA, MORAMO VAS VRATITI NA POCETAK!!!"<<endl;
			Sleep(900);
			return;
		}
		char znak;
		cout<<"Unesite sifru: ";
		sifra = skrivena_sifra(sifra, znak);
		cout<<endl;
		if(sifra == adminPassword) {
			rezultat = true;
			brojac++;
			break;
		}
		broj++;
	} while(!rezultat);

	if(brojac<3) {
		ispravnost=true;
	}
}
//funkcija koja sluzi za unos sifre bez prikazivanja karaktera
string skrivena_sifra(string sifra, char znak) {
	sifra.clear();
	while(znak = getch()){
  		if(znak == 13) {
            return sifra;
        }
        else if(znak == 8 && sifra.size() != 0) {
            sifra.erase(sifra.size() - 1);
  			cout<<"\b \b";
  			continue;
        }
  		else if(znak == 8 && sifra.size() == 0) {
            continue;
        }
  		sifra += znak;
        cout<<"*";
    }
}
//funkcija za admin menu
int admin_menu() {
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\tADMIN MENU"<<endl;
	poruka(1);
	cout << "\t\t1. Prikazi rezervacije\n";
	cout << "\t\t2. Prihvati / odbaci rezervaciju\n";
	cout << "\t\t3. Pretrazi sobe po kriterijima\n";
	cout << "\t\t4. Uredi cjenovnik\n";
	cout << "\t\t5. Izdaj racun\n";
	cout << "\t\t6. Pregled svih racuna\n";
	cout << "\t\t7. Informacije / stanje hotela\n";
	cout << "\t\t8. Dodaj radnika\n";
	cout << "\t\t9. Isplati plate radnicima\n";
	cout << "\t\t0. Odjava\n";
	poruka(1);
	int opcija;
	cout<<"\t\tIzaberite opciju: ";
	cin >> opcija;
	if (opcija!=0) return opcija;
	else {
		cout<<"\nUspjesno ste se odjavili iz admin menua!\n";
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
}
//funkcija koja ispisuje sve rezervacije koje se nalaze u datoteci rezervacije.txt
void prikazi_rezervacije(){
	Rezervacija *r = new Rezervacija;
	int broj;
	string temp;
	int br_rezervacija = prebroj_clanove("rezervacije.txt");
	if(br_rezervacija == 0){
		cout<<"Trenutno nema aktivnih rezervacija!"<<endl;
		return;
	}
	cout<<"-----------------------------------------------------------------------------------------\n";
	cout<<left<<setw(8)<<"Kod"<<setw(15)<<"Broj sobe"<<setw(15)<<"Username"<<setw(20)<<"Prijava"<<setw(20)<<"Odjava"<<setw(15)<<"Stanje"<<endl;
	cout<<"-----------------------------------------------------------------------------------------\n";
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		while(ulaz >> r->kod >> r->broj_sobe >> r->username >> r->datumPrijave.dan >> r->datumPrijave.mjesec >> r->datumPrijave.godina
			>> r->datumOdjave.dan >> r->datumOdjave.mjesec >> r->datumOdjave.godina >> broj){
			if(broj == 0) temp = "Cekanje";
			else temp = "Prihvaceno";
			string tacka=".";
			stringstream dP;
			dP<<r->datumPrijave.dan<<tacka<<r->datumPrijave.mjesec<<tacka<<r->datumPrijave.godina;
			string datumPrijave=dP.str();
			stringstream dO;
			dO<<r->datumOdjave.dan<<tacka<<r->datumOdjave.mjesec<<tacka<<r->datumOdjave.godina;
			string datumOdjave=dO.str();
			cout<<left<<setw(8)<<r->kod<<setw(15)<<r->broj_sobe<<setw(15)<<r->username<<setw(20)<<datumPrijave<<setw(20)<<datumOdjave<<setw(15)<<temp<<endl;
		}
		ulaz.close();
		cout<<"-----------------------------------------------------------------------------------------\n";
		delete r;	
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja na osnovu unesenog koda rezervacije mijenja stanje rezervacije
void prihvati_odbij_rezervaciju(){
	Rezervacija *r = new Rezervacija;
	int unos;
	int izbor;
	int stanje;
	int br = 0;
	int pozicija;
	int soba;
	bool postoji = false;
	int br_rezervacija = prebroj_clanove("rezervacije.txt");
	if(br_rezervacija == 0){
		cout<<"Trenutno nema aktivnih rezervacija!"<<endl;
		return;
	}
	Rezervacija *niz = new Rezervacija[br_rezervacija];
	cout<<"Unesite kod rezervacije koju zelite prihvatiti / odbiti: ";
	cin>>unos;
	do{
		cout<<"1 - PRIHVATANJE | 2 - ODBIJANJE : ";
		cin>>izbor;
	}
	while(izbor < 1 || izbor > 2);	
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		while(ulaz >> r->kod >> r->broj_sobe >> r->username >> r->datumPrijave.dan >> r->datumPrijave.mjesec >> r->datumPrijave.godina
			>> r->datumOdjave.dan >> r->datumOdjave.mjesec >> r->datumOdjave.godina >> stanje){
			if(stanje == 0) r->stanje = cekanje;
			else r->stanje = prihvaceno;
			niz[br] = *r;
			br++;
			if(unos == r->kod){
				postoji = true;
				if(izbor == 1 && r->stanje == cekanje){
					cout<<"Uspjesno ste prihvatili rezervaciju!"<<endl;
					soba = r->broj_sobe;
				}
				else if(izbor == 2 && r->stanje == cekanje){
					cout<<"Uspjesno ste odbili rezervaciju!"<<endl;
				}
				else if((izbor == 1 || izbor == 2) && r->stanje == prihvaceno){
					cout<<"Ova rezervacija je vec prihvacena!"<<endl;
					return;
				}
				pozicija = br-1;
			}
		}
		ulaz.close();
		if(!postoji){
			cout<<"Ne postoji uneseni kod rezervacije!"<<endl;
			return;
		}
		else{
		azuriraj_rezervacije(niz, br_rezervacija, pozicija, izbor);
		}
		delete r;
		delete[] niz;	
	}
	else{
		poruka(5);
		return;
	}
	int br_soba = prebroj_clanove("sobe.txt");
	Soba *s = new Soba;
	Soba *sobe_niz = new Soba[br_soba];
	int soba_brojac = 0;
	int velicina_broj;
	int pozicija_soba;
	ifstream ulaz2("sobe.txt");
	if(ulaz2.is_open()){
		while(ulaz2 >> s->brojSobe >> s->cijena >> velicina_broj >> s->slobodna){
			if(velicina_broj == 1) s->velicina = jednokrevetna;
			else if(velicina_broj == 2) s->velicina = dvokrevetna;
			else if(velicina_broj == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;
			sobe_niz[soba_brojac] = *s;
			soba_brojac++;
			if(soba == s->brojSobe){
				pozicija_soba = soba_brojac-1;
			}
		}
		ulaz2.close();
		promijeni_stanje_sobe(sobe_niz, br_soba, pozicija_soba);
		delete s;
		delete[] sobe_niz;	
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja mijenja sve promjene rezervacija u datoteci
void azuriraj_rezervacije(Rezervacija *niz, int br_rezervacija, int pozicija, int izbor){
	string linija;
	ofstream izlaz("rezervacije.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_rezervacija; i++){
			if(i == pozicija && izbor == 1){
				izlaz<<niz[i].kod<<" "<<niz[i].broj_sobe<<" "<<niz[i].username<<" "<<niz[i].datumPrijave.dan<<" "<<niz[i].datumPrijave.mjesec<<" "<<niz[i].datumPrijave.godina<<" "
					<<niz[i].datumOdjave.dan<<" "<<niz[i].datumOdjave.mjesec<<" "<<niz[i].datumOdjave.godina<<" "<<izbor<<endl;
			}
			else if(i == pozicija && izbor == 2){
				izlaz << "odbijeno" << endl;
			}
			else{
				izlaz<<niz[i].kod<<" "<<niz[i].broj_sobe<<" "<<niz[i].username<<" "<<niz[i].datumPrijave.dan<<" "<<niz[i].datumPrijave.mjesec<<" "<<niz[i].datumPrijave.godina<<" "
					<<niz[i].datumOdjave.dan<<" "<<niz[i].datumOdjave.mjesec<<" "<<niz[i].datumOdjave.godina<<" "<<niz[i].stanje<<endl;
			}
		}
	izlaz.close();	
	}
	else{
		poruka(5);
		return;
	}
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		ofstream novi_izlaz("azurirano.txt");
		if(novi_izlaz.is_open()){
			while(getline(ulaz,linija)){
				if(linija != "odbijeno"){
					novi_izlaz << linija << endl;
				}
			}
		novi_izlaz.close();	
		}
		else{
			poruka(5);
			return;
		}
	ulaz.close();
	remove("rezervacije.txt");
	rename("azurirano.txt","rezervacije.txt");
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja slobodnu sobu postavlja na zauzeto stanje
void promijeni_stanje_sobe(Soba *sobe_niz, int br_soba, int soba_pozicija){
	bool zauzeta = true;
	ofstream izlaz("sobe.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_soba; i++){
			if(i == soba_pozicija){
				izlaz << sobe_niz[i].brojSobe << " " << sobe_niz[i].cijena << " " << sobe_niz[i].velicina << " " << zauzeta << endl;	
			}
			else{
				izlaz << sobe_niz[i].brojSobe << " " << sobe_niz[i].cijena << " " << sobe_niz[i].velicina << " " << sobe_niz[i].slobodna << endl;
			}
		}
	izlaz.close();
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja na osnovu unosa ispisuje sobe prema tom kriteriju
void pretrazi_sobe(){
	string pojam;
	string krevet;
	string stanje;
	int velicina_broj;
	int brojac = 0;
	cout<<"Pretraga soba prema odredjenom kriteriju"<<endl;
	cout<<"Dostupni pojmovi: jednokrevetna | dvokrevetna | trokrevetna | apartman | zauzeta | slobodna"<<endl;
	do{
		pojam.clear();
		cout<<"Unesite pojam: ";
		cin>>pojam;
		if(pojam != "jednokrevetna" && pojam != "dvokrevetna" && pojam != "trokrevetna" && pojam != "apartman" && pojam != "zauzeta" && pojam != "slobodna")
		poruka(3);
	}
	while(pojam != "jednokrevetna" && pojam != "dvokrevetna" && pojam != "trokrevetna" && pojam != "apartman" && pojam != "zauzeta" && pojam != "slobodna");
	poruka(1);
	cout<<left<<setw(15)<<"Broj sobe"<<setw(15)<<"Cijena (KM)"<<setw(20)<<"Velicina"<<setw(20)<<"Stanje"<<endl;
	poruka(1);
	Soba *s = new Soba;
	ifstream ulaz("sobe.txt");
	if(ulaz.is_open()){
		while(ulaz >> s->brojSobe >> s->cijena >> velicina_broj >> s->slobodna){
			if(velicina_broj == 1) krevet = "jednokrevetna";
			else if(velicina_broj == 2) krevet = "dvokrevetna";
			else if(velicina_broj == 3) krevet = "trokrevetna";
			else krevet = "apartman";
			if(s->slobodna) stanje = "zauzeta";
			else stanje = "slobodna";
			if(pojam == krevet || pojam == stanje){
				brojac++;
				cout<<left<<setw(15)<<s->brojSobe<<setw(15)<<s->cijena<<setw(20)<<krevet<<setw(20)<<stanje<<endl;
			}
		}
		ulaz.close();
		delete s;
	}
	else{
		poruka(5);
		return;
	}
	if(brojac == 0){
		poruka(4);
		return;
	}
	poruka(1);
}
void uredi_cjenovnik(){
	int broj;
	float nova_cijena;
	int velicina_broj;
	int br_soba = prebroj_clanove("sobe.txt");
	do{
		cout<<"Unesite broj sobe kojoj zelite promijeniti cijenu: ";
		cin>>broj;
		if(broj < 1 || broj > br_soba){
			poruka(3);
			cout<<"Samo u intervalu 1 - "<<br_soba<<endl;
		}
	}
	while(broj < 1 || broj > br_soba);
	do{
		cout<<"Unesite novu cijenu sobe: ";
		cin>>nova_cijena;
		if(nova_cijena < 50){
			poruka(3);
			cout<<"Samo cijene vece od 50 KM!"<<endl;
		}
	}
	while(nova_cijena < 50);
	Soba *s = new Soba;
	Soba *niz = new Soba[br_soba];
	int br = 0;
	int pozicija;
	ifstream ulaz("sobe.txt");
	if(ulaz.is_open()){
		while(ulaz >> s->brojSobe >> s->cijena >> velicina_broj >> s->slobodna){
			if(velicina_broj == 1) s->velicina = jednokrevetna;
			else if(velicina_broj == 2) s->velicina = dvokrevetna;
			else if(velicina_broj == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;
			niz[br] = *s;
			br++;
			if(broj == s->brojSobe){
				pozicija = br-1;
			}
		}
		ulaz.close();
		azuriraj_sobe(niz, br_soba, pozicija, nova_cijena);
		delete s;
		cout<<"Uspjesno ste promijenili cijenu sobe!"<<endl;
	}
	else{
		poruka(5);
		return;
	}
	
}
//funkcija koja mijenja cijenu u datoteci za unesenu sobu
void azuriraj_sobe(Soba *niz, int br_soba, int pozicija, float nova_cijena){
	ofstream izlaz("sobe.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_soba; i++){
			if(i == pozicija){
				izlaz << niz[i].brojSobe << " " << nova_cijena << " " << niz[i].velicina << " " << niz[i].slobodna << endl;	
			}
			else{
				izlaz << niz[i].brojSobe << " " << niz[i].cijena << " " << niz[i].velicina << " " << niz[i].slobodna << endl;
			}
		}
	izlaz.close();
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja izdaje racun korisniku na osnovu unesenog username
void izdaj_racun(){
	string unos;
	bool platio = true;
	cout<<"Unesite username korisnika kojem zelite izdati racun: ";
	cin>>unos;
	Racun *rac = new Racun;
	ifstream ulaz0("racuni.txt");
	if(ulaz0.is_open()){
		while(ulaz0 >> rac->id >> rac->username >> rac->iznos >> rac->placeno){
			if(unos == rac->username && !rac->placeno){
				platio = false;
				break;
			}
		}
		ulaz0.close();
		delete rac;
		if(!platio){
			cout<<"Ne mozete izdati racun korisniku koji vec ima neplacen racun!"<<endl;
			return;
		}
	}
	else{
		poruka(5);
		return;
	}
	int stanje;
	Datum *d1 = new Datum;
	Datum *d2 = new Datum;
	int br_sobe;
	bool postoji = false;
	Rezervacija *r = new Rezervacija;
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		while(ulaz >> r->kod >> r->broj_sobe >> r->username >> r->datumPrijave.dan >> r->datumPrijave.mjesec >> r->datumPrijave.godina
			>> r->datumOdjave.dan >> r->datumOdjave.mjesec >> r->datumOdjave.godina >> stanje){
			if(stanje == 0) r->stanje = cekanje;
			else r->stanje = prihvaceno;
			if(unos == r->username && r->stanje == prihvaceno){
				postoji = true;
				br_sobe = r->broj_sobe;
				d1->dan = r->datumPrijave.dan;
				d1->mjesec = r->datumPrijave.mjesec;
				d1->godina = r->datumPrijave.godina;
				d2->dan = r->datumOdjave.dan;
				d2->mjesec = r->datumOdjave.mjesec;
				d2->godina = r->datumOdjave.godina;
				break;
			}
		}
		ulaz.close();
		delete r;
		if(!postoji){
			cout<<"Ne postoji uneseni username ili korisnik nema prihvacenu rezervaciju!"<<endl;
			return;
		}
	}
	else{
		poruka(5);
		return;
	}
	Soba *s = new Soba;
	float cijena_sobe;
	int velicina_broj;
	ifstream ulaz2("sobe.txt");
	if(ulaz2.is_open()){
		while(ulaz2 >> s->brojSobe >> s->cijena >> velicina_broj >> s->slobodna){
			if(velicina_broj == 1) s->velicina = jednokrevetna;
			else if(velicina_broj == 2) s->velicina = dvokrevetna;
			else if(velicina_broj == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;
			if(br_sobe == s->brojSobe){
				cijena_sobe = s->cijena;
				break;
			}
		}
		ulaz2.close();
		delete s;
	}
	else{
		poruka(5);
		return;
	}
	dodatneAktivnosti *dA = new dodatneAktivnosti;
	float aktivnosti_cijena = 0;
	int aktivirano;
	ifstream ulaz3("dodatneAktivnosti.txt");
	if(ulaz3.is_open()){
		while(ulaz3 >> dA->username >> aktivirano >> dA->cijena){
			if(aktivirano == 1) dA->aktivnost = teretana;
			else if(aktivirano == 2) dA->aktivnost = bazen;
			else if(aktivirano == 3) dA->aktivnost = fitness;
			else if(aktivirano == 4) dA->aktivnost = masaza;
			else dA->aktivnost = sauna;
			if(unos == dA->username){
				aktivnosti_cijena += dA->cijena;
			}
		}
		ulaz3.close();
		delete dA;
	}
	else{
		poruka(5);
		return;
	}
	//------------------------------------------------------------------
	int br_dana = izracunaj_dane(d1,d2);
	float ukupna_cijena = (cijena_sobe + aktivnosti_cijena) * br_dana;
	float konacna_cijena;
	cout<<"Uspjesno ste izdali racun korisniku: "<<unos<<endl;
	cout<<"Podaci su spremljeni u datoteku racuni.txt..."<<endl;
	delete d1;
	delete d2;
	if(br_dana > 5){
		konacna_cijena = izracunaj_popust(ukupna_cijena,br_dana);
		cout<<"Broj dana rezervacije je "<<br_dana<<", te korisnik ima aktiviran popust!"<<endl;
	}
	else{
		konacna_cijena = ukupna_cijena;
		cout<<"Broj dana rezervacije je "<<br_dana<<", te korisnik nema aktiviran popust!"<<endl;
	}
	cout<<"Cijena sobe: "<<cijena_sobe*br_dana<<endl;
	cout<<"Cijena dodatnih aktivnosti: "<<aktivnosti_cijena*br_dana<<endl;
	cout<<"Ukupna cijena racuna: "<<ukupna_cijena<<" KM!"<<endl;
	cout<<"Konacni racun iznosi: "<< fixed << setprecision(2) << konacna_cijena <<" KM!"<<endl;
	//------------------------------------------------------------------
	bool placeno = false;
	srand(time(NULL));
	rand();
	int temp = rand()%900+100;
	ofstream izlaz("racuni.txt", ios::app);
	if(izlaz.is_open()){
		izlaz << temp << " " << unos << " " << fixed << setprecision(2) << konacna_cijena << " " << placeno << endl;
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija koja provjerava da li je godina prestupna
bool prestupna(int godina) {
	return (godina % 4 == 0) && (godina % 100 != 0 || godina % 400 == 0);
}
//funkcija koja racuna broj dana izmedju datuma prijava i datuma odjave
int izracunaj_dane(Datum *d1, Datum *d2){
	int br_dana_d1 = 0; 
	int br_dana_d2 = 0; 
	int razlika; 
	int dani_u_mjesecu[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
	for(int i=1; i<d1->godina; i++){
		if(prestupna(i)) br_dana_d1 += 366;
		else br_dana_d1 += 365;
	}
	for(int i=1; i<d1->mjesec; i++){
		br_dana_d1 += dani_u_mjesecu[i-1];
	}
	br_dana_d1 += d1->dan;
	for(int i=1; i<d2->godina; i++){
		if(prestupna(i)) br_dana_d2 += 366;
		else br_dana_d2 += 365;
	}
	for(int i=1; i<d2->mjesec; i++){
		br_dana_d2 += dani_u_mjesecu[i-1];
	}
	br_dana_d2 += d2->dan;
	razlika = br_dana_d2 - br_dana_d1;
	return razlika; 
}
//REKURZIVNA FUNKCIJA koja racuna popust na cijenu
float izracunaj_popust(float konacna_cijena, int br_dana){
	if(br_dana == 0) return konacna_cijena;
	else{
		br_dana--;
		konacna_cijena -= konacna_cijena*1.05 / 100;
		izracunaj_popust(konacna_cijena,br_dana);
	}
}
//funkcija koja ispisuje listu svih racuna iz datoteke
void pregled_racuna(){
	int brojac = 0;
	poruka(1);
	cout<<setw(5)<<"ID"<<setw(20)<<"Username"<<setw(15)<<"Iznos"<<setw(15)<<"Placeno"<<endl;
	poruka(1);
	Racun *r = new Racun;
	ifstream ulaz("racuni.txt");
	if(ulaz.is_open()){
		while(ulaz >> r->id >> r->username >> r->iznos >> r->placeno){
			brojac++;
			if(r->placeno){
				cout<<setw(5)<<r->id<<setw(18)<<r->username<<setw(18)<<r->iznos<<setw(12)<<"DA"<<endl;
			}
			else{
				cout<<setw(5)<<r->id<<setw(18)<<r->username<<setw(18)<<r->iznos<<setw(12)<<"NE"<<endl;
			}
		}
		ulaz.close();
		delete r;
	}
	else{
		poruka(5);
		return;
	}
	if(brojac == 0){
		poruka(4);
		return;
	}
	poruka(1);
}
//funkcija koja ispisuje sve informacije o hotelu i njegovom stanju
void stanje_hotela(){
	float hotel_racun;
	ifstream ulaz("hotel.txt");
	if(ulaz.is_open()){
		ulaz >> hotel_racun;
		ulaz.close();
	}
	else{
		poruka(5);
		return;
	}
	int br_soba = prebroj_clanove("sobe.txt");
	int br_korisnika = prebroj_clanove("listaKorisnika.txt");
	int br_radnika = prebroj_clanove("radnici.txt");
	Soba *s = new Soba;
	int br_slobodnih = 0;
	int br_zauzetih = 0;
	int velicina_broj;
	ifstream ulaz2("sobe.txt");
	if(ulaz2.is_open()){
		while(ulaz2 >> s->brojSobe >> s->cijena >> velicina_broj >> s->slobodna){
			if(velicina_broj == 1) s->velicina = jednokrevetna;
			else if(velicina_broj == 2) s->velicina = dvokrevetna;
			else if(velicina_broj == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;
			if(s->slobodna){
				br_zauzetih++;
			}
			else{
				br_slobodnih++;
			}
		}
		ulaz2.close();
		delete s;
	}
	else{
		poruka(5);
		return;
	}
	poruka(1);
	cout<<"\t\tStatistika hotela"<<endl;
	poruka(1);
	cout<<"Stanje na racunu: "<<hotel_racun<<" KM"<<endl;
	cout<<"Broj registrovanih korisnika: "<<br_korisnika<<endl;
	cout<<"Ukupno soba: "<<br_soba<<endl;
	cout<<"Broj zauzetih soba: "<<br_zauzetih<<endl;
	cout<<"Broj slobodnih soba: "<<br_slobodnih<<endl;
	cout<<"Ukupno radnika: "<<br_radnika<<endl;
	poruka(1);
	cout<<"\t\tInformacije o radnicima"<<endl;
	poruka(1);
	Radnik *r = new Radnik;
	int pozicija;
	string temp;
	cout<<left<<setw(5)<<"ID"<<setw(15)<<"Ime"<<setw(20)<<"Prezime"<<setw(15)<<"Pozicija"<<setw(8)<<"Plata"<<endl;
	poruka(1);
	ifstream ulaz3("radnici.txt");
	if(ulaz3.is_open()){
		while(ulaz3 >> r->id >> r->ime >> r->prezime >> pozicija >> r->plata){
			if(pozicija == 1) temp = "recepcioner";
			else if(pozicija == 2) temp = "cistac";
			else if(pozicija == 3) temp = "konobar";
			else if(pozicija == 4) temp = "menadzer";
			else temp = "trener";
			cout<<left<<setw(5)<<r->id<<setw(15)<<r->ime<<setw(20)<<r->prezime<<setw(15)<<temp<<setw(8)<<r->plata<<endl; 
		}
		ulaz3.close();
		delete r;
		poruka(1);
	}
	else{
		poruka(5);
		return;
	}
		
}
//funkcija koja isplacuje platu svim radnicima od ukupnog novca na racunu hotela
void isplati_plate(){
	float hotel_racun;
	ifstream ulaz("hotel.txt");
	if(ulaz.is_open()){
		ulaz >> hotel_racun;
		ulaz.close();
	}
	else{
		poruka(5);
		return;
	}
	float ukupna_plata = 0;
	int pozicija;
	Radnik *r = new Radnik;
	ifstream ulaz2("radnici.txt");
	if(ulaz2.is_open()){
		while(ulaz2 >> r->id >> r->ime >> r->prezime >> pozicija >> r->plata){
			ukupna_plata += r->plata;
		}
		ulaz2.close();
		delete r;
	}
	else{
		poruka(5);
		return;
	}
	if(ukupna_plata > hotel_racun){
		cout<<"Nemate dovoljno novca na racunu hotela za isplatu plate radnicima!"<<endl;
		return;
	}
	else{
		cout<<"Uspjesno ste isplatili plate svim radnicima hotela!"<<endl;
		cout<<"Ukupna plata radnika iznosi: "<<ukupna_plata<<" KM!"<<endl;
		cout<<"Staro stanje racuna hotela: "<<hotel_racun<<" KM!"<<endl;
		cout<<"Novo stanje racuna hotela: "<<hotel_racun - ukupna_plata<<" KM!"<<endl;
	}
	ofstream izlaz("hotel.txt");
	if(izlaz.is_open()){
		izlaz << hotel_racun - ukupna_plata;
	}
	else{
		poruka(5);
		return;
	}
}
//funkcija za korisnik menu
int korisnikMenu(){
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\t\tKorisnicki menu"<<endl;
	cout << "\t\t1. Informacije o hotelu\n";
	cout << "\t\t2. Pregled slobodnih soba\n";
	cout << "\t\t3. Rezervacija sobe\n";
	cout << "\t\t4. Rezervacija dodatnih aktivnosti\n";
	cout << "\t\t5. Placanje racuna\n";
	cout << "\t\t0. Izlaz\n";
	poruka(1);
	int opcija;
	cout<<"\t\tIzaberite opciju: ";
	cin >> opcija;
	if (opcija!=0) return opcija;
	else {
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
}
//funkcija koja ispisuje informacije o hotelu
void hotelInfo(){
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\tINFORMACIJE O HOTELU\n";
	cout<<"\tSavrsen balans tradicije i modernih sadrzaja. \n"; 
	cout<<"\tSmjesten u srcu Sarajeva, Hotelio predstavlja \n\tidealan izbor turistima i poslovnim gostima.\n"; 
	cout<<"\tNa samo nekoliko koraka nalaze se sve glavne \n\tgradske atrakcije, znacajne kulturne i poslovne \n\tinstitucije, shopping zone i mnoge druge \n\tzanimljive lokacije."<<endl;
	poruka(1);
}
//funkcija koja ispisuje slobodne sobe u korisnik menuu
void pregledSlobodnihSoba(){
	system("cls");
	int kriterij, velicinaBroj;
	float min, max;
	string krevet, stanje;
	cout<<"Pretraga slobodnih soba prema odredjenom kriteriju"<<endl;
	cout<<"Izaberite broj za zeljeni kriterij: 1. Jednokrevetne 2. Dvokrevetne 3. Trokrevetne 4. Apartmani"<<endl;
	//unos nekog od zeljenog kriterija (ograniceno na unos brojeva 1-4)
	do{
		cout<<"Unesite broj: ";
		cin>>kriterij;
		if(!cin){
			cin.clear();
			cin.ignore(100, '\n');
			poruka(3);
			return;
		}
		if(kriterij != 1 && kriterij != 2 && kriterij != 3 && kriterij != 4){
			poruka(3);
		}
	}
	while(kriterij != 1 && kriterij != 2 && kriterij != 3 && kriterij != 4);
	cout<<"Unesite minimalnu cijenu sobe: ";
	cin>>min;
	if(!cin){
		cin.clear();
		cin.ignore(100, '\n');
		poruka(3);
		return;
	}
	do{
		cout<<"Unesite maksimalnu cijenu sobe: ";
		cin>>max;
		if(!cin){
			cin.clear();
			cin.ignore(100, '\n');
			poruka(3);
			return;
		}
		if(max<min){
			poruka(3);
			cout<<"Maksimalna cijena sobe mora biti veca od minimalne"<<endl;
		}
	}while(max<min);
	poruka(1);
	//ispis sobe prema datom kriteriju iz datoteke sobe.txt
	cout<<setw(5)<<"Broj sobe"<<setw(14)<<"Cijena(KM)"<<setw(15)<<"Velicina"<<setw(15)<<endl;
	Soba *s=new Soba;
	ifstream ispis("sobe.txt");
	if(ispis.is_open()){
		while(ispis>>s->brojSobe>>s->cijena>>velicinaBroj>>s->slobodna){
			if(velicinaBroj == 1) {
				krevet = "jednokrevetna";
			}
			else if(velicinaBroj == 2) {
				krevet = "dvokrevetna";	
			}
			else if(velicinaBroj == 3) {
				krevet = "trokrevetna";
			}
			else {
				krevet = "apartman";
			}
			if(s->slobodna) stanje = "zauzeta";
			else stanje = "slobodna";
			if(s->cijena>=min && s->cijena<=max){
				switch(kriterij){
					case 1:
						if(kriterij == 1 && velicinaBroj==1 && stanje=="slobodna") cout<<setw(5)<<s->brojSobe<<setw(16)<<s->cijena<<setw(18)<<krevet<<setw(15)<<endl;
						break;
					case 2:
						if(kriterij == 2 && velicinaBroj==2 && stanje=="slobodna") cout<<setw(5)<<s->brojSobe<<setw(16)<<s->cijena<<setw(18)<<krevet<<setw(15)<<endl;
						break;
					case 3:
						if(kriterij == 3 && velicinaBroj==3 && stanje=="slobodna") cout<<setw(5)<<s->brojSobe<<setw(16)<<s->cijena<<setw(18)<<krevet<<setw(15)<<endl;
						break;			
					case 4:
						if(kriterij == 4 && velicinaBroj==4 && stanje=="slobodna") cout<<setw(5)<<s->brojSobe<<setw(16)<<s->cijena<<setw(18)<<krevet<<setw(15)<<endl;
						break;								
				}	
			}
			
		}
	poruka(1);	
	ispis.close();
	delete s;
	}
	else{
		poruka(5);
		return;
	}
	
}
//funkcija za rezervaciju sobe
void rezervacijaSobe(string user){
	system("cls");
	int redniBroj, brojSoba, velicinaBroj, stanje=0, velicinaSobe;
	Soba *s=new Soba;
	Datum *datumPrijave=new Datum;
	Datum *datumOdjave=new Datum;
	Rezervacija *r=new Rezervacija;
	Racun *rac=new Racun;
	brojSoba=prebroj_clanove("sobe.txt"); //poziva se funkcija za prebrojavanje clanova u nekoj datoteci i taj broj se smijesta u varijablu 
	//unos broja sobe u rasponu 1-20 jer hotel ima 20 soba
	do{
		cout<<"Unesite broj sobe koju zelite rezervisati (nas hotel ima 20 soba): "; // bug ukoliko se unese npr "23 10"
		cin>>redniBroj;
		if(!cin){
			cin.clear();
			cin.ignore(100, '\n');
			poruka(3);
			return;
		}
		if(redniBroj>brojSoba || redniBroj<=0){
			cout<<"Ta soba ne postoji!\n";
		}
	}while(redniBroj>brojSoba || redniBroj<=0);
	//ucitavanje datoteke sobe.txt kako bi se provjerilo da li je izabrana soba zauzeta
	ifstream ispis("sobe.txt");
	if(ispis.is_open()){
		while(ispis>>s->brojSobe>>s->cijena>>velicinaBroj>>s->slobodna){
			if(velicinaBroj == 1) s->velicina = jednokrevetna;
			else if(velicinaBroj == 2) s->velicina = dvokrevetna;
			else if(velicinaBroj == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;	
			if(redniBroj==s->brojSobe && s->slobodna){
				cout<<"Soba je zauzeta\n";
				return;
			}
		}
	}	
	else{
		poruka(5);
		return;
	}
	ispis.close();
	//unos datuma rezervacije; tu imamo funkciju koja provjerava da li je uneseni datum ispravan, te ukoliko nije ispisuje se odgovarajuca poruka;
	do{
		cout<<"Unesite datum pocetka rezervacije (dd/mm/gggg): ";
		cin>>datumPrijave->dan>>datumPrijave->mjesec>>datumPrijave->godina;
		if(!cin){
			cin.clear();
			cin.ignore(100, '\n');
			poruka(3);
			return;
		}
		if(!provjera_datuma(datumPrijave)) cout<<"Nepostojeci datum, unesite ponovo!\n";
	}while(!provjera_datuma(datumPrijave));
	//unos krajnjeg datuma rezervacije; imamo istu funkciju za provjeru datuma, ali se poziva jos jedna funkcija koja osigurava da datum zavrsetka bude 100% poslije datuma pocetka
	//rezervacije
	do{
		cout<<"Unesite datum zavrsetka rezervacije (dd/mm/gggg): ";
		cin>>datumOdjave->dan>>datumOdjave->mjesec>>datumOdjave->godina;
		if(!provjera_datuma(datumOdjave)) cout<<"Nepostojeci datum, unesite ponovo!\n";
		if(!provjeraDatuma2(datumPrijave, datumOdjave)) cout<<"Datum odjave mora biti nakon datuma prijave!\n";
	}while(!provjera_datuma(datumOdjave) || !provjeraDatuma2(datumPrijave, datumOdjave));
	//Upisivanje podataka u datoteku rezervacije.txt nakon sto su prosle sve provjere
	ofstream upis("rezervacije.txt", ios::app);
	if(upis.is_open()){
		srand(time(NULL));
		rand();
		r->kod=rand() %900+100; // (b-a+1) + a
		upis<<r->kod<<" ";
		upis<<redniBroj<<" ";
		upis<<user<<" ";
		upis<<datumPrijave->dan<<" "<<datumPrijave->mjesec<<" "<<datumPrijave->godina<<" ";
		upis<<datumOdjave->dan<<" "<<datumOdjave->mjesec<<" "<<datumPrijave->godina<<" ";
		upis<<stanje<<endl;
		cout<<"Uspjesno ste izvrsili rezervaciju sobe. Rezervacija ce biti prihvacena kroz nekoliko trenutaka."<<endl;
	}
	else{
		poruka(5);
		return;
	}
	upis.close();
	delete s;
	delete r;
	delete rac;
	delete datumPrijave;
	delete datumOdjave;
}
//funkcija koja provjerava ispravnost datuma
bool provjera_datuma(Datum *datum){
    int dani_u_mjesecu[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(prestupna(datum->godina)) dani_u_mjesecu[1]++; 
    bool ispravan = true; 
    if(datum->dan < 1 || datum->mjesec < 1 || datum->mjesec > 12 || datum->godina < 1) ispravan = false;
    if(datum->dan > dani_u_mjesecu[datum->mjesec-1]) ispravan = false; 
    return ispravan; 
}
//funkcija koja osigurava da datum odjave dolazi nakon datuma prijavljivanaj
bool provjeraDatuma2(Datum *datum1, Datum *datum2){
	bool ispravan=true;
	if(datum2->godina<=datum1->godina && datum2->mjesec<=datum1->mjesec && datum2->dan<=datum1->dan) ispravan=false;
	if(datum2->godina==datum1->godina && datum2->mjesec<datum1->mjesec && datum2->dan>=datum1->dan) ispravan=false;
	if(datum2->godina<datum1->godina && datum2->dan>=datum1->dan && datum2->mjesec>=datum1->mjesec) ispravan=false;
	if(datum2->godina<datum1->godina && datum2->dan<=datum1->dan && datum2->mjesec>=datum1->mjesec) ispravan=false;
	if(datum2->dan>datum1->dan && datum2->mjesec>datum1->mjesec && datum2->godina<datum1->godina) ispravan=false;
	if(datum2->dan>datum1->dan && datum2->mjesec<datum1->mjesec && datum2->godina<datum1->godina) ispravan=false;
	return ispravan;
}
//funkcija za rezervaciju dodatnih aktivnosti
void rezervacijaDodatnihAktivnosti(string user){
	int stanjeRezervacije, redniBroj, aktivnost;
	string prihvaceno;
	bool imaRezervaciju=false;
	Rezervacija *r=new Rezervacija;
	dodatneAktivnosti *da=new dodatneAktivnosti;
	//provjera da li korisnik ima prihvacenu rezervaciju, ukoliko ima, funkcija ce mu ispisati moguce dodatne aktivnosti
	ifstream ispis("rezervacije.txt");
	if(ispis.is_open()){
		while(ispis>>r->kod>>r->broj_sobe>>r->username>>r->datumPrijave.dan>>r->datumPrijave.mjesec>>r->datumPrijave.godina>>
				r->datumOdjave.dan>>r->datumOdjave.mjesec>>r->datumOdjave.godina>>stanjeRezervacije){
			if(stanjeRezervacije==0) prihvaceno="cekanje";
			else prihvaceno="prihvaceno";
			if(r->username==user && prihvaceno=="prihvaceno"){
				imaRezervaciju=true;
				cout<<"\n\n\n\n\n\n\n\n";
				cout<<"================";
				poruka(1);
				cout<<"Lista dodatnih aktivnosti naseg hotela su:\n\n1. Teretana\t2. Bazen\t3. Fitness\t4. Masaza\t5. Sauna\n\n";
				cout<<"================";
				poruka(1);
			}
		}
	}
	else{
		poruka(5);
		return;
	}
	ispis.close();
	//ukoliko ima odobrenu rezervaciju, korisnik moze rezervisati dodatnu aktivnost
	if(imaRezervaciju){
		do{
			cout<<"Unesite redni broj dodatne aktivnosti koju zelite rezervisati: ";
			cin>>redniBroj;
			if(!cin){
				cin.clear();
				cin.ignore(100, '\n');
				poruka(3);
				return;
			}
			if(redniBroj<1 || redniBroj>5) poruka(3);
		}while(redniBroj<1 || redniBroj>5);
	}
	else{
		cout<<"Nemate rezervisanu sobu!\n";
		return;
	}
	//provjera koja korisniku nece omoguciti da dva puta rezervise istu stvar
	ifstream provjera("dodatneAktivnosti.txt");
	if(provjera.is_open()){
		while(provjera>>da->username>>aktivnost>>da->cijena){
			if(aktivnost==1) da->aktivnost=teretana;
			else if(aktivnost==2) da->aktivnost=bazen;
			else if(aktivnost==3) da->aktivnost=fitness;
			else if(aktivnost==4) da->aktivnost=masaza;
			else da->aktivnost=sauna;
			if(user==da->username && redniBroj==da->aktivnost){
				cout<<"Vec imate rezervisanu tu aktivnost\n";
				return;
			}
		}
	}
	else{
		poruka(5);
		return;
	}
	provjera.close();
	//upis u datoteku dodatneAktivnosti nakon svih provjera
	ofstream upis("dodatneAktivnosti.txt", ios::app);
	if(upis.is_open()){
		switch(redniBroj){
			case 1:{
				upis<<user<<" ";
				upis<<1<<" ";
				upis<<15<<endl;
				break;
			}
			case 2:{
				upis<<user<<" ";
				upis<<2<<" ";
				upis<<25<<endl;
				break;
			}
			case 3:{
				upis<<user<<" ";
				upis<<3<<" ";
				upis<<40<<endl;
				break;
			}
			case 4:{
				upis<<user<<" ";
				upis<<4<<" ";
				upis<<20<<endl;
				break;
			}
			case 5:{
				upis<<user<<" ";
				upis<<5<<" ";
				upis<<35<<endl;
				break;
			}
		}
		cout<<"Uspjesno ste rezervisali Vasu dodatnu aktivnost!\n";
	}
	else{
		poruka(5);
		return;
	}
	upis.close();
	delete r;
	delete da;
}
//funckija za placanje racuna
void platiRacun(string user){
	int stanjeRezervacije, dAktivnost, izbor, placen1, placenStanje, sifra, pozicija=0, brClanova=0, brClanovaSobe, velicina, pozicijaSobe=0, brojSobe, brojacAktivnosti=0;
	float ukupnaCijena, stanje, stanjeKase, kusur, iznos;
	string akt, korisnik;
	bool placen=false;
	Rezervacija *r=new Rezervacija;
	dodatneAktivnosti *a=new dodatneAktivnosti;
	Racun *rac=new Racun;
	Soba *s=new Soba;
	brClanova=prebroj_clanove("racuni.txt");
	brClanovaSobe=prebroj_clanove("sobe.txt");
	Racun *racun1=new Racun[brClanova];
	Soba *sobe=new Soba[brClanovaSobe];
	ifstream ispisRacuna("racuni.txt");
	ifstream ispisAktivnosti("dodatneAktivnosti.txt");
	ifstream ispisRezervacije("rezervacije.txt");
	ifstream ispisSoba("sobe.txt");
	//smjestanje svih podataka u niz te dodjeljivanje vrijednosti varijablama koje ce se poslije koristiti
	if(ispisRacuna.is_open()){
		while(ispisRacuna>>rac->id>>rac->username>>rac->iznos>>rac->placeno){
			racun1[pozicija]=*rac;
			pozicija++;
			if(rac->username==user){
				ukupnaCijena=rac->iznos;
				korisnik=rac->username;	
			} 
		}
	}
	else{
		poruka(5);
		return;
	}
	ispisRacuna.close();
	//dodjeljivanje vrijednosti varijablama radi kasnijeg ispisa
	if(ispisAktivnosti.is_open()){
		while(ispisAktivnosti>>a->username>>dAktivnost>>a->cijena){
			if(dAktivnost==1) akt="teretana";
			else if(dAktivnost==2) akt="bazen";
			else if(dAktivnost==3) akt="fitness";
			else if(dAktivnost==4) akt="masaza";
			else akt="sauna";
			if(a->username==user){
				brojacAktivnosti++;
			}
		}
	}
	else{
		poruka(5);
		return;
	}
	ispisAktivnosti.close();
	bool postoji=false;
	//ispis informacija o rezervaciji
	if(ispisRezervacije.is_open()){
		while(ispisRezervacije>>r->kod>>r->broj_sobe>>r->username>>r->datumPrijave.dan>>r->datumPrijave.mjesec>>r->datumPrijave.godina>>
			  r->datumOdjave.dan>>r->datumOdjave.mjesec>>r->datumOdjave.godina>>stanjeRezervacije){
			if(stanjeRezervacije==0) r->stanje=cekanje;
			else r->stanje=prihvaceno;
			if(r->username==user && r->stanje==prihvaceno){ 
				brojSobe=r->broj_sobe;
				cout<<"\n\n\n\n\n\n\n\n";
				cout<<"\t\t\t\tInformacije o vasoj rezervaciji\n";
				cout<<"================================";
				poruka(1);
				cout<<setw(5)<<"Broj sobe"<<setw(20)<<"Datum prijave"<<setw(20)<<"Datum odjave"<<setw(25)<<"Dodatna aktivnost"<<setw(20)<<"Ukupna cijena"<<setw(15)<<endl;
				cout<<"================================";
				poruka(1);
				cout<<setw(10)<<setw<<r->broj_sobe<<r->datumPrijave.dan<<"."<<r->datumPrijave.mjesec<<"."<<r->datumPrijave.godina<<setw(13);
				cout<<r->datumOdjave.dan<<"."<<r->datumOdjave.mjesec<<"."<<r->datumOdjave.godina<<setw(20)<<akt<<setw(21)<<ukupnaCijena<<setw(15)<<endl;
				cout<<"================================";
				poruka(1);
				postoji=true; 
			}
		}
	}
	else{
		poruka(5);
		return;
	}
	ispisRezervacije.close();
	if(!postoji){
		cout<<"Nemate rezervisanu sobu!\n";
		return;
	}
	if(ukupnaCijena>=100000){
		cout<<"Greska u sistemu! Trenutno ne mozete platiti racun.\n";
		return;
	}
	//smjestanje podataka iz datoteke sobe.txt u niz
	if(ispisSoba.is_open()){
		while(ispisSoba>>s->brojSobe>>s->cijena>>velicina>>s->slobodna){
			if(velicina == 1) s->velicina = jednokrevetna;
			else if(velicina == 2) s->velicina = dvokrevetna;
			else if(velicina == 3) s->velicina = trokrevetna;
			else s->velicina = predsjednickiApartman;
			sobe[pozicijaSobe]=*s;
			pozicijaSobe++;	
		}
	}
	else{
		poruka(5);
		return;
	}
	ispisSoba.close();
	//placanje racuna
		cout<<"\nDa li zelite platiti racun sada? 1. Da\t2. Ne\n";
		cout<<endl;	
		do{
			cout<<"Unesite Vas izbor: ";
			cin>>izbor;
			if(!cin){
				cin.clear();
				cin.ignore(100, '\n');
				poruka(3);
				return;
			}
			if(izbor<1 || izbor>2) poruka(3);
		}while(izbor<1 || izbor>2);
		if(izbor==1){ //ako izabere da plati program mu trazi da unese kolicinu novca
			do{
				cout<<"Unesite iznos novca s kojim zelite platiti: ";
				cin>>iznos;
				if(!cin){
					cin.clear();
					cin.ignore(100, '\n');
					poruka(3);
					return;
				}
				placen=true; 
				if(iznos<ukupnaCijena) cout<<"Iznos novca mora biti veci od ukupne cijene rezervacije!\n";
				if(iznos>100000) cout<<"Iznos novca mora biti manji od 100.000KM\n";
			}while(iznos<ukupnaCijena || iznos>100000);
		}
		else return;  //ukoliko je korisnik izabrao da nece platiti racun u tom trenutku, vraca ga na korisnik menu;
	//promjena stanja iz neplacen u placen ukoliko je racun placen
	if(placen){
		for(int i=0;i<brClanova;i++){
			if(korisnik==racun1[i].username && !racun1[i].placeno){
				racun1[i].placeno=1;
			}
		}
		//promjena stanja sobe iz zauzeta u slobodna ukoliko je korisnik platio racun; pretpostavljamo da se racun placa kada istekne rezervacija
		for(int j=0;j<brClanovaSobe;j++){
			if(brojSobe==sobe[j].brojSobe){
				sobe[j].slobodna=0;
			}
		}
	}
	//spremanje stanja kase u varijablu koja ce se poslije koristiti za ispis kusura koji je potrebno vratiti korisniku
	ifstream ispisStanja("hotel.txt");
	if(ispisStanja.is_open()){
		while(ispisStanja>>stanje){
			stanjeKase=stanje;
		}
	}
	else{
		poruka(5);
		return;
	}
	ispisStanja.close();
	//promjena stanja u kasi hotela
	ofstream upis_u_kasu("hotel.txt");
	ofstream promjenaStanjaRacuni("racuni.txt");
	if(placen){
		if(upis_u_kasu.is_open()){
			stanjeKase+=iznos; //povecava se stanje kase hotela za iznos koji je korisnik platio
			if(iznos>ukupnaCijena){
				kusur=iznos-ukupnaCijena; //ukoliko je korisnik unio vecu kolicinu novca nego sto iznosi racun, sistem ce izracunati kusur
				stanjeKase-=kusur; //iz kase hotela se vraca kusur korisniku
				cout<<"Vas kusur iznosi: "<<kusur<<endl;
			}
			upis_u_kasu<<stanjeKase; //upis novog stanja kase u datoteku hotel.txt
		}
		else{
			poruka(5);
			return;
		}
		upis_u_kasu.close();
		//promjena stanja u datoteci racuni.txt; ukoliko je racun placen, mijenja stanje racuna iz neplacen u placen
		if(promjenaStanjaRacuni.is_open()){
			if(korisnik==user){
				for(int i=0;i<brClanova;i++){
					promjenaStanjaRacuni<<racun1[i].id<<" "<<racun1[i].username<<" "<<racun1[i].iznos<<" "<<racun1[i].placeno<<endl;
				}
			}
		}
		else{
			poruka(5);
			return;
		}
		promjenaStanjaRacuni.close();
		//promjena stanja u datoteci sobe.txt; ukoliko je racun placen, mijenja se stanje racuna iz zauzeta u slobodna
		ofstream promjenaStanjaSobe("sobe.txt");
		if(promjenaStanjaSobe.is_open()){
			for(int j=0;j<brClanovaSobe;j++){
					promjenaStanjaSobe<<sobe[j].brojSobe<<" "<<sobe[j].cijena<<" "<<sobe[j].velicina<<" "<<sobe[j].slobodna<<endl;
			}
		}
	}
	//brisanje rezervacije nakon sto je racun placen
	int brRezervacija;
	brRezervacija=prebroj_clanove("rezervacije.txt");
	Rezervacija *bris=new Rezervacija;
	Rezervacija *brisanje=new Rezervacija[brRezervacija];
	int brojac=0;
	int rezervacijaStanje;
	int pom;
	ifstream brisanjeRezervacija("rezervacije.txt");
	if(brisanjeRezervacija.is_open()){
		while(brisanjeRezervacija>>bris->kod>>bris->broj_sobe>>bris->username>>bris->datumPrijave.dan>>bris->datumPrijave.mjesec>>bris->datumPrijave.godina>>
			  bris->datumOdjave.dan>>bris->datumOdjave.mjesec>>bris->datumOdjave.godina>>rezervacijaStanje){
			if(rezervacijaStanje == 0) bris->stanje=cekanje;
			else if(rezervacijaStanje==1) bris->stanje=prihvaceno;
			brisanje[brojac]=*bris;  //smjestanje podataka iz datoteke rezervacije.txt u dinamicki alociran niz
			brojac++;
			if(bris->username==user){
				pom=brojac-1;  //odredjivanje pozicije rezervacije koju treba izbrisati u datoteci rezervacije.txt 
			}	
		}
	}
	else{
		poruka(5);
		return;
	}
	brisanjeRezervacija.close();
	brisanjeRezervacije(brisanje, brRezervacija, pom);
	//brisanje dodatnih aktivnosti iz datoteke dodatne aktivnosti nakon sto je racun placen; postupak je isti kao i za brisanje rezervacija
	int brDodatnihAktivnosti;
	brDodatnihAktivnosti=prebroj_clanove("dodatneAktivnosti.txt");
	dodatneAktivnosti *dodatneA=new dodatneAktivnosti;
	dodatneAktivnosti *brisanjeDodatne=new dodatneAktivnosti[brDodatnihAktivnosti];
	int brojac2=0;
	int dodatnaAktivnostEnum;
	ifstream brisanjeDodatneAktivnosti("dodatneAktivnosti.txt");
	if(brisanjeDodatneAktivnosti.is_open()){
		while(brisanjeDodatneAktivnosti>>dodatneA->username>>dodatnaAktivnostEnum>>dodatneA->cijena){
			if(dodatnaAktivnostEnum==1) dodatneA->aktivnost=teretana;
			else if(dodatnaAktivnostEnum==2) dodatneA->aktivnost=bazen;
			else if(dodatnaAktivnostEnum==3) dodatneA->aktivnost=fitness;
			else if(dodatnaAktivnostEnum==4) dodatneA->aktivnost=masaza;
			else dodatneA->aktivnost=sauna;
			brisanjeDodatne[brojac2]=*dodatneA;
			brojac2++;
		}
	}
	else{
		poruka(5);
		return;
	}
	brisanjeDodatneAktivnosti.close();
	aktivnostBrisanje(brisanjeDodatne, brDodatnihAktivnosti, user);
	delete r;
	delete rac;
	delete a;
	delete s;
	delete[] racun1;
	delete[] sobe;
	delete bris;
	delete[] brisanje;
	delete dodatneA;
	delete[] brisanjeDodatne;	
}
//funkcija za brisanje rezervacija iz rezervacije.txt
void brisanjeRezervacije(Rezervacija* niz, int br_rezervacija, int pozicija){
	string linija;
	ofstream izlaz("rezervacije.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_rezervacija; i++){
			if(i == pozicija){  //kad pronadje dati argument u tu liniju ispise izbrisano
				izlaz << "obrisano" << endl;
			}
			else{ //u suprotnom nista ne radi
				izlaz<<niz[i].kod<<" "<<niz[i].broj_sobe<<" "<<niz[i].username<<" "<<niz[i].datumPrijave.dan<<" "<<niz[i].datumPrijave.mjesec<<" "<<niz[i].datumPrijave.godina<<" "
					<<niz[i].datumOdjave.dan<<" "<<niz[i].datumOdjave.mjesec<<" "<<niz[i].datumOdjave.godina<<" "<<niz[i].stanje<<endl;
			}
		}
	izlaz.close();	
	}
	else{
		poruka(5);
		return;
	}
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		ofstream novi_izlaz("update.txt");  //u pomocnu datoteku sprema novi ispis dodatnih aktivnosti
		if(novi_izlaz.is_open()){
			while(getline(ulaz,linija)){
				if(linija != "obrisano"){
					novi_izlaz << linija << endl;
				}
			}
		novi_izlaz.close();	
		}
		else{
			poruka(5);
			return;
		}
	ulaz.close();
	remove("rezervacije.txt"); //uklanja se postojeca datoteka
	rename("update.txt","rezervacije.txt"); //a pomocna se preimenuje u rezervacije.txt
	}
	else{
		poruka(5);
		return;
	}	
}
//funkcija za brisanje dodatnih aktivnosti iz datoteke dodatneAktivnosti.txt; postupak je isti kao u funkciji iznad tj. funkciji za brisanje rezervacija
void aktivnostBrisanje(dodatneAktivnosti* niz, int br_dodatnihAktivnosti, string user){
	string linija;
	ofstream izlaz("dodatneAktivnosti.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_dodatnihAktivnosti; i++){
			if(niz[i].username==user){
				izlaz << "obrisano" << endl;
			}
			else{
				izlaz<<niz[i].username<<" "<<niz[i].aktivnost<<" "<<niz[i].cijena<<endl;
			}
		}
	izlaz.close();	
	}
	else{
		poruka(5);
		return;
	}
	ifstream ulaz("dodatneAktivnosti.txt");
	if(ulaz.is_open()){
		ofstream novi_izlaz("promijeni.txt");
		if(novi_izlaz.is_open()){
			while(getline(ulaz,linija)){
				if(linija != "obrisano"){
					novi_izlaz << linija << endl;
				}
			}
		novi_izlaz.close();	
		}
		else{
			poruka(5);
			return;
		}
	ulaz.close();
	remove("dodatneAktivnosti.txt");
	rename("promijeni.txt","dodatneAktivnosti.txt");
	}
	else{
		poruka(5);
		return;
	}	
}
