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
|| 			© 2021                              	||
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
const string adminUsername="admin";//postavljamo globalno username za admina
const string adminPassword="admin";//postavljamo globalno sifru za admina
//-------------------- >>> GLOBALNE VARIJABLE <<< ---------------------

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
void pretrazi_sobe();
void uredi_cjenovnik();
void azuriraj_sobe(Soba*,int,int,float);
//-------------------- >>> MAIN FUNKCIJA <<< ---------------------

int main() {
	splashscreen();
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
				if(ispravnostKorisnik) cout<<"Uspjesno ste prijavljeni"<<endl;//ovaj if sluzi za otvaranje korisnickog menija
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
								//
								break;
							}
							case 6: {
								system("cls");
								//
								break;
							}
							case 7: {
								system("cls");
								//
								break;
							}
							case 8: {
								system("cls");
								//
								break;
							}
							case 9: {
								system("cls");
								//
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

//funkcija koja pruza odgovarajucu poruku na osnovu greske
void poruka(int broj) {
	switch(broj) {
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
//funkcija za prvi menu
int glavniMenu() {
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\t\tGLAVNI MENU"<<endl;
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
	if(brojac==2) { //ukoliko su username i sifra ispravno uneseni, ispravnost postavljamo na true, to ce nam trebati da mozemo dalje raditi u programu
		ispravnost=true;
	}
	delete[] korisnici;
}

//funckija za prijavu admina
void adminPrijava(bool& ispravnost) {
	int broj=0, brojPokusaja=0, brojac=0;
	bool rezultat=false;
	string korisnickoIme, sifra;
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

	if(brojac==2) {
		ispravnost=true;
	}
}
//funkcija koja sluzi za unos sifre bez prikazivanja karaktera
string skrivena_sifra(string sifra, char znak) {
	sifra.clear();
	while (znak = getch()) {
		if (znak != 13) {
			cout << "*";
		}
		sifra += znak;
		if (znak == 13) {
			break;
		}
	}
	sifra.erase(sifra.length() - 1);
	return sifra;
}
//funkcija za admin menu
int admin_menu() {
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n";
	poruka(1);
	cout<<"\t\t\t\tADMIN MENU"<<endl;
	cout << "\t\t1. Prikazi rezervacije\n";
	cout << "\t\t2. Prihvati / odbaci rezervaciju\n";
	cout << "\t\t3. Pretrazi sobe po kriterijima\n";
	cout << "\t\t4. Uredi cjenovnik\n";
	cout << "\t\t5. Izdaj racun\n";
	cout << "\t\t6. Pregled svih racuna\n";
	cout << "\t\t7. Stanje hotela\n";
	cout << "\t\t8. Dodaj radnika\n";
	cout << "\t\t9. Informacije o radnicima\n";
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
	cout<<"-------------------------------------------------------------------------------------\n";
	cout<<setw(5)<<"Kod"<<setw(14)<<"Broj sobe"<<setw(16)<<"Username"<<setw(14)<<"Prijava"<<setw(14)<<"Odjava"<<setw(16)<<"Stanje"<<endl;
	cout<<"-------------------------------------------------------------------------------------\n";
	ifstream ulaz("rezervacije.txt");
	if(ulaz.is_open()){
		while(ulaz >> r->kod >> r->broj_sobe >> r->username >> r->datumPrijave.dan >> r->datumPrijave.mjesec >> r->datumPrijave.godina
			>> r->datumOdjave.dan >> r->datumOdjave.mjesec >> r->datumOdjave.godina >> broj){
			if(broj == 0) temp = "Cekanje";
			else temp = "Prihvaceno";
			cout<<setw(5)<<r->kod<<setw(12)<<r->broj_sobe<<setw(16)<<r->username<<setw(10)<<right<<r->datumPrijave.dan<<"."<<r->datumPrijave.mjesec<<"."<<r->datumPrijave.godina
			<<setw(10)<<r->datumOdjave.dan<<"."<<r->datumOdjave.mjesec<<"."<<r->datumOdjave.godina<<setw(14)<<temp<<endl;
		}
		ulaz.close();
		cout<<"-------------------------------------------------------------------------------------\n";
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
	cout<<setw(5)<<"Broj sobe"<<setw(10)<<"Cijena"<<setw(15)<<"Velicina"<<setw(15)<<"Stanje"<<endl;
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
				cout<<setw(5)<<s->brojSobe<<setw(12)<<s->cijena<<setw(18)<<krevet<<setw(15)<<stanje<<endl;
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
