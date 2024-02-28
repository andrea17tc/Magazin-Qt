#include "Produs.h"
#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>

using std::ostream;
using std::stringstream;


void RepoProdus::adauga(const Produs& p) {
	/*Adauga un produs la lista de produse
	param: p - produsul de adaugat
	type: Produs&
	return - 
	raises: msg - daca exista deja produsul
	*/
	if (exist(p)) {
		throw RepoProdusExceptie("Produsul cu numele " + p.get_nume() + ", tipul " + p.get_tip() + ", producatorul " + p.get_producator() + " exista deja.\n");
	}
	all.push_back(p);
}

void RepoProdus::adauga_cos(const Produs& p) {
	/*Adauga un produs la lista de produse
	param: p - produsul de adaugat
	type: Produs&
	return -
	*/
	all.push_back(p);
}

bool RepoProdus::exist(const Produs& p) const{
	/*Verifica daca exista produsul in lista de produse
	* param: p - produsul cautat
	* type: Produs&
	* return : true - daca exista
	*			false - daca nu exista
	*/
	try {
		cauta_el(p.get_nume(), p.get_pret());
		return true;
	}
	catch (RepoProdusExceptie&) {
		return false;
	}
}

const Produs& RepoProdus::cauta_el(string nume, int pret) const {
	/* Cauta produsul cu numele dat.
	* param: nume - numele produsului cautat
	* type: string
	* return: ind - pozitia elementului - -1 daca nu este in lista
	*									 valoare pozitiva daca este in lista
	* rtype: int
	*/
	for (auto& i : all)
		if (cmp_nume(i, nume) && i.get_pret() == pret) {
			return i;
		}
	throw RepoProdusExceptie("Nu exista produsul\n");
}

int RepoProdus::cauta_poz(string nume, int pret) const{
	/* Cauta produsul cu numele dat.
	* param: nume - numele produsului cautat
	* type: string
	* return: ind - pozitia elementului - -1 daca nu este in lista
	*									 valoare pozitiva daca este in lista
	* rtype: int
	*/
	int ind = -1;
	for(int i=0;i<all.size();i++)
		if (cmp_nume(all[i], nume) && all[i].get_pret()==pret) {
			ind = i;
		}
	return ind;
}

int RepoProdus::cauta(string nume) const {
	/* Cauta produsul cu numele dat.
	* param: nume - numele produsului cautat
	* type: string
	* return: ind - pozitia elementului - -1 daca nu este in lista
	*									 valoare pozitiva daca este in lista
	* rtype: int
	*/
	int ind = -1;
	for (int i = 0; i < all.size(); i++)
		if (cmp_nume(all[i], nume)) {
			ind = i;
		}
	if (ind == -1)
		throw RepoProdusExceptie("Nu exista produsul\n");
	else
		return ind;
}

void RepoProdus::sterge(Produs& p) {
	/* Sterge un produs dat.
	* param: p - produsul dat
	* type: Produs&
	* return -
	* raises : mesaj daca produsul nu exista
	*/
	int ind = cauta_poz(p.get_nume(), p.get_pret());
	if (ind == -1){
		throw RepoProdusExceptie("Produsul cu numele " + p.get_nume() + " nu exista.\n");
	}
	else {
		all.erase(all.begin()+ind);
	}
}

void RepoProdus::modificare(Produs& p, int pret) {
	/* Modifica pretul unui produs dat.
	* param: p - produsul dat
	* type: Produs&
	* param: pret - pretul nou
	* type: int
	* return : -
	* raises: mesaj daca produsul nu exista
	*/
	int ind = cauta_poz(p.get_nume(), p.get_pret());
	if (ind == -1) {
		throw RepoProdusExceptie("Produsul cu numele " + p.get_nume() + " nu exista.\n");
	}
	else {
		all[ind].set_pret(pret);
	}
}

void RepoProdus::golire() {
	/*Goleste vectorul de produse.
	*/
	all.clear();
}

vector<Produs>& RepoProdus::get_all() noexcept {
	/*Returneaza lista de produse*/
	return all;
}

ostream& operator<<(ostream& out, const RepoProdusExceptie& ex) {
	/*Suprascrie operatorul << pentru a afisa mesajul in caz de exceptie*/
	out << ex.msg;
	return out;
}