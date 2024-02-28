#include "ui.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <random>

using namespace std;
using std::cin;
using std::cout;
using std::string;

void UI::afisare(const vector<Produs>& magazin) {
	int ok = 1;
	const char separator = ' ';
	const int nameWidth = 10;
	const int numWidth = 10;
	cout<<"      ";
	cout << left << setw(nameWidth) << setfill(separator) << "Nume";
	cout << left << setw(nameWidth) << setfill(separator) << "Tip";
	cout << left << setw(nameWidth) << setfill(separator) << "Pret";
	cout << left << setw(nameWidth) << setfill(separator) << "Producator\n";
	for (const auto& produs : magazin) {
		cout << "      ";
		cout << left << setw(nameWidth) << setfill(separator) << produs.get_nume();
		cout << left << setw(nameWidth) << setfill(separator) << produs.get_tip();
		cout << left << setw(nameWidth) << setfill(separator) << produs.get_pret();
		cout << left << setw(nameWidth) << setfill(separator) << produs.get_producator() << '\n';
		ok = 0;
	}
	if (ok)
		cout << "Nu exista produse inregistrate.\n";
}

void UI::afisare_cos() {
	afisare(cos.get_all());
	int s = 0;
	for (auto& produs : cos.get_all())
		s = s + produs.get_pret();
	cout << "Pret:"<< s << "\n\n";
}

void UI::golire() {
	cos.golire();
	cout << "Cos golit cu succes!\n";
}

void UI::populeaza() {

	vector<Produs> rez{ srv.get_all() };

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, rez.size()-1); // define the range

	int nr;
	cout << "Numarul produselor de generat: ";
	cin >> nr;
	for (int n = 0; n < nr; ++n)
	{
		int poz = distr(gen);
		Produs p = rez[poz];
		cos.adauga_cos(p.get_nume(), p.get_tip(), p.get_pret(), p.get_producator());
	}
	
}

void UI::adauga() {
	string nume, tip, producator;
	int pret;
	cout << "Nume: ";
	cin >> nume;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	cout << "Producator: ";
	cin >> producator;
	srv.adauga(nume, tip, pret, producator);
	cout << "Produs adaugat.\n";
}

void UI::adauga_cos() {
	string nume;
	cout << "Nume produs: ";
	cin >> nume;
	Produs produs = srv.cauta(nume);
	cos.adauga(produs.get_nume(), produs.get_tip(), produs.get_pret(), produs.get_producator());
	cout << "Produs adaugat in cos.\n";
}

void UI::sterge() {
	string nume, tip, producator;
	int pret;
	cout << "Nume: ";
	cin >> nume;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	cout << "Producator: ";
	cin >> producator;
	Produs p{ nume,tip,pret,producator };
	srv.sterge(p);
	cout << "Produs sters.\n";
}
void UI::modifica() {
	string nume, tip, producator;
	int pret, pret_nou;
	cout << "Nume: ";
	cin >> nume;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	cout << "Producator: ";
	cin >> producator;
	Produs p{ nume,tip,pret,producator };
	cout << "Pret nou: ";
	cin >> pret_nou;
	srv.modificare(p, pret_nou);
	cout << "Produs modificat.\n";
}
void UI::cauta() {
	string nume;
	int pret;
	cout << "Nume: ";
	cin >> nume;
	cout << "Pret: ";
	cin >> pret;
	Produs produs = srv.cauta_el(nume, pret);
	cout << produs.get_nume() << " " << produs.get_tip() << " " << produs.get_pret() << " " << produs.get_producator() << '\n';
}

void UI::filtrare() {
	string optiune;
	cout << "Pret/Nume/Producator\nScrie\n p-pentru pret\n n-pentru nume\n pr-pentru producator\n";
	cin >> optiune;
	vector<Produs> rez;
	if (optiune == "n")
	{
		cout << "Scrie numele: ";
		string nume;
		cin >> nume;
		rez = srv.filtrare_nume(nume);
	}
	else if (optiune == "p")
	{
		cout << "Scrie pretul";
		int pret;
		cin >> pret;
		rez = srv.filtrare_pret_mai_mic(pret);
	}
	else if (optiune == "pr") {
		cout << "Scrie producatorul";
		string producator;
		cin >> producator;
		rez = srv.filtrare_producator(producator);
	}
	else
	{
		cout << "Optiune invalida!Reintrodu optiunea: \n";
		filtrare();
	}
	afisare(rez);
		
}

void UI::sortare() {
	cout << "Alege sortarea: \n";
	cout << ">>>1.Nume\n";
	cout << ">>>2.Pret\n";
	cout << ">>>3.Nume+tip\n";
	int opt;
	vector<Produs> rez;
	cin >> opt;
	switch (opt) {
	case 1:
	{
		rez = srv.sort_nume();
		afisare(rez);
		break;
	}
		
	case 2:
	{
		rez = srv.sort_pret();
		afisare(rez);
		break;
	}
		
	case 3:
	{
		rez = srv.sort_nume_tip();
		afisare(rez);
		break;
	}
		
	}
}

void UI::salveaza_fisier() {
	string nume;
	cout << "Nume fisier: ";
	cin >> nume;
	cos.salveaza_fisier(nume);
}

void UI::run() {
	while (true) {
		cout << "0.Exit\n";
		cout << "1.Afisare produse\n";
		cout << "2.Adaugare produs\n";
		cout << "3.Sterge produs\n";
		cout << "4.Modifica produs\n";
		cout << "5.Cauta produs\n";
		cout << "6.Filtrare\n";
		cout << "7.Sortare\n";
		cout << "8.Afisare cos\n";
		cout << "9.Adaugare cos\n";
		cout << "10.Goleste cos\n";
		cout << "11.Genereaza cos\n";
		cout << "12.Salveaza in fisier\n";
		int opt;
		cin >> opt;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Comanda invalida!!\n";
			cin >> opt;
		}
		try {
			switch (opt) {
			case 1:
				afisare(srv.get_all());
				break;
			case 2:
				adauga();
				break;
			case 3:
				sterge();
				break;
			case 4:
				modifica();
				break;
			case 5:
				cauta();
				break;
			case 6:
				filtrare();
				break;
			case 7:
				sortare();
				break;
			case 8:
				afisare_cos();
				break;
			case 9:
				adauga_cos();
				break;
			case 10:
				golire();
				break;
			case 11:
				populeaza();
				break;
			case 12:
				salveaza_fisier();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n";
			}
		}
		catch (const RepoProdusExceptie& ex) {
			cout << ex << '\n';
		}
		catch (const ValidatorExceptie& ex) {
			cout << ex << '\n';
		}
	}
}